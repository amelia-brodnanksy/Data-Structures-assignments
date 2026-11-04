/* ALGORITHM:
1. If front has reached or passed back, it’s a palindrome. Stop.
2. If the front letter and the back letter are different, it’s not a palindrome. Stop.
3. Otherwise, ask the same question again with front moved one to the right and back moved one to the left.*/

#include <iostream>
#include <cctype> //to make all letters lowercase
using namespace std;

bool isPalindrome(string word, int front, int back) {
        
        if (front>= back) { //step 1: base case: front has reached or passed back
            return true;
        }

    if (word[front] != word[back]) { //step 2: if the front letter and the back letter are different, it’s not a palindrome
        return false;
    }

    return isPalindrome(word, front + 1, back - 1); //step 3: ask the same question again with front moved one to the right and back moved one to the left
}

int main () {

    cout << "Enter word: " << endl; //prompt user to enter a word
    string word;                    //create a variable to store the word entered by the user  
    cin>> word;                     //put the word entered by the user into the variable

    //For edge cases: convert all letters to lowercase to ensure consistent comparison
    for (int i = 0; i < word.length(); i++) {
       word[i] = tolower(word[i]);
    }
    
    bool result = isPalindrome(word, 0, word.length() -1); //call function to check if the word is a palindrome and store the result in the variable 'result'
    
    if (result == true) {                               //if function returns true, the word is a palindrome
      cout << "Yes, the word is a palindrome." << endl; 
    } else{
       cout << "No, the word is not a palindrome." << endl;  //if function returns false, the word is not a palindrome
      }

    return 0;
}