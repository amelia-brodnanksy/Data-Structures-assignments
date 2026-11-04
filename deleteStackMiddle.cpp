/* ==== ALGORITHM ====
1. Count the size of the original stack.
2. The number of elements I pop off will be (size of original stack / 2).
3. Push those elements into a temporary stack.
4. Pop one more element from the original stack and remove it completely. This is the middle element.
5. Pop everything off the temporary stack and push it back onto the original stack. */

#include <iostream>
using namespace std;

// Make a plate (stack element): holds a number and an arrow to the plate underneath
struct Node {
    int data;
    Node* next;
};

//Make a stack: holds a sign pointing to the top plate and a count of how many plates there are
class Stack {
public:
// The stack's two things
Node* top = nullptr;   // sign pointing to the top plate (nothing yet)
int size = 0;          // how many plates there are

// Function: Push a new plate on top
void push(int value) {
    Node* newNode = new Node;   // 1. make a new plate
    newNode->data = value;      //    write the number on it
    newNode->next = top;        // 2. its arrow points to the old top
    top = newNode;              // 3. sign now points to the new plate
    size += 1;                  // 4. one more plate
}

// Function: Pop the top plate off and give back its number
int pop() {
    if (top == nullptr) {                 // 1. empty? nothing to pop
        cout << "Stack is empty" << endl;
        return -1;
    }
    int value = top->data;                // 2. remember the number that used to be top
    Node* oldTop = top;                   // 3. hold on to the old top plate
    top = top->next;                      // 4. move top down one plate
    delete oldTop;                        // 5. throw away the old plate
    size -= 1;                            // 6. one fewer plate
    return value;                         // 7. give back the number of the old top plate
}

int peek() {
        if (top == nullptr) {
            cout << "stack is empty" << endl;
            return -1;
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {
    Stack original;  //make a stack to hold original numbers                 
    cout << "Type numbers, then type q when done typing numbers: ";  //prompt user for input
    int userNumbers;   //variable to hold user input       

    while (cin >> userNumbers) {      //while user is typing numbers                       
        original.push(userNumbers);        //push user input onto the stack              
    }

    Stack temporaryStack; //make a stack to hold temporary numbers
    int halfOriginalSize = original.size / 2; //calculate half the size of the original stack

    //loop through half the original stack, moving plates to the temporary stack
    for (int i = 0; i < halfOriginalSize; i++) { 
    int plate = original.pop();        // take a plate off, catch its number
    temporaryStack.push(plate);        // put it on the temp stack
    }

    original.pop();     // remove the middle

    //move the plates from the temporary stack back to the original stack
    while (!temporaryStack.isEmpty()) {
    int plate = temporaryStack.pop();
    original.push(plate);
}

cout << "Stack after deleting the middle (top to bottom): ";
    while (!original.isEmpty()) {
        cout << original.pop() << " ";
    }
    cout << endl;

}