/* Write a program to find the k’th larger element in the following unsorted array.
4 8 2 26 33 1 5 8 7 3  */

#include <iostream> //Include the iostream library to use input and output functions
using namespace std; //Use the standard namespace to avoid prefixing std:: before standard functions

int main (int argc, char *argv[]) {

    //Define the size of the array and declare the array. The size of the array is 10 since we are sorting 1o integers.
    const int SIZE = 10;
    int unsortedArray[SIZE] {4, 8, 2, 26, 33, 1, 5, 8, 7, 3}; //Initialize the array with the given unsorted integers

    //Prompt the user to enter the value of k to find the k'th largest element in the array
    cout << "Enter k: " << endl;
    int k; //Declare a variable to store the value of k
    cin >> k; //Read the value of k from the user

    if (k < 1 || k > SIZE) { //Check if the value of k is valid (between 1 and SIZE)
        cout << "Invalid value of k. Please enter a value between 1 and " << SIZE << "." << endl; //Print an error message if k is invalid
        return 1; //Return 1 to indicate an error;
    }

    //Sort the array in descending order using bubble sort algorithm
    for (int pass = 0; pass < SIZE -1; pass++) { //Outer Loop to iterate through the array SIZE - 1 times
        for (int index = 0; index < SIZE -1 - pass; index++) { //Inner loop to compare adjacent elements and swap them if they are in the wrong order
            if (unsortedArray[index] < unsortedArray[index + 1]) { //If the current elent is less than the next element, swap them
                int temporary = unsortedArray[index]; //Store the current element in a temporary variable
                unsortedArray[index] = unsortedArray[index + 1]; //Assign the next element to the current element
                unsortedArray[index + 1] = temporary; //Assign the temporary variable (which holds the current element) to the next element
            }
        }
    }

    //Display the k'th largest element
    cout << "The " << k << "'th largest element is: " << unsortedArray[k - 1] << endl;

    return 0;
}