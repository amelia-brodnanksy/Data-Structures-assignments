//  Write a program to reverse the following linked list: 8 25 3 41 22
/*
1. create the list
2. reverse the list
3. set head to the new first node
display the reversed list
return 0
*/

#include <iostream> 
using namespace std; 

int main () { 

    //Define the structure for a node in the linked list
    struct Node {
        int data; //Data field to store the value of the node
        Node* next; //Pointer to the next node in the linked list
    };

    //Declare pointers to the head and tail of the linked list
    Node* head = nullptr; //pointer to the head of the linked list, initialized to nullptr
    Node* tail = nullptr; //pointer to the tail of the linked list, initialized to nullptr

    //Prompt user to enter the values for the linked list
    cout << "Enter the values for the linked list: " << endl; 

       //Loop to read 5 values from user input and create nodes for the linked list
       for (int i = 0; i < 5; i++) { 
        Node* newNode = new Node; 

        cin >> newNode->data; //read the value for the new node from user input
        newNode->next = nullptr; //initialize the next pointer of the new node to nullptr because it will be the last node in the linked list

        if (head == nullptr) { //if the linked list is empty, set the head and tail to the new node because it is the first node in the linked list
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode; //if the linked list is not empty, set the next pointer of the tail to the new node and update the tail to the new node
            tail = newNode; //update the tail to the new node
        }
        }

        Node* prev = nullptr; //pointer to the previous node, initialized to nullptr
        Node* current = head; //pointer to the current node, initialized to the head of the linked list

        //Loop to reverse the linked list
        while (current != nullptr) { 
            Node* nextNode = current-> next; //store the next node in a temporary variable
            current->next = prev; //reverse the next pointer of the current node to point to the previous node
            prev = current; //update the previous node to the current node
            current = nextNode; //update the current node to the next node
        }
            //update the head of the linked list to the previous node (which is now the new head of the reversed linked list)
            head = prev;
            cout << "The reversed linked list is: " << endl;

            //loop to traverse the reversed linked list and print the values of the nodes
        Node* temp = head;
        while (temp != nullptr) {
                cout << temp-> data << " ";
                temp = temp-> next;
            }
                
                cout << endl;
                return 0; 
    }
