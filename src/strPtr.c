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
//assume dest is large enough
void strgCopy(char *dest, char *src) {
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
    int i = 0;
    while (*s1 != '\0' || *s2 != '\0'){
        if (*s1++ != *s2++){
            return i;
        }
        i++;
    }
    return -1;
}
//assume dest is large enough
void strgInterleave(char *s1, char *s2, char *d) {
    if (s1 == NULL || s2 == NULL || d == NULL){
        return;
    }

    int s1Idx = 0, s2Idx = 0, dIdx = 0;

    //interleave
    while (s1[s1Idx] != '\0' && s2[s2Idx] != '\0'){
        d[dIdx++] = s1[s1Idx++];
        d[dIdx++] = s2[s2Idx++];
    }

    //finish up s1 if applicable
    while (s1[s1Idx] != '\0'){
        d[dIdx++] = s1[s1Idx++];
    }

    //finish up s2 if applicable
    while (s2[s2Idx] != '\0'){
        d[dIdx++] = s2[s2Idx++];
    }

    d[dIdx] = '\0';
}

void strgReverseLetters(char *s) {
    if (s == NULL){
        return;
    }

    //two pointer reverse string
    int left = 0, right = strgLen(s)-1;
    while (left < right){
        //skips a left if digit
        while (left < right && !isalpha(s[left])){
            left++;
        }
        //skips a right if digit
        while (left < right && !isalpha(s[right])){
            right--;
        }
        
        //swaps left and right
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
 **/

 /*
int main(int argc, char* argv[]){
	(void)argc;
	(void)argv;
    char s1[] = "abc";
    char s2[] = "123";
    char d[70];
    strgInterleave(s1, s2, d);
    printf("%s\n", d);
	return 0;
}*/
