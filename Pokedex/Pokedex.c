//Creado por Ignacio Catalán
#include <stdio.h>
#include <string.h>
#define n 15 //largo de nombres
#define t 18 //cantidad de tipos
#define p 151 //tamaño de la pokedex

typedef struct informacion{ /*peso, estatura, nombre, tipos y especie del pokemon.*/
               float wt, ht;
               char name[n], type1[n], type2[n], species[n];}
               info;

typedef struct type_relations{ /*ventajas y desventajas del pokemon segun sus tipos.*/
               char res[50], sres[50], inm[50], wk[50], swk[50];}
               adv;

typedef struct estadisticas_base{ /*valores de todas las estadisticas base del pokemon.*/
               int ps, atk, def, spatk, spdef, spd;}
               stats;

typedef struct aporte_EVs{ /*valores de todos los puntos de EV que aporta el pokemon al ser vencido en batalla.*/
               int ps, atk, def, spatk, spdef, spd;}
               evs;

typedef struct pokemon{ /*toda la informacion del pokemon dada por las estructuras anteriores, más su numero de pokedex.*/
               int number;
               info info;
               stats stats;
               evs evs;
               adv adv;}
               pkmn;

void show_pkmn(pkmn pokemon) //Formato de impresión de la información, usando como parametro de entrada el pokemon elegido.
{
    printf("\n =============");
    printf("\n Pokedex n%c%.3d",-8, pokemon.number);
    printf("\n =============");
    printf("\n Nombre  : %s", pokemon.info.name);
    printf("\n Especie : Pokemon %s", pokemon.info.species);
    printf("\n Tipo    : %s", pokemon.info.type1);
    printf(" %s",pokemon.info.type2);
    printf("\n Estatura: %.1f m", pokemon.info.ht);
    printf("\n Peso    : %.1f Kg", pokemon.info.wt);

    printf("\n\n VENTAJAS Y DESVENTAJAS DE TIPOS");
    if (strcmp(pokemon.adv.res,"\0")!=0)
        printf("\n  Resistente a    : %s", pokemon.adv.res);
    if (strcmp(pokemon.adv.wk,"\0")!=0)
        printf("\n  Debil a         : %s", pokemon.adv.wk);
    if (strcmp(pokemon.adv.sres,"\0")!=0)
        printf("\n  Muy resistente a: %s", pokemon.adv.sres);
    if (strcmp(pokemon.adv.swk,"\0")!=0)
        printf("\n  Muy debil a     : %s", pokemon.adv.swk);
    if (strcmp(pokemon.adv.inm,"\0")!=0)
        printf("\n  Inmune a        : %s", pokemon.adv.inm);

    printf("\n\n ESTADISTICAS BASE           APORTE DE EVs");
    printf("\n  Puntos de Salud:%3d         Puntos de Salud:%2d", pokemon.stats.ps, pokemon.evs.ps);
    printf("\n  Ataque         :%3d         Ataque         :%2d", pokemon.stats.atk, pokemon.evs.atk);
    printf("\n  Defensa        :%3d         Defensa        :%2d", pokemon.stats.def, pokemon.evs.def);
    printf("\n  Ataque esp.    :%3d         Ataque esp.    :%2d", pokemon.stats.spatk, pokemon.evs.spatk);
    printf("\n  Defensa esp.   :%3d         Defensa esp.   :%2d", pokemon.stats.spdef, pokemon.evs.spdef);
    printf("\n  Velocidad      :%3d         Velocidad      :%2d", pokemon.stats.spd, pokemon.evs.spd);
}

void data_f(pkmn lista[p]) //Extrae toda la información del archivo "pokedex.txt" para almacenarla en las variables correspondientes de cada pokemon almacenado en el array "lista".
{
    FILE *fp=NULL;
    char *path="pokedex.txt";
    int i;

    fp=fopen(path,"r");

    if (fp==NULL){
        printf("\nERROR: NO SE PUDO LEER EL ARCHIVO.\n\n");
    }
    else
    {
        for(i==0;i<p;i++)
        {
            lista[i].number=i+1;
            fscanf(fp," %[^,]",&lista[i].info.name);
            fseek(fp,1,SEEK_CUR);
            fscanf(fp," %[^,]",&lista[i].info.species);
            fseek(fp,1,SEEK_CUR);
            fscanf(fp," %[^.]",&lista[i].info.type1);
            fseek(fp,1,SEEK_CUR);
            strcpy(lista[i].info.type2,"\0");
            fscanf(fp," %[^.]",&lista[i].info.type2);
            fseek(fp,1,SEEK_CUR);
            fscanf(fp,"%f",&lista[i].info.ht);
            fscanf(fp,"%f",&lista[i].info.wt);
            fscanf(fp,"%d",&lista[i].stats.ps);
            fscanf(fp,"%d",&lista[i].stats.atk);
            fscanf(fp,"%d",&lista[i].stats.def);
            fscanf(fp,"%d",&lista[i].stats.spatk);
            fscanf(fp,"%d",&lista[i].stats.spdef);
            fscanf(fp,"%d",&lista[i].stats.spd);
            fscanf(fp,"%d",&lista[i].evs.ps);
            fscanf(fp,"%d",&lista[i].evs.atk);
            fscanf(fp,"%d",&lista[i].evs.def);
            fscanf(fp,"%d",&lista[i].evs.spatk);
            fscanf(fp,"%d",&lista[i].evs.spdef);
            fscanf(fp,"%d",&lista[i].evs.spd);
        }
    }
    fclose(fp);
    lista[51].info.species[8]=-92; //correccion para agregar la ñ en algunas variables.
    lista[78].info.species[6]=-92;
    lista[105].info.species[2]=-92;
}

pkmn data_tp_relations(pkmn pokemon) //Calcula las ventajas y desventajas del pokemon elegido (parámetro de entrada) para almacenarlos en sus respectivas variables.
{
    int j, i, type1_ev=18, type2_ev=18;
    float mult=1;
    char types[t][n]={"Normal","Fuego","Agua","Electrico","Planta","Hielo","Lucha","Veneno","Tierra","Volador","Psiquico","Bicho","Roca","Fantasma","Dragon","Siniestro","Acero","Hada"};
    float adv[t][t+1]={1,1,1,1,1,1,1,1,1,1,1,1,.5,0,1,1,.5,1,1,
                     1,.5,.5,1,2,2,1,1,1,1,1,2,.5,1,.5,1,2,1,1,
                     1,2,.5,1,.5,1,1,1,2,1,1,1,2,1,.5,1,1,1,1,
                     1,1,2,.5,.5,1,1,1,0,2,1,1,1,1,.5,1,1,1,1,
                     1,.5,2,1,.5,1,1,.5,2,.5,1,.5,2,1,.5,1,.5,1,1,
                     1,.5,.5,1,2,.5,1,1,2,2,1,1,1,1,2,1,.5,1,1,
                     2,1,1,1,1,2,1,.5,1,.5,.5,.5,2,0,1,2,2,.5,1,
                     1,1,1,1,2,1,1,.5,.5,1,1,1,.5,.5,1,1,0,2,1,
                     1,2,1,2,.5,1,1,2,1,0,1,.5,2,1,1,1,2,1,1,
                     1,1,1,.5,2,1,2,1,1,1,1,2,.5,1,1,1,.5,1,1,
                     1,1,1,1,1,1,2,2,1,1,.5,1,1,1,1,0,.5,1,1,
                     1,.5,1,1,2,1,.5,.5,1,.5,2,1,1,.5,1,2,.5,.5,1,
                     1,2,1,1,1,2,.5,1,.5,2,1,2,1,1,1,1,.5,1,1,
                     0,1,1,1,1,1,1,1,1,1,2,1,1,2,1,.5,1,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,.5,0,1,
                     1,1,1,1,1,1,.5,1,1,1,2,1,1,2,1,.5,1,.5,1,
                     1,.5,.5,.5,1,2,1,1,1,1,1,1,2,1,1,1,.5,2,1,
                     1,.5,1,1,1,1,2,.5,1,1,1,1,1,1,2,2,.5,1,1};


    strcpy(pokemon.adv.res,"\0");
    strcpy(pokemon.adv.sres,"\0");
    strcpy(pokemon.adv.inm,"\0");
    strcpy(pokemon.adv.wk,"\0");
    strcpy(pokemon.adv.swk,"\0");

    for (i=0;i<t;i++)
    {
        if (strcmp(types[i],pokemon.info.type1)==0)
            type1_ev=i;
        if (strcmp(types[i],pokemon.info.type2)==0)
            type2_ev=i;
    }
    for (i=0;i<t;i++)
    {
        mult=mult*adv[i][type1_ev];
        mult=mult*adv[i][type2_ev];

        if (mult==0.5)
        {
            strcat(pokemon.adv.res,types[i]);
            strcat(pokemon.adv.res," ");
        }

        if (mult==0.25)
        {
            strcat(pokemon.adv.sres,types[i]);
            strcat(pokemon.adv.sres," ");
        }

        if (mult==0)
        {
            strcat(pokemon.adv.inm,types[i]);
            strcat(pokemon.adv.inm," ");
        }

        if (mult==2)
        {
            strcat(pokemon.adv.wk,types[i]);
            strcat(pokemon.adv.wk," ");
        }

        if (mult==4)
        {
            strcat(pokemon.adv.swk,types[i]);
            strcat(pokemon.adv.swk," ");
        }
        mult=1;
    }

    return pokemon;
}

void upper_correction(char name[n]) //corrige el nombre ingresado por el usuario, dejando el primer caracter en mayuscula y el resto en minuscula, para que pueda ser reconocido por el programa.
{
    int i;
    if (name[0]<123&&name[0]>96){
        name[0]=name[0]-32;}
    for (i=1;i<strlen(name);i++)
    {
        if (name[i]<91&&name[i]>64){
            name[i]=name[i]+32;}
    }
}

int seek_alike(char name[n], pkmn lista[p]) //En caso de que el nombre ingresado por el usuario no coincida con ninguno de los pokemon, esta funcion busca el nombre más cercano para entregarlo como sugerencia, retorna un verdadero si se encontró una posible sugerencia, y un falso si es que no se encontró.
{
    int matches=0,last_match=0, i, j, found=0,suggest;

    for (i=0;i<p;i++)
    {
        for (j=0;j<strlen(name);j++)
        {
            if (name[j]==lista[i].info.name[j-1] || name[j]==lista[i].info.name[j] || name[j]==lista[i].info.name[j+1]){
                matches++;}
        }
        if (matches>last_match){
            last_match=matches;
            suggest=i;}
        matches=0;
    }
    if (last_match>=strlen(lista[suggest].info.name)/2){
        strcpy(name,lista[suggest].info.name);
        found=1;}
    return found;
}

int selection_name(pkmn lista[p]) //Permite buscar un pokemon por su nombre, cuando el usuario elije esta opción, retorna el pokemon encontrado como una posición en el array "lista".
{
    int poke=p+1,i, found, copia;
    char name[n];
    printf("\nEscribe el nombre del pokemon quieres buscar: ");
    fflush(stdin);
    scanf("%[^\n]",&name);
    upper_correction(name);
    for (i=0;i<p;i++)
    {
        if (strcmp(name,lista[i].info.name)==0)
        {
            poke=i;
        }
    }
    if (poke==p+1)
    {
        found=seek_alike(name,lista); //Si es que no se encontró el nombre ingresado por el usuario, se ejecuta esta funcion para buscar el más parecido.
        if (found){
            printf("\nNo se pudo encontrar tu pokemon, quzas quisiste decir \"%s\".",name);}
        else{
            printf("\nNo se pudo encontrar tu pokemon, comprueba que escribiste bien su nombre.");}

    }
    return poke;
}

int selection_num(pkmn lista[p])//Permite buscar un pokemon por su número de pokedex, cuando el usuario elije esta opción, retorna el pokemon encontrado como una posición en el array "lista".
{
    int poke,i;
    printf("\nEscribe el numero del pokemon quieres buscar: ");
    fflush(stdin);
    scanf("%d",&poke);
    poke--;
    if (poke<1||poke>p){
        printf("\nNo se pudo encontrar tu pokemon, selecciona un numero entre 1 y %d.",p);}
    return poke;
}

void show_all(pkmn lista[p]) //imprime todos los pokemon de la pokedex.
{
    int i;
    for(i=0;i<p;i++)
    {
        lista[i]=data_tp_relations(lista[i]);
        show_pkmn(lista[i]);
        printf("\n");
    }
}

int main() //Funcion principal del programa, recoje toda la informácion de los pokemon, entrega al usuario 3 métodos de búsqueda diferentes y ejecuta la opción elegida.
{
    pkmn lista[p];
    int sear,ver,election=p+1;

    data_f(lista);
    printf("Bienvenido a la Pokedex, puedes buscar cualquier pokemon de la primera generacion (del n%c1 al n%c%d) \na traves de su nombre o su numero de pokedex.",-8,-8,p);
    while (1)
    {
        ver=0;
        while (ver==0)
        {
            printf("\n\nTipo de busqueda (1: por nombre, 2: por numero de pokedex, 3: mostrar toda la Pokedex): ");
            fflush(stdin);
            scanf("%d",&sear);
            if (sear==1||sear==2||sear==3){
                ver=1;}
            else{
                printf("\nSelecciona una opcion valida (ingresa \"1\" o \"2\" o \"3\").");}
        }
        if (sear==1){
            election=selection_name(lista);}
        else if(sear==2){
            election=selection_num(lista);}
        else if (sear==3){
            election=p+1;
            show_all(lista);}

        if (election>=0&&election<p){
            lista[election]=data_tp_relations(lista[election]);
            show_pkmn(lista[election]);}
        printf("\n");
    }
    return 0;
}
