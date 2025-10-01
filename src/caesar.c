#include <stdlib.h>
#include "caesar.h" 
#include "strPtr.h"
#include <string.h>

/**
 *  Feel free to use the functions that you made in strPtr.c
*/ 

int encryptCaesar(const char *plaintext, char *ciphertext, int key) {
    if (plaintext == NULL || ciphertext == NULL){
        return -2;
    }

    int i = 0;
    int skipped = 0;
    for (i = 0; plaintext[i] != '\0'; i++){
        char c = plaintext[i];

        if (isupper(c)){
            int shift = (key + i) % 26;
            ciphertext[i] = ((c - 'A' + shift) % 26) + 'A';
        }else if (islower(c)){
            int shift = (key + i) % 26;
            ciphertext[i] = ((c - 'a' + shift) % 26) + 'a';
        }else if (isdigit(c)){
            int shift = (key + 2*i) % 10;
            ciphertext[i] = ((c - '0' + shift) % 10) + '0';
        }else{
            ciphertext[i] = c;
            skipped++;
        }
    }
    int encodedCount = i - skipped;
    char eom[] = "__EOM__";
    char *eom_ptr = eom;
    while (*eom_ptr != '\0'){
        ciphertext[i++] = *eom_ptr++; 
    }
    ciphertext[i] = '\0';
    return encodedCount;
}

int decryptCaesar(const char *ciphertext, char *plaintext, int key) {
	(void)ciphertext;
    (void)plaintext;
    (void)key;
    return 0;
}


/**
 * Create all test cases inside of the main function below.
 * Run the test cases by first compiling with "make" and then 
 * running "./bin/caesar"
 * 
 * Before submmiting your assignment, please comment out your 
 * test cases for the TAs. 
 * Comment out if using criterion to test.
 */

 /*
int main(int argc, char* argv[]){
	(void)argc;
	(void)argv;
    char plaintext[] = "System Fundamentals";
    char ciphertext[100];
    int e = encryptCaesar(plaintext, ciphertext, 1);
    printf("%s\n%d\n%d\n", ciphertext, e, strgLen(plaintext));
	return 0;
}
    */
