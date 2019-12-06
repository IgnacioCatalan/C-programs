#include <stdio.h>
#include <stdlib.h>
#define tam 12

char columnas[27] = "abcdefghijklmnopqrstuvwxyz";

void Titulo(void){
    printf("                  \n");
    printf("XXX   X  X  XXXX  XXXX   XXX  XX XX X X   X  XXX  XXXX \n");
    printf("X  X  X  X  XX    XX    X   X X X X X XX  X X   X XX   \n");
    printf("XXX   X  X  XXXX  XX    XXXXX X   X X X X X XXXXX XXXX \n");
    printf("X  X  X  X    XX  XX    X   X X   X X X  XX X   X   XX \n");
    printf("XXX   XXXX  XXXX  XXXX  X   X X   X X X   X X   X XXXX \n");
	printf("\n\n\n");
}

void LimpiaPantalla(void){
    system("clear||cls");
}

void crear_minas(char tablero[tam][tam], int n){
    int i, random, random2;
    srand(1);
    for (i = 0; i < n; i++){
        random = rand() % tam;
        random2 = rand() % tam;
        tablero[random][random2] = '*';
    }
}

void construir_tablero(char tablero[tam][tam], int n){
    int i, j;
    for(i = 0; i < tam; i++)
        for(j = 0; j < tam; j++)
            tablero[i][j] = ' ';
    crear_minas(tablero, n);
}

void mostrar_tablero(char tablero[tam][tam],int fin){
	int i, j;
	printf("   ");
	for(j = 0; j < tam; j++)
		printf("  %c ", columnas[j]);
	printf("\n\n");
	for(i = 0; i < tam; i++){
		printf("%2d ", i+1);
		for(j = 0; j < tam; j++){
            if(fin == 1)
    			printf("| %c ",tablero[i][j]);
            else if(tablero[i][j] != '*')
                printf("| %c ",tablero[i][j]);
            else
                printf("|   ");
		}
		printf("|");
		printf("\n   ");
        for(j = 0; j < tam; j++) printf("----");
        printf("\n");
	}
}

