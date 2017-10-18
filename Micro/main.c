#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMFILA 17
#define TAMCOLUMNA 13

typedef enum {INICIO=1,FIN,LEER,ESCRIBIR,ID,CONSTANTE,PARENIZQUIERDO,PARENDERECHO,PUNTOYCOMA,COMA,ASIGNACION,SUMA,RESTA,FDT,ERROR}TOKEN;
int cursor=0;

struct simbolo
{
    char palabra[32];
    TOKEN token;
};

struct simbolo tablaSimbolos[1000];

void inicializarTablaSimbolos()
{
    int c=0;
    struct simbolo vacio;
    struct simbolo inicio;
    struct simbolo fin;
    struct simbolo escribir;
    struct simbolo leer;
    vacio.token=-1;
    while (c<1000)
    {
        tablaSimbolos[c]=vacio;
        c++;
    }
    strcpy(inicio.palabra,"inicio");
    inicio.token=INICIO;
    tablaSimbolos[0]=inicio;

    strcpy(fin.palabra,"fin");
    fin.token=FIN;
    tablaSimbolos[1]=fin;

    strcpy(escribir.palabra,"escribir");
    escribir.token=ESCRIBIR;
    tablaSimbolos[2]=escribir;

    strcpy(leer.palabra,"leer");
    leer.token=LEER;
    tablaSimbolos[3]=leer;
    return;
}

void agregarATablaSimbolos(char *palabra)
{
    int c=0;
    struct simbolo nuevoId;
    nuevoId.token=ID;
    strcpy(nuevoId.palabra,palabra);
    while(tablaSimbolos[c].token!=-1) c++;
    tablaSimbolos[c]=nuevoId;
    return;

}

/*void pasarAMayuscula(char *palabra)
{
    int c=0;
    if (palabra[c]>='a' && palabra[c]<='z')
    {
    while(palabra[c])
    {
        palabra[c]=palabra[c]-32;
        c++;
    }
    }
    return;
}*/

int esPalabraReservada(char palabra[])
{
    int c=0;
    while (strcmp(palabra,tablaSimbolos[c].palabra)&& c<=4)
    {
        c++;
    }
    if (c>4) return 0;
    else return 1;
}

TOKEN devolverPalabraReservada(char palabra[])
{

    if (strcmp(palabra,"leer")==0)
        return LEER;

    if (strcmp(palabra,"escribir")==0)
        return ESCRIBIR;

    if (strcmp(palabra,"inicio")==0)
        return INICIO;

    if (strcmp(palabra,"fin")==0)
        return FIN;

}

int estadoSiguiente(int fila,int columna)
{
    int matriz [TAMFILA][TAMCOLUMNA]={
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 0*/
                        {1,1,10,10,10,10,10,10,10,10,10,10,13},/*FILA 1*/
                        {13,2,14,14,14,14,14,14,14,14,14,14,13},/*FILA 2*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 3*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 4*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 5*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 6*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 7*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 8*/
                        {11,11,11,11,11,11,11,11,11,12,11,11,11},/*FILA 9*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 10*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 11*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 12*/
                        {13,13,16,16,16,16,16,16,16,16,16,16,13},/*FILA 13*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13},/*FILA 14*/
                        {15,15,15,15,15,15,15,15,15,15,15,15,15},/*FILA 15*/
                        {1,2,3,4,5,6,7,8,9,11,15,0,13}/*FILA 16*/
                        };

      return matriz[fila][columna];
}

int columna(int caracter)
{
    if (caracter>='a'&& caracter<='z' || caracter>='A' && caracter<='Z')
        return 0;
    if (caracter>='0' && caracter<='9')
        return 1;
    switch(caracter)
    {
        case '+':return 2;
        case '-':return 3;
        case '(':return 4;
        case ')':return 5;
        case ',':return 6;
        case ';':return 7;
        case ':':return 8;
        case '=':return 9;
        case EOF:return 10;
        case '\r':return 11;
        case '\n':return 11;
        case ' ':return 11;
        default: return 12;

    }
}

TOKEN tokens (int estado,char palabra[])
{

    switch (estado)
    {
        case 3:return SUMA;
        case 4:return RESTA;
        case 5:return PARENIZQUIERDO;
        case 6:return PARENDERECHO;
        case 7:return COMA;
        case 8:return PUNTOYCOMA;
        case 10:if (esPalabraReservada(palabra)==1)
                 {
                    return devolverPalabraReservada(palabra);
                 }
                //agregarATablaSimbolos(palabra);
                return ID;
        case 11:return ERROR;
        case 12:return ASIGNACION;
        case 14:return CONSTANTE;
        case 15:return FDT;
        case 16:return ERROR;
    }
}

TOKEN devolverTokens (char *programaFuente)
{

    int pos=0;
    int estado=0;
    int _columna=0;
    char caracterLeido;
    char buffer[32];
    FILE* programa;
    if (programa=fopen(programaFuente,"rb"))
    {
        fseek(programa,cursor*sizeof(char),SEEK_SET);
        while ((estado>=0 && estado<=2) || estado==9 || estado==13 )
    {
        caracterLeido=fgetc(programa);
        cursor++;
        _columna=columna(caracterLeido);
        estado=estadoSiguiente(estado,_columna);
        if (estado==10 || estado==14 || estado==16 || estado==15)
            {
                cursor--;
                //ungetc(caracterLeido,programa);
                pos=0;
            }
        if (estado==1)
            {
                buffer[pos]=caracterLeido;
                buffer[++pos]='\0';
            }
       // tokens(estado,buffer);
    }
    }
    fclose(programa);
    return tokens(estado,buffer);
}

TOKEN proximoToken()
{
   TOKEN token;
   int posicion=cursor;
   token=devolverTokens("programaDePrueba.txt");
   cursor=posicion;
   return token;

}

void match(TOKEN tokenEsperado)
{
    TOKEN tokenRecibido=devolverTokens("programaDePrueba.txt");
    if (tokenEsperado==tokenRecibido)
        return;
    printf("Error sintactico (no matchea %d con %d)\n",tokenEsperado,tokenRecibido);
    return;

}

void programa()
{
    match(INICIO);
    listaDeSentencias();
    match(FIN);
}

void listaDeSentencias()
{
    sentencia();
    while(1)
    {
        switch(proximoToken())
        {
        case ID:
        case ESCRIBIR:
        case LEER:sentencia();
                  break;
        default: return;
        }
    }
}

void sentencia()
{
    TOKEN token=proximoToken("programaDePrueba.txt");
    switch(token)
    {
        case ID: match(ID);
                 match(ASIGNACION);
                 //expresion
                 match(PUNTOYCOMA);
                 break;
        case LEER: match(PARENIZQUIERDO);
                   //lista de identificadores
                   match(PARENDERECHO);
                   match(PUNTOYCOMA);
                   break;
        case ESCRIBIR: match(PARENIZQUIERDO);
                       //lista de expresiones
                       match(PARENDERECHO);
                       match(PUNTOYCOMA);
                       break;
    }
    return;
}




int main(int argc,char *argv[])
{
        int c=0;
        inicializarTablaSimbolos();
        programa();
        match(FDT);

}
// Compilador-micro
