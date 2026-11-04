/* Write a program to sort the following unsorted integer array:
4 8 2 26 33 1 5 8 7 3 */

#include <iostream> //Include the iostream library to use input and output functions
using namespace std; //Use the standard namespace to avoid prefixing std:: before standard functions

int main (int argc, char *argv[]) {

//Define the size of the array and delcare the array. The size of they array is 10 since we are sorting 10 integers.
    const int SIZE = 10;
    int unsortedArray[SIZE];

    //Prompt the user to enter 10 integers to sort
    cout << "Enter 10 integers to sort: " << endl;

    //Read the integers from the user and store them in the array
    for (int i= 0; i < SIZE; i++) {
        cin >> unsortedArray[i];
    }

    //Sort array using bubble sort algorithm
    for (int i=0; i < SIZE -1; i++) { //Outer loop to iterate through the array SIZE - 1 times
        for (int j = 0; j < SIZE -1 - i; j++) { //Inner loop to compare adjacent elements and swap them if they are in the wrong order
            if (unsortedArray[j] > unsortedArray[j+1]) { //If the current element is greater than the next element, swap them
                int temporary = unsortedArray[j]; //Store the current element in a temporary variable
                unsortedArray[j] = unsortedArray [j+1]; //Assign the next element to the current element
                unsortedArray[j+1] = temporary; //Assign the temporary variable (which holds the current element) to the next element
    
            }
        }
    }
    
    cout << "Sorted array: " << endl; //Print the sorted array

    for (int i = 0; i < SIZE; i++) { //Loop through the sorted array and print each element
        cout << unsortedArray[i] << " "; //Print the current element folowed by a space
    }
    cout << endl;
    return 0;
}