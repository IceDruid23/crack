#include <stdio.h>
#include <ctype.h>
int main()
{
    char c;
    c = '!';
    printf("\nResult when uppercase alphabet is passed: %d", isalpha(c));

    c = '1';
    printf("\nResult when lowercase alphabet is passed: %d", isalpha(c));

    c='c';
    printf("\nResult when non-alphabetic character is passed: %d", isalpha(c));

    return 0;
}
