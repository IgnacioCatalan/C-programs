#include <stdio.h>

int main()
{
    int fila;
    int columna;
    char letra;

    printf("Ingrese coordenada de casilla (ej: 1,a): ");
    scanf("%d,%c", &fila, &letra);

    fila--;
    /* Al restarle 1 a la fila que ingresa el usuario, te permite usar esta variable "fila" para acceder a la posición correcta dentro del tablero. */

    columna = letra - 97;
    /*el ASCII de la 'a' es 97. Al restar 97 a la letra ingresada, entonces "columna" queda como 0.
    Recuerda que los ASCII de las letras son consecutivos, entonces si el usuario ingresa 'b', se almancena un 98, y al restar 97, queda como 1...
    ...para la 'c', queda almacenado un 2, .... y así susecuvamente.
    Con esto, puedes usar esta variable "columna" para acceder a la posición correcta dentro del tablero. */

    printf("\nLa fila es: %d", fila);
    printf("\nLa columna es: %d", columna);

    printf("\n\n");

    return 0;
}
