/*Write a program to remove duplicates from the following linked list.
test values: 9 8 9 8 8 10 11 */

#include <iostream>
using namespace std;

//Define a structure for the linked list node, which contains an integer value and a pointer to the next node. 
struct Node {
	int value;
	Node* next;

    //Constructor to initialize the node with a value and an optional next pointer (default is nullptr)
	Node(int value, Node* next = nullptr) : value(value), next(next) {}
};

//Function to remove duplicates from the linked list. It takes a pointer to the head of the list as an argument.
void removeDuplicates(Node* head) {
	for (Node* current = head; current != nullptr; current = current->next) {
		Node* previous = current;
		Node* runner = current->next;

        //Inner loop to check for duplicates of the current node's value in the rest of the list
		while (runner != nullptr) {
			if (runner->value == current->value) {
				previous->next = runner->next;
				delete runner;
				runner = previous->next;
			} else { //If the value is not a duplicate, move the preivious and runner pointers forward to continue checking the rest of the list
				previous = runner;
				runner = runner->next;
			}
		}
	}
}

//Function to print the values of the linked list.
void printList(const Node* head) {
	while (head != nullptr) {
		cout << head->value;
		if (head->next != nullptr) {
			cout << " ";
		}
		head = head->next;
	}
	cout << endl;
}

//Function to delete the entire linked list and free the allocated memory.
void deleteList(Node* head) {
	while (head != nullptr) {
		Node* next = head->next;
		delete head;
		head = next;
	}
}

int main() {

    //Prompt the user to enter the number of values they will input for the linked list.
	int numberOfValues;
	cout << "How many values will you enter? ";
	cin >> numberOfValues;

    //Check if the number of values is negative and display an error message if it is.
	if (numberOfValues < 0) {
		cout << "The number of values cannot be negative." << endl;
		return 1;
	}

    //Initialize pointers for the head and tail of the linked list.
	Node* head = nullptr;
	Node* tail = nullptr;

    //Prompt the user to enter the values for the linked list and create nodes for each value, linking them together. 
	cout << "Enter the values: ";
	for (int index = 0; index < numberOfValues; ++index) {
		int value;
		cin >> value;

        //Create a new node with the entered value and add it to the linked list.
		Node* newNode = new Node(value);
		if (head == nullptr) { //If the list is empty, set the head and tail to the new node. 
			head = newNode;
			tail = newNode;
		} else { //If the list is not empty, link the new node to the end of the list and update the tail pointer.
			tail->next = newNode;
			tail = newNode;
		}
	}

    //Call the removeDuplicates function to remove any duplicate values from the linked list.
	removeDuplicates(head);

    //Print the linked list after removing duplicates.
	cout << "List without duplicates: ";
	printList(head);

    //Delete the linked list to free the allocated memory and prevent memory leaks.
	deleteList(head);
	return 0;
}