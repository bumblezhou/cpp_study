/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int is_palindrome(const char* str, int size) {
    int mid = size / 2;
    int i, result = 0;
    for (i = 0; i <= mid; i++) {
        if(str[i] != str[size - 1 - i]) {
            result = 1;
            break;
        }
    }
    return result;
}

int index_of(const char* str, int size, const char c) {
    int result = -1, i;
    for(i = 0; i < size; i++) {
        if (c == str[i]) {
            result = i;
            break;
        }
    }
    return result;
}

int is_mirrored_palindrome(const char* str, int size) {
    char symmetric[11] = { 'A', 'H', 'I', 'M', 'O', 'T', 'U', 'V', 'W', 'X', 'Y' };
    int mid = size / 2;
    int i, result = 0;
    for (i = 0; i <= mid; i++) {
        if(str[i] != str[size - 1 - i] || index_of(str, size, str[i]) < 0) {
            result = 1;
            break;
        }
    }
    return result;
}

int main()
{
    char test_a[8] = {"ATOYOTA"};
    int palindrome_judge = is_palindrome(test_a, 7);
    int mirrored_palindrome_judge = is_mirrored_palindrome(test_a, 7);
    if (palindrome_judge == 0) {
        printf("%s is a palindrome.\n", test_a);
    }
    if (mirrored_palindrome_judge == 0) {
        printf("%s is a mirrored palindrome.\n", test_a);
    }
    
    char test_b[12] = {"NORMALTEXT"};
    palindrome_judge = is_palindrome(test_b, 11);
    mirrored_palindrome_judge = is_mirrored_palindrome(test_b, 11);
    if (palindrome_judge == 0) {
        printf("%s is a palindrome.\n", test_b);
    }
    if (mirrored_palindrome_judge == 0) {
        printf("%s is a mirrored palindrome.\n", test_b);
    }
    
    char test_c[6] = {"TENET"};
    palindrome_judge = is_palindrome(test_c, 5);
    mirrored_palindrome_judge = is_mirrored_palindrome(test_c, 5);
    if (palindrome_judge == 0) {
        printf("%s is a palindrome.\n", test_c);
    }
    if (mirrored_palindrome_judge == 0) {
        printf("%s is a mirrored palindrome.\n", test_c);
    }
    
    return 0;
}
