#include <stdio.h>
#include <string.h>
#include <math.h>

void dec2bin (char letter, char binary[8])
{
    int c,aux;
    for(c=0;c<8;c++)
    {
        if (letter%2==1)
            binary[7-c]='1';
        else
            binary[7-c]='0';

        letter=letter/2;
    }
    //printf("\nbinary=%s",binary);
}

char bin2dec (char binary[8])
{
    int letter=0, c;
    for (c=0;c<8;c++)
    {
        if (binary[c]=='1')
            letter=letter+pow(2,(7-c));
    }
    return letter;
}

int main()
{
    char letra, binario[8];
    int opcion,ver;

    while (1)
    {
        strcpy(binario,"00000000");
        ver=0;
        while (ver==0)
        {
            printf("1: transformar de decimal a binario, 2: transformar de binario a decimal: ");
            fflush(stdin);
            scanf("%d",&opcion);
            if (opcion==1||opcion==2)
                ver=1;
            else
                printf("\nIngresa una opcion valida(1 o 2)\n\n");
        }

        if (opcion==1)
        {
            printf("\nIngresa un caracter de la tabla ASCII: ");
            fflush(stdin);
            scanf("%c",&letra);
            dec2bin(letra,binario);
            printf("\nEl caracter \"%c\" (correspondiente al numero %d en la tabla ASCII) en binario es %.*s",letra,letra,8,binario);
        }

        if (opcion==2)
        {
            ver=0;
            while (ver==0)
            {
                printf("\nIngresa un bite en binario (8 digitos): ");
                fflush(stdin);
                scanf("%s",&binario);
                if (strlen(binario)==8)
                    ver=1;
                else
                    printf("\nPor favor ingresa un bite valido (de 8 digitos).\n");
            }
            letra=bin2dec(binario);
            printf("\nEl bite ingresado corresponde al caracter \"%c\" en la tabla ASCII (correspondiente al numero %d).",letra,letra);

        }
        printf("\n\n");
    }

}
