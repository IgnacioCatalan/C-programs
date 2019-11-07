#include <stdio.h>

int main()
{
    char car;
    printf("caracter: ");
    fflush(stdin);
    scanf("%c",&car);
    printf("\nASCII: %d",car);
    return 0;
}
