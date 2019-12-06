//Ignacio Catalán, Matías Aguilera
#include <stdio.h>
#include <math.h>
#include "libreria.h"

int cant_m=0;

typedef struct coordenadas{
               int x,y;}
               coord;

char inicio() //Muestra la pantalla de inicio del juego y pregunta la dificultad, almacena la respuesta en una variable y luego la retorna.
{
    int verif=0;
    char dificultad;
    Titulo();
    while (verif==0)
    {
        printf("Ingrese dificultad de la partida (F: facil, M: medio, D:dificil): ");
        fflush(stdin);
        scanf("%c",&dificultad);
        if (dificultad=='f'||dificultad=='F'||dificultad=='m'||dificultad=='M'||dificultad=='d'||dificultad=='D')
            {
                LimpiaPantalla();
                verif=1;
            }
        else
            printf("\nSeleccione una dificultad valida.\n\n");
    }
    return dificultad;
}

int ev_casilla(char tablero[tam][tam], coord casilla) //Utiliza la matriz tablero y las coordenadas de una casilla como parámetros de entrada. Evalúa si la casilla ingresada tiene mina o no, si no tiene, evalúa cuántas hay al rededor y asigna ese numero a la casilla evaluada en la matriz tablero. Retorna una variable que indica si en la casilla hay mina o no.
{
    int hay_mina=0,i,j;
    char cant_mina='0';
    if(tablero[casilla.x][casilla.y]=='*')
    {
        hay_mina=1;
    }
    else
    {
        for(i=casilla.x-1;i<=casilla.x+1;i++)
        {
            for(j=casilla.y-1;j<=casilla.y+1;j++)
            {
                if(tablero[i][j]=='*')
                {
                    cant_mina++;
                }
            }
        }
        tablero[casilla.x][casilla.y]=cant_mina;
    }
    return hay_mina;
}

coord correccion_coordenadas(int x, char y) //Toma como parámetros de entrada dos corrdenadas ingresadas por el usuario. Corrige las coordenadas para que se puedan trabajar como posiciones de la matriz tablero, luego las retorna como una variable de tipo coord.
{
    coord casilla;
    casilla.x = x-1;
    casilla.y = y-97;
    return casilla;
}

int jugada(char tablero[tam][tam],int fin, int minas) //Toma como parámetros de entrada la matriz tablero, la variable fin y la cantidad de minas definidas según la dificultad. La función e ejecuta constantemente, es donde el usuario elije si revelar o marcar una casilla, e ingresa la casilla que quiere. con esta info ejecuta las funciones definidas arriba. También contabiliza cuántas minas se han marcado. Finalmente retorna la variable "fin", la que indica si el juego se acabó o no.
{
    int verif, fila, hay_mina;
    char accion, columna;
    coord casilla;

    verif=0;
    mostrar_tablero(tablero,fin);
    while (verif==0) //para asegurarse que el usuario ingrese M o A solamente.
    {
        printf("\nIngrese M para marcar , A para abrir una casilla :");
        fflush(stdin);
        scanf("%c",&accion);
        if (accion=='m'||accion=='M'||accion=='a'||accion=='A')
            verif=1;
        else
            printf("\nIngrese una opcion valida.\n");
    }
    verif=0;
    while (verif==0) //para asegurarse que el usuario ingrese coordenadas válidas.
    {
        printf("Ingrese coordenada de casilla (ej: 1,a): ");
        fflush(stdin);
        scanf("%d,%c", &fila, &columna);
        if (fila>=0&&fila<=tam && columna>96&&columna<97+tam)
            verif=1;
        else
            printf("\nIngrese coordenadas validas.\n");
    }
    casilla = correccion_coordenadas(fila,columna);
    if (accion=='m'||accion=='M')
    {
        if(tablero[casilla.x][casilla.y]=='*')
        {
            cant_m++;
        }
        tablero[casilla.x][casilla.y]='M';
        if(cant_m==minas)
        {
            fin=1;
        }
    }
    else if (accion=='a'||accion=='A')
    {
        hay_mina = ev_casilla(tablero,casilla);
        if (hay_mina==1 || cant_m==minas)
        {
            fin=1;
        }
    }
    return fin; //fin=1 si el jugador ganó o perdió en esta jugada, fin=2 si sigue jugando.
}

char juego(char continuar) //La función principal del juego, define la dificultad, ejecuta las demás funciones del programa y muestra los mensajes de victoria y derrota. la variable "contianuar" es tanto un parámetro de entrada como de salida.
{
    char dificultad, tablero[tam][tam];
    int minas, fin=2, verif=0, i, j;

    dificultad=inicio();
    if (dificultad=='f'||dificultad=='F') //dificultad facil, aprox. un 10% de las casillas tienen minas.
        minas=pow(tam,2)/10;
    else if (dificultad=='m'||dificultad=='M') //dificultad media, aprox. un 15% de las casillas tienen minas.
        minas=pow(tam,2)*15/100;
    else if (dificultad=='d'||dificultad=='D') //dificultad dificil, aprox. un 20% de las casillas tienen minas.
        minas=pow(tam,2)*20/100;

    construir_tablero(tablero,minas);

    minas=0;
    for (i=0;i<tam;i++) //Como las minas se generan en posiciones aleatorias, es posible que algunas se posicionen donde ya se posicionó otra antes, y como consecuancia quede un numero menor de minas que el que se quería, por eso fue necesario hacer este ciclo for que cuenta la cantidad de minas de nuevo.
    {
        for (j=0;j<tam;j++)
        {
            if (tablero[i][j]=='*')
                minas++;
        }
    }

    while (fin==2)
    {
        LimpiaPantalla();
        fin=jugada(tablero,fin,minas); //se va a ejecutar constantemente hasta que el usuario gane o pierda, en estos dos casos "fin" va a ser igual a 1.
    }
    if (fin==1)
    {
        LimpiaPantalla();
        mostrar_tablero(tablero,fin);
        if(cant_m==minas)
        {
          printf("\nGanaste!!!");
          printf("\nMarcaste correctamente %d minas.",minas);
        }
        else
        {
            printf("\nPerdiste!!!");
            printf("\nAcertaste con %d minas.",cant_m);
        }
        while (verif==0) //Para asegurarse que el usuario ingrese solamente "s" o "n".
        {
            printf("\n\n           Quieres Volver a jugar (s/n)? ");
            fflush(stdin);
            scanf("%c",&continuar);
            if (continuar=='s'||continuar=='n')
                verif=1;
            else
                printf("\n           Ingresa una opcion valida (repsonde con letras en minuscula).");
        }

        if(continuar=='s')
        {
            LimpiaPantalla();
            cant_m=0; //reinicialización de la variable para una nueva partida.
        }
    }
    return continuar;
}

int main() //solamente ejecuta la función "juego", hasta que el usuario decida no seguir jugando.
{
    char continuar='s';
    while (continuar=='s')
    {
       continuar=juego(continuar);
    }
    return 0;
}
