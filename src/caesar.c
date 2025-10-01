#include <stdlib.h>
#include "caesar.h"
#include "strPtr.h"
#include <string.h>

/**
 *  Feel free to use the functions that you made in strPtr.c
 */

int encryptCaesar(const char *plaintext, char *ciphertext, int key) {
    //null
    if (plaintext == NULL || ciphertext == NULL)    {
        return -2;
    }
    //empty
    if (plaintext[0] == '\0')    {
        const char empty[] = "undefined__EOM__";
        int i;
        for (i = 0; empty[i] != '\0'; i++)        {
            ciphertext[i] = empty[i];
        }
        ciphertext[i] = '\0';
        return 0;
    }

    int i = 0;
    int skipped = 0;
    for (i = 0; plaintext[i] != '\0'; i++)    {
        char c = plaintext[i];

        if (isupper(c)){ //uppercase
            int shift = (key + i) % 26;
            ciphertext[i] = ((c - 'A' + shift) % 26) + 'A';
        }else if (islower(c)){//lowercase
            int shift = (key + i) % 26;
            ciphertext[i] = ((c - 'a' + shift) % 26) + 'a';
        }else if (isdigit(c)){ //digit
            int shift = (key + 2*i) % 10;
            ciphertext[i] = ((c - '0' + shift) % 10) + '0';
        }else{ //non-ascii
            ciphertext[i] = c;
            skipped++;
        }
    }

    //add eom marker
int encodedCount = i - skipped;
    const char *eom = "__EOM__";
    while (*eom != '\0')    {
        ciphertext[i++] = *eom++;
    }
    ciphertext[i] = '\0';
    return encodedCount;
}

int decryptCaesar(const char *ciphertext, char *plaintext, int key) {
    //null check
    if (ciphertext == NULL || plaintext == NULL){
        return -2;
    }

    //missing marker check
    const char marker[] = "__EOM__";
    const char *pos = strstr(ciphertext, marker);
    if (pos == NULL){
        return -1;
    }

    //empty input marker check
    const char empty[] = "undefined__EOM__";
    if (strcmp(ciphertext, empty) == 0){
        const char *undef = "undefined";
        int i = 0;
        while (*undef != '\0'){
            plaintext[i++] = *undef++;
        }
        plaintext[i] = '\0';
        return 0;
    }

    //zero length plaintext check
    int cap = strgLen(plaintext);
    if (cap == 0){
        return 0;
    }

    int i = 0;
    int skipped = 0;
    for (i = 0; i < pos - ciphertext; i++){
        char c = ciphertext[i];

        if (c == '_' && strncmp(&ciphertext[i], "__EOM__", 7) == 0){
            break;
        }

        if (isupper(c)){ //uppercase
            int shift = (key + i) % 26;
            plaintext[i] = ((c - 'A' - shift + 26) % 26) + 'A';
        }else if (islower(c)){ //lowercase
            int shift = (key + i) % 26;
            plaintext[i] = ((c - 'a' - shift + 26) % 26) + 'a';
        }else if (isdigit(c)){ //digit
            int shift = (key + 2*i) % 10;
            plaintext[i] = ((c - '0' - shift + 10) % 10) + '0';
        }else{ //non-ascii
            plaintext[i] = c;
            skipped++;
        }
    }

    plaintext[i] = '\0';
    return i - skipped;
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
