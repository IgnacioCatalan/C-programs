#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int dado (int caras)
{
    int result=rand()%(caras)+1;
    return result;
}

void lanzamiento(int cantidad, int caras)
{
    int c=1, result, suma=0;
    if (cantidad==1)
        printf("\nSe lanza un dado D%d.\n",caras);
    else
        printf("\nSe lanzan %d dados D%d.\n",cantidad,caras);
    Sleep(300);
    printf(".");
    Sleep(300);
    printf(".");
    Sleep(300);
    printf(".");
    Sleep(300);
    printf("\nResultados:\n");
    while (c<=cantidad)
    {
        result=dado(caras);
        printf("|%d|",result);
        suma=suma+result;
        c++;
    }
    if (cantidad>1)
        printf("\nLa suma es %d",suma);
}

int main()
{
    int caras, cantidad, ver;
    printf("Vamos a rolear!\n");
    while(1)
    {
        srand(time(NULL));
        printf("\nCuantos dados quieres lanzar? ");
        scanf("%d",&cantidad);
        if (cantidad<1)
        {
            printf("\nNo lanzas ningun dado.\n");
        }
        else
        {
            ver=0;
            while (ver==0)
            {
                printf("\nDe cuantas caras (4,6,8,10,12,20)? ");
                scanf("%d",&caras);
                if (caras==4||caras==6||caras==8||caras==10||caras==12||caras==20)
                    ver=1;
                else
                    printf("Selecciona un numero valido.\n");
            }
            lanzamiento(cantidad,caras);
            printf("\n");
        }

    }
    return 0;
}
