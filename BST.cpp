#include <iostream>
#include <vector> //a list that grows and shrinks as you add and remove elements
#include <queue> //for level order traversal
#include <algorithm> //for std::max for height calculation
#include <climits> //LLONG_MIN/LLONG_MAX for isValidBST
#include <string> //for the label text in printTree
using namespace std;

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k){
        key = k;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
    private:
        TreeNode* root;   // Java's "private TreeNode root;" becomes a pointer in C++

        bool containsHelper(TreeNode* node, int key) {
        if (node == nullptr) {
            return false;                              
        }
        if (key == node->key) {
            return true;                              
        }
        if (key < node->key) {
            return containsHelper(node->left, key);     
        } else {
            return containsHelper(node->right, key);     
        }
     }

        bool insertHelper(TreeNode* node, int key) {
        if (key == node->key) {
            return false;                          // duplicate
        }
        if (key < node->key) {
            if (node->left == nullptr) {           // empty spot on the left?
                node->left = new TreeNode(key);    // attach new node here
                return true;
            }
            return insertHelper(node->left, key);  // otherwise keep walking left
        } else {
                if (node->right == nullptr) {     //empty spot on the right?
                    node->right = new TreeNode(key); //attach new node here
                    return true;}
            return insertHelper(node->right, key); //otherwise keep walking right
        }
        }

        void inorderHelper(TreeNode* node, vector<int>& result) {
           if (node == nullptr) {             // base case: empty spot, nothing to add
            return;
        }
        inorderHelper(node->left, result); // 1. everything on the left
        result.push_back(node->key);       // 2. me
        inorderHelper(node->right, result);// 3. everything on the right
        }

        void preorderHelper(TreeNode* node, vector<int>& result) {
           if (node == nullptr) {             // base case: empty spot, nothing to add
            return;
        }
        result.push_back(node->key);       //  me
        preorderHelper(node->left, result); // everything on the left
        preorderHelper(node->right, result);// everything on the right
        }

        void postorderHelper(TreeNode* node, vector<int>& result) {
           if (node == nullptr) {             // base case: empty spot, nothing to add
            return;
        }
        postorderHelper(node->left, result); // everything on the left
        postorderHelper(node->right, result);// everything on the right
        result.push_back(node->key);       //  me
        }

        
       int sizeHelper(TreeNode* node) {
        if (node == nullptr) {
            return 0;                                   //how many nodes in an empty spot?
        }
        return 1 + sizeHelper(node->left) + sizeHelper(node->right); //how many nodes in the left + how many nodes in the right + me
        }

        
        int heightHelper(TreeNode* node) {
           if (node == nullptr) {
               return -1; //height of an empty tree is -1. Height of tree with one node is 0.                                            
           }
           return 1 + max(heightHelper(node->left), heightHelper(node->right));
        }

        void rangeHelper(TreeNode* node, int low, int high, vector<int>& result) {
            if (node == nullptr) {
                return;
            }
            if (node->key > low) {                              // only go left if my key is bigger than low
                rangeHelper(node->left, low, high, result);
            }
            if (node->key >= low && node->key <= high) {                              // only add me if low <= my key <= high
                result.push_back(node->key);
            }
            if (node->key < high) {                              // only go right if my key is smaller than high
                rangeHelper(node->right, low, high, result);
            }
        }

        bool validHelper(TreeNode* node, long long low, long long high) {
            if (node == nullptr) {
                return true;            //is an empty tree a valid BST?
            }
            if (node->key <= low || node->key >= high) {
            return false;            //key is outside its allowed range
            }
            // the whole thing is valid only if BOTH sides are valid
            return validHelper(node->left,  low, node->key)     // left side's range
                && validHelper(node->right, node->key, high);    // right side's range
        }

                // smallest key in a subtree: go left as far as possible
        TreeNode* findMin(TreeNode* node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        // returns what should now sit in this node's spot
        TreeNode* removeHelper(TreeNode* node, int key) {
            if (node == nullptr) {
                return nullptr;
            }
            if (key < node->key) {
                node->left = removeHelper(node->left, key);
            } else if (key > node->key) {
                node->right = removeHelper(node->right, key);
            } else {
                // Cases 1 and 2: no left child, so the right child (maybe nullptr) moves up
                if (node->left == nullptr) {
                    TreeNode* child = node->right;
                    delete node;
                    return child;
                }
                // Case 2: no right child, so the left child moves up
                if (node->right == nullptr) {
                    TreeNode* child = node->left;
                    delete node;
                    return child;
                }
                // Case 3: two children, so replace with the inorder successor
                TreeNode* successor = findMin(node->right);
                node->key = successor->key;
                node->right = removeHelper(node->right, successor->key);
            }
            return node;
        }

    public:
       BinarySearchTree() {     // constructor: a new tree starts empty
        root = nullptr;
    }

        bool contains(int key) {
        return containsHelper(root, key);
    }

        bool insert(int key) {
        if (root == nullptr) {           // empty tree: new node becomes the root
            root = new TreeNode(key);
            return true;
        }
        return insertHelper(root, key);
    }

        vector<int> inorder() {
        vector<int> result;          // start with an empty list
        inorderHelper(root, result); // fill it, starting from the root
        return result;
    }

        vector<int> preorder() {
        vector<int> result;          // start with an empty list
        preorderHelper(root, result); // fill it, starting from the root
        return result;
    }

        vector<int> postorder() {
        vector<int> result;          // start with an empty list
        postorderHelper(root, result); // fill it, starting from the root
        return result;
    }

        vector<int> levelOrder() {
        vector<int> result;
        if (root == nullptr) {
            return result;     // empty tree: return the empty list
        }

        queue<TreeNode*> line;
        line.push(root); //put the root in the line

        while (!line.empty()) {
            TreeNode* node = line.front();   // look at the front node
            line.pop(); // remove it from the line

            result.push_back(node->key); // add its key to result

            // if it has a left child, put that child in the line
            if (node->left != nullptr) {
                  line.push(node->left);
           }
            // if it has a right child, put that child in the line
            if (node->right != nullptr) {
            line.push(node->right);
}
        }
        return result;
    }

       int size() {
           return sizeHelper(root);
       }

       int height() {
           return heightHelper(root);
       }
           
        vector<int> rangeSearch(int low, int high) {
            vector<int> result;
            rangeHelper(root, low, high, result);
            return result;
        }

        // "delete" in the assignment outline; named remove because delete is a C++ keyword
        bool remove(int key) {
            if (!contains(key)) {
                return false;
            }
            root = removeHelper(root, key);
            return true;
        }

        bool isValidBST() {
            return validHelper(root, LLONG_MIN, LLONG_MAX);
        }

        // TEST ONLY: builds an invalid tree (60 in the left subtree of 50)
        // so we can show isValidBST checks the whole subtree, not just parent-child pairs.
        void makeBrokenExample() {
            root = new TreeNode(50);           // 50 is the root
            root->left = new TreeNode(30);     // 30 is 50's left child
            root->left->right = new TreeNode(60); //60 is 30's right child, which is invalid for a BST
    }
};

void printList(vector<int> list) {
    for (int x : list) {
        cout << x << " ";
    }
    cout << endl;
}

// prints all four traversals and the validity check for a tree
void printTree(string label, BinarySearchTree& t) {
    cout << label << endl;
    cout << "  Inorder:     "; printList(t.inorder());
    cout << "  Preorder:    "; printList(t.preorder());
    cout << "  Postorder:   "; printList(t.postorder());
    cout << "  Level order: "; printList(t.levelOrder());
    cout << "  Valid BST:   " << t.isValidBST() << endl;
}

int main() {
    cout << boolalpha;
    BinarySearchTree tree;

    //Implementation Task 1: build the tree
    cout << "Task 1: Insert 50, 30, 80, 20, 40, 70, 90, 35, 75, 10, 85" << endl;
    int keys[] = {50, 30, 80, 20, 40, 70, 90, 35, 75, 10, 85};
    for (int k : keys) {
        bool added = tree.insert(k);
        cout << "insert(" << k << ") returned " << added
             << ", valid BST: " << tree.isValidBST() << endl;
    }
    cout << "insert(40) again (duplicate) returned " << tree.insert(40) << endl;
    cout << "contains(35): " << tree.contains(35) << endl;
    cout << "contains(60): " << tree.contains(60) << endl;
    cout << endl;

    //Implementation Task 2: all four traversals
    cout << "Task 2: Traversals " << endl;
    printTree("Original tree:", tree);
    cout << endl;

    //Implementation Task 3: delete 10, then 40, then 80
    cout << "Task 3: Deletions" << endl;

    tree.remove(10);
    cout << "After deleting 10 (Case 1: leaf, no children):" << endl;
    cout << "  Inorder:   "; printList(tree.inorder());
    cout << "  Valid BST: " << tree.isValidBST() << endl;

    tree.remove(40);
    cout << "After deleting 40 (Case 2: one child, 35 moves up):" << endl;
    cout << "  Inorder:   "; printList(tree.inorder());
    cout << "  Valid BST: " << tree.isValidBST() << endl;

    tree.remove(80);
    cout << "After deleting 80 (Case 3: two children, replaced by inorder successor 85):" << endl;
    cout << "  Inorder:   "; printList(tree.inorder());
    cout << "  Valid BST: " << tree.isValidBST() << endl;

    cout << "remove(999) on a missing key returned " << tree.remove(999) << endl;
    cout << endl;

    //Implementation Task 4: range searches (on the original tree)
    cout << "Task 4: Range searches" << endl;
    BinarySearchTree original;
    for (int k : keys) {
        original.insert(k);
    }
    cout << "rangeSearch(30, 75) on original tree: ";
    printList(original.rangeSearch(30, 75));
    cout << "rangeSearch(36, 84) on original tree: ";
    printList(original.rangeSearch(36, 84));
    cout << endl;

    //for part c1 table testing
    cout << "rangeSearch(51, 69) on original tree (should be empty): ";
    printList(original.rangeSearch(51, 69));

    //Height and size
    cout << "Height and size" << endl;
    BinarySearchTree empty;
    BinarySearchTree one;
    one.insert(5);
    cout << "Size of empty tree: "      << empty.size()      << endl;
    cout << "Size of one node tree: "   << one.size()        << endl;
    cout << "Size of larger tree: "     << original.size()   << endl;
    cout << "Height of empty tree: "    << empty.height()    << endl;
    cout << "Height of one node tree: " << one.height()      << endl;
    cout << "Height of larger tree: "   << original.height() << endl;
    cout << endl;

    //ImplementationTask 5: isValidBST deep-subtree test
    cout << "Task 5: isValidBST on a broken tree" << endl;
    BinarySearchTree broken;
    broken.makeBrokenExample();
    cout << "Tree: 50 with left child 30, and 60 as 30's right child." << endl;
    cout << "Every parent-child pair looks fine, but 60 is in the left subtree of 50." << endl;
    cout << "isValidBST: " << broken.isValidBST() << "  (expected false)" << endl;

    return 0;
}
