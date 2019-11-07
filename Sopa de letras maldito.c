#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define t 16
int main()
{
    srand(time(NULL));
    char draw[t][t];
    int i,j,c,palabra,hor_ver,cerrar;
    printf("                 Sopa de Letras Maldito\n");
    printf("                 ======================\n");
    for (i=0;i<t;i++)
    {
        printf("\n            ");
        for (j=0;j<t;j++)
        {
            printf("%2c",draw[i][j]=(rand()%26)+65);
        }
    }
    printf("\n\n");
    printf("               Intenta encontrar: ");

    for(c=0;c<3;c++)
    {
        palabra=rand()%9;
        i=rand()%16;
        hor_ver=rand()%2;
        for (j=palabra;j<(palabra+8);j++)
            {
                if(hor_ver==0)
                    printf("%c",draw[i][j]);
                else
                    printf("%c",draw[j][i]);
            }
        printf("\n                                  ");
    }
    printf("\n       (podrian estar en horizontal o en vertical).\n");
    printf("");
    scanf("%d",&cerrar);
    return 0;
}
