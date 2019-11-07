#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
int arriba=0, abajo=0;

void sandwitch()
{
    int caida;
    caida=rand()%2;
    if (caida==0)
    {
        printf("El pancito cayo con la palta para arriba %cD\n",58);
        Sleep(500);
        arriba++;
    }
    else
    {
        printf("El pancito cayo con la palta para abajo %cc\n",58);
        Sleep(500);
        abajo++;
    }
    printf("Panes con palta sobrevivientes: %d\n",arriba);
    printf("Panes con palta sacrificados: %d\n\n",abajo);
    Sleep(2000);

}

int main()
{
    srand(time(NULL));
    printf("Este programa lanzara un pan con palta cada 3 segundos, y contara cuantos han caido\ncon la palta para arriba y cuantos con la palta para abajo.\n\n");
    while(1)
    {
        sandwitch();
    }

    return 0;
}
