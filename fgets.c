#include <stdio.h>
#include <string.h>

int main() {
    char string[100];

    printf("Enter a string: ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';  // Remove trailing newline

    int length = strlen(string);

    printf("The length of the string is: %d\n", length);

    return 0;
}
