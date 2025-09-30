#include <stdlib.h>
#include <ctype.h>
#include "strPtr.h"

int strgLen(const char *s) {
    //checks if s is null
    if (s == NULL){
        return -1;
    }

    //walks through the array, stopping at terminator
    int len = 0;
    while (*s != '\0'){
        len++;
        s++;
    }
    return len;
}

void strgCopy(char *src, char *dest) {
    //checks if either src or dest are null
    if (src == NULL || dest == NULL){
        return; 
    }  

    //moves through s until terminator
    char *d = dest, *s = src;
    while (*s != '\0'){
        //sets d to s 
        *d++ = *s++;
    }
    //end d with a terminator
    *d = '\0';
}

void strgChangeCase(char *s) {
    if (s == NULL){
        return;
    }

    //traverse through string
    for (int i = 0; s[i] != '\0'; i++){
        //check if current char is letter
        if (isalpha(s[i])){
            bool isAdjacentToDigit = 
            (i > 0 && isdigit(s[i-1])) || //checks everything but 1st element 
            (s[i+1] != '\0' && isdigit(s[i+1])); //checks everything but last element

            //toggle case
            if (!isAdjacentToDigit){
                s[i] = islower(s[i]) ? toupper(s[i]) : tolower(s[i]);
            }
        }
    }
}

int strgDiff(char *s1, char *s2) {
    if (s1 == NULL || s2 == NULL){
        return -2;
    }

    for (int i = 0; s1[i] != '\0'; i++){
        if (s1[i] != s2[i]){
            return i;
        }
    }
    return -1;
}

void strgInterleave(char *s1, char *s2, char *d) {
    // TODO: implement
    (void)s1;
    (void)s2;
    (void)d;
}
//your mom
void strgReverseLetters(char *s) {
    if (s == NULL){
        return;
    }

    //fix this dog 
    //only reverses doesnt keep non letters in place
    int left = 0, right = strgLen(s)-1;
    while (left < right){
        if (isdigit(s[left])){
            left++;
        }
        if (isdigit(s[right])){
            right--;
        }
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}



/**
 * Create all test cases inside of the main function below.
 * Run the test cases by first compiling with "make" and then 
 * running "./bin/strPtr"
 * 
 * Before submmiting your assignment, please comment out your 
 * test cases for the TAs. 
 * Comment out if using criterion to test.
 */
int main(int argc, char* argv[]){
	(void)argc;
	(void)argv;
	/** CREATE TEST CASES HERE **/
    char str[] ="";
    strgReverseLetters(str);
    printf("%s\n", str);
    /** ---------------------- **/
	return 0;
}
