#include <stdio.h>
#include <string.h>
#include <windows.h>

int main()
{
    char palabra[5], palabra_original[5];
    strcpy(palabra_original,"hola");
    printf("palabra: ");
    scanf("%s",&palabra);
    if (strcmp(palabra,palabra_original)==0)
        printf("Funciona");
    else
        printf("no son iguales");
    return 0;
}
