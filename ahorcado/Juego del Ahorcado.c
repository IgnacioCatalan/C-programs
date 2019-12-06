//Ignacio Catalán
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "dibujos.h"

#define p 20 //cantidad de palabras
#define t 15 //extensión máxima de cada palabra

int jugadas=0,errores=0,gameover=0,victoria=0,c_l=0;
char letra,letras_ing[27];
char palabras[p][t]={"magia", "musica", "abrazo", "taxi", "malabares", "constante",
                     "tangente", "situacion", "nintendo", "continente", "finlandia",
                     "universidad", "marsupial", "pikachu", "explosion", "aquelarre",
                     "programacion", "extremadamente", "tribulaciones", "yuxtapuesto"};
                     // las palabras se juegan en orden (dificultad creciente)

void palabra_inicial(char p_elegida[t]) //esta función genera un string a partir del array de entrada, el que rellena con guiones, con el mismo largo de la palabra que se está jugando, más adelante los guiones se van reemplazando con las letras correctas que ingresa el usuario.
{
    int i;
    for (i = 0; i <= strlen(palabras[jugadas]); i++)
    {
        if (i == strlen(palabras[jugadas]))
        {
            p_elegida[i] = '\0';
        }
        else
        {
            p_elegida[i] = '-';
        }
    }
}

void interfaz(char p_elegida[t]) //esta función dibuja la pantalla de juego; segun la cantidad de errores que se han cometido, dibuja una parte nueva del ahorcado. También dibuja las pantallas de victoria y de derrota cuando correspondan. El array de entrada lo utiliza para imprimir la palabra con las letras que ya se han revelado.
{
    TituloJuego();
    if (victoria == 1)
    {
        MensajeGanaste();
        gameover = 1;
    }
    else
    {
        if (errores == 0)
        {
            SinAhorcado();
        }
        if (errores == 1)
        {
            Cabeza();
        }
        if (errores == 2)
        {
            Tronco();
        }
        if (errores == 3)
        {
            BrazoIzquierdo();
        }
        if (errores == 4)
        {
            BrazoDerecho();
        }
        if (errores == 5)
        {
            PiernaIzquierda();
        }
        if (errores == 6)
        {
            PiernaDerecha();
        }

        if (errores == 7)
        {
            MensajePerdiste();
            gameover = 1;
        }
        else
        {
            printf("\n PALABRA SECRETA: %s\n",p_elegida);
        }

    }
}

int comprueba_letra() //esta función corrige la letra (que es una variable global) ingresada por el usuario en caso de que sea una mayúscula y/o tenga tildes, luego comprueba si la letra está dentro de la palabra que se está jugando, y retorna este mensaje (verdadero o falso) a la funcion principal.
{
    int correcto = 0,i;

    if (letra==-96||letra==-75||letra==-123||letra==-73||letra==-124||letra==-114)//cada codigo ascii negativo en estos if corresponden a la vocal, tanto mayúscula como minúscula, con diferentes símbolos diacríticos: tildes agudos(´), tildes graves(`) y diéresis(¨).
        letra = 'a';
    if (letra==-126||letra==-112||letra==-118||letra==-44||letra==-119||letra==-45)
        letra = 'e';
    if (letra==-95||letra==-42||letra==-115||letra==-34||letra==-117||letra==-40)
        letra = 'i';
    if (letra==-94||letra==-32||letra==-107||letra==-29||letra==-108||letra==-103)
        letra = 'o';
    if (letra==-93||letra==-23||letra==-105||letra==-21||letra==-127||letra==-102)
        letra = 'u';

    if (letra>=65&&letra<=90||letra==-127||letra==-102)//transforma mayúsculas en minúsculas.
        letra=letra+32;

    for (i=0;i<t;i++)
    {
        if (letra==palabras[jugadas][i])
            correcto=1;
    }

    return correcto;
}

int pozo_letras_ingresadas() //esta funcion agrega a un array todas las letras incorrectas que ha ingresado el usuario, para luego verificar si una letra en particular ya se había ingresado antes o no, si ya está en el array, la función retorna un verdadero, y el programa no vuelve a castigar el error.
{
    int i, repetida=0;
    for (i=0;i<strlen(letras_ing);i++)
        {
            if (letra==letras_ing[i])
            {
                repetida=1;
            }
        }
    if (repetida==0)
        {
            letras_ing[c_l]=letra;
            letras_ing[c_l+1]='\0';
            c_l++;
        }
    return repetida;
}

void ingresa_letra(char p_elegida[t]) //en esta función el usuario ingresa una letra, con esa letra se ejecutan las funciones anteriores, y luego reemplaza los guiones correspondientes en la palabra inicial (la que es un parámetro de entrada)hace  con la letra en cuestión en caso de ser correcta.
{
    int correcto=0,repetida=0,c=0,i;

    printf("\n INGRESA UNA LETRA: ");
    fflush(stdin);
    scanf("%c",&letra);
    correcto=comprueba_letra();
    if (correcto==0)
        repetida=pozo_letras_ingresadas();

    if (letra>=97&&letra<=122&&repetida==0) //solo entra si se ingresó una letra, y si esa letra no se había ingresado antes, no entra con otro tipo de caracter.
    {
        if (correcto==0)
        {
            errores++;
        }
        else
        {
            for(i=0;i<t;i++)
            {
                if (letra==palabras[jugadas][i])
                {
                    p_elegida[i]=letra;
                }
            }
            for(i=0;i<t;i++)
            {
                if (p_elegida[i]!='-')
                {
                    c++;
                }
            }
            if (c==t)
            {
                victoria=1;
            }
        }
    }



}

void juego() //la función principal del juego, ejecuta todas las funciones anteriores, y una vez que el juego termina, reinicializa todas las variables necesarias y pregunta al usuario si quiere volver a jugar, en caso afirmativo, crea una palabra inicial con la siguiente palabra de la matriz.
{
    char p_elegida[t],pregunta;
    int ver=0,continuar=1;

    palabra_inicial(p_elegida);
    while (continuar==1)
    {
        LimpiaPantalla();
        interfaz(p_elegida);
        if (gameover==0)
        {
            ingresa_letra(p_elegida);
        }
        else
        {
            printf("\n\n              LA PALABRA SECRETA ERA: %s\n\n",palabras[jugadas]);
            while (ver==0)
            {
                printf("\n              QUIERES VOLVER A JUGAR?(s/n) ");
                fflush(stdin);
                scanf("%c",&pregunta);
                if (pregunta=='n'||pregunta=='s')
                {
                    ver=1;
                }
            }
            if (pregunta=='n')
                {
                    continuar=0;
                }
            else
            {
                gameover=0;
                errores=0;
                ver=0;
                victoria=0;
                strcpy(letras_ing,"\0");
                c_l=0;
                jugadas++;
                if (jugadas==20)
                {
                    jugadas=0;
                }
                palabra_inicial(p_elegida);
            }
        }
    }

}

int main() //La función main solo ejecuta la funcion juego (la función principal del programa).
{
    juego();
    return 0;
}
