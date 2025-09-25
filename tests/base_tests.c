#include <criterion/criterion.h>
#include <string.h>

#include "caesar.h" 
#include "strPtr.h"


/*
 * Part 1: String utility functions
 */

Test(strgLen, basic) {
    cr_assert_eq(strgLen("Stony Brook"), 11);
    cr_assert_eq(strgLen("CSE 220"), 7);
    cr_assert_eq(strgLen("C"), 1);
    cr_assert_eq(strgLen("System Fundamental"), 18);
    cr_assert_eq(strgLen("1"), 1);
    cr_assert_eq(strgLen(""), 0);
}

Test(strgLen, null_input) {
    cr_assert_eq(strgLen(NULL), -1);
}

Test(strgCopy, normal_and_empty) {
    char dest[32] = {0};
    strgCopy(dest, "Computer Science");
    cr_assert_str_eq(dest, "Computer Science");

    dest[0] = '\0';
    strgCopy(dest, "");
    cr_assert_str_eq(dest, "");
}

Test(strgCopy, truncation) {
    char d[5] = {0};
    strgCopy(d, "Computer Science");
    cr_assert_str_eq(d, "Comp");  // 4 chars + '\0'
}

Test(strgCopy, null_args_do_nothing) {
    char dest[16] = "UNCHANGED";
    strgCopy(NULL, "foo");
    cr_assert_str_eq(dest, "UNCHANGED");
    strgCopy(dest, NULL);
    cr_assert_str_eq(dest, "UNCHANGED");
}

Test(strgChangeCase, flip_only_non_adjacent_to_digits) {
    char s1[] = "Stony Brook";
    strgChangeCase(s1);
    cr_assert_str_eq(s1, "sTONY bROOK");

    char s2[] = "CSE220";
    strgChangeCase(s2);
    cr_assert_str_eq(s2, "csE220");

    char s3[] = "a1b";
    strgChangeCase(s3);
    cr_assert_str_eq(s3, "a1b");

    char s4[] = "A9B";
    strgChangeCase(s4);
    cr_assert_str_eq(s4, "A9B");

    char s5[] = "_X_";
    strgChangeCase(s5);
    cr_assert_str_eq(s5, "_x_");
}

Test(strgChangeCase, empty_and_digit_only) {
    char e1[] = "";
    strgChangeCase(e1);
    cr_assert_str_eq(e1, "");

    char e2[] = "1";
    strgChangeCase(e2);
    cr_assert_str_eq(e2, "1");
}

Test(strgDiff, differences_and_equals) {
    cr_assert_eq(strgDiff("Hello","Hello"), -1);
    cr_assert_eq(strgDiff("CSE-220","CSE220"), 3);
    cr_assert_eq(strgDiff("CSE220","SE220"), 0);
    cr_assert_eq(strgDiff("",""), -1);
}

Test(strgDiff, null_inputs) {
    cr_assert_eq(strgDiff(NULL, "foo"), -2);
    cr_assert_eq(strgDiff("foo", NULL), -2);
}

Test(strgInterleave, normal_and_unequal_lengths) {
    char dest[32] = {0};

    strgInterleave("abc","123", dest);
    cr_assert_str_eq(dest, "a1b2c3");

    strgInterleave("abcdef","123", dest);
    cr_assert_str_eq(dest, "a1b2c3def");

    strgInterleave("cse","12345", dest);
    cr_assert_str_eq(dest, "c1s2e345");

    strgInterleave("1234","cs", dest);
    cr_assert_str_eq(dest, "1c2s34");

    strgInterleave("", "", dest);
    cr_assert_str_eq(dest, "");

    strgInterleave("","123", dest);
    cr_assert_str_eq(dest, "123");
}

Test(strgInterleave, truncation) {
    char tiny[5] = {0};
    strgInterleave("abc","123", tiny);
    cr_assert_str_eq(tiny, "a1b2");  // truncated to 4 chars + '\0'
}

Test(strgReverseLetters, basic) {
    char t1[] = "hello";
    strgReverseLetters(t1);
    cr_assert_str_eq(t1, "olleh");

    char t2[] = "hello world";
    strgReverseLetters(t2);
    cr_assert_str_eq(t2, "dlrow olleh");

    char t3[] = "ab-cd";
    strgReverseLetters(t3);
    cr_assert_str_eq(t3, "dc-ba");

    char t4[] = "e1f!";
    strgReverseLetters(t4);
    cr_assert_str_eq(t4, "f1e!");

    char t5[] = "_X_";
    strgReverseLetters(t5);
    cr_assert_str_eq(t5, "_X_");

    char t6[] = "";
    strgReverseLetters(t6);
    cr_assert_str_eq(t6, "");
}

/*
 * Part 2: Position-aware Caesar cipher
 */

/* encryptCaesar tests */


Test(encryptCaesar, basic_shifts) {
    char out[64];

    cr_assert_eq(encryptCaesar("abc",  out, 2), 3);
    cr_assert_str_eq(out, "ceg__EOM__");

    cr_assert_eq(encryptCaesar("Ayb",  out, 3), 3);
    cr_assert_str_eq(out, "Dcg__EOM__");

    cr_assert_eq(encryptCaesar("Cse220", out, 1), 6);
    cr_assert_str_eq(out, "Duh911__EOM__");

    cr_assert_eq(encryptCaesar("CS",   out, 0), 2);
    cr_assert_str_eq(out, "CT__EOM__");

    cr_assert_eq(encryptCaesar("System Fundamentals", out, 1), 18);
    cr_assert_str_eq(out, "Tavxjs Ndxomzscjrdl__EOM__");
}

Test(encryptCaesar, empty_input) {
    char out[32] = {0};
    cr_assert_eq(encryptCaesar("", out, 42), 0);
    cr_assert_str_eq(out, "undefined__EOM__");
}

Test(encryptCaesar, insufficient_space) {
    /* buffer length = 1 (only NUL), always too small */
    char b1[1] = {0};
    cr_assert_eq(encryptCaesar("anything", b1, 5), -1);

    /* buffer length = 4, contains "abc", so strlen=3, still too small for __EOM__ */
    char b2[4] = "abc";
    cr_assert_eq(encryptCaesar("abc", b2, 2), -1);
}

Test(encryptCaesar, null_args) {
    char out[16];
    cr_assert_eq(encryptCaesar(NULL, out, 5), -2);
    cr_assert_eq(encryptCaesar("hi",  NULL, 5), -2);
}

/* decrypt tests */

Test(decryptCaesar, basic_unshifts) {
    char out[64];

    cr_assert_eq(decryptCaesar("ceg__EOM__", out, 2), 3);
    cr_assert_str_eq(out, "abc");

    cr_assert_eq(decryptCaesar("Dcg__EOM__", out, 3), 3);
    cr_assert_str_eq(out, "Ayb");

    cr_assert_eq(decryptCaesar("Duh911__EOM__", out, 1), 6);
    cr_assert_str_eq(out, "Cse220");

    cr_assert_eq(decryptCaesar("CT__EOM__", out, 0), 2);
    cr_assert_str_eq(out, "CS");

    cr_assert_eq(decryptCaesar("Tavxjs Ndxomzscjrdl__EOM__", out, 1), 18);
    cr_assert_str_eq(out, "System Fundamentals");
}

Test(decryptCaesar, empty_input_marker) {
    char out[32];
    cr_assert_eq(decryptCaesar("undefined__EOM__", out, 7), 0);
    cr_assert_str_eq(out, "undefined");
}

Test(decryptCaesar, zero_length_plaintext) {
    /* initial strlen(plaintext)==0 ⇒ return 0, no write */
    char p[1] = "";
    cr_assert_eq(decryptCaesar("ceg__EOM__", p, 2), 0);
    cr_assert_str_eq(p, "");
}

Test(decryptCaesar, missing_marker) {
    /* plaintext must remain unchanged */
    char buf[32];
    strcpy(buf, "no marker here");
    cr_assert_eq(decryptCaesar("no marker here", buf, 1), -1);
    cr_assert_str_eq(buf, "no marker here");
}

Test(decryptCaesar, null_args) {
    char out[16];
    cr_assert_eq(decryptCaesar(NULL, out, 5), -2);
    cr_assert_eq(decryptCaesar("abc__EOM__", NULL, 5), -2);
}

Test(decryptCaesar, truncation_by_strlen) {
    /* initial strlen(plaintext)==4 ⇒ can only store 4 chars + NUL */
    char p[5] = "xxxx";
    int rv = decryptCaesar("Duh911__EOM__", p, 1);
    cr_assert_eq(rv, 6);
    cr_assert_str_eq(p, "Cse2");
}