#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMFILA 17
#define TAMCOLUMNA 13

const char palabraReservada [10][10]=
{
  {'I','N','I','C','I','O','\0'},
  {'F','I','N','\0'},
  {'l','e','e','r','\0'},
  {'e','s','c','r','i','b','i','r','\0'},
};

/*strcpy(*palabrasReservadas[1],"FIN");
strcpy(*palabrasReservadas[2],"leer");
strcpy(*palabrasReservadas[3],"escribir");*/

int esPalabraReservada(char palabra[])
{
    int c=0;
    while (strcmp(palabra,palabraReservada[c])&& c<=4)
    {
        c++;
    }
    if (c>4) return 0;
    else return 1;
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

void tokens (int estado,char palabra[])
{
    switch (estado)
    {
        case 0:break;
        case 1:break;
        case 2:break;
        case 3:printf("OPERADOR SUMA\n");
                break;
        case 4:printf("OPERADOR RESTA\n");
                break;
        case 5:printf("PARENTESIS ABIERTO\n");
                break;
        case 6:printf("PRENTESIS CERRADO\n");
                break;
        case 7:printf("COMA\n");
                break;
        case 8:printf("PUNTO Y COMA\n");
                break;
        case 9:break;
        case 10:if (esPalabraReservada(palabra)==1)
                 {
                    printf("PALABRA RESERVADA\n");
                    palabra[0]='\0';
                    break;
                 }
                printf("IDENTIFICADOR\n");
                palabra[0]='\0';
                break;
        case 11:printf("ERROR LEXICOGRAFICO\n");
                break;
        case 12:printf("OPERADOR ASIGNACION\n");
                break;
        case 13:break;
        case 14:printf("DIGITO\n");
                break;
        case 15:break;
        case 16:printf("ERROR LEXICOGRAFICO\n");
                break;
    }
   return;
}

void devolverTokens (char *programaFuente)
{
    int pos=0;
    int estado=0;
    int _columna=0;
    char caracterLeido;
    char palabra[32];
    FILE* programa;
    if (programa=fopen(programaFuente,"rb"))
    {
        while (estado!=15)
    {
        caracterLeido=fgetc(programa);
        _columna=columna(caracterLeido);
        estado=estadoSiguiente(estado,_columna);
        if (estado==10 || estado==14 || estado==16)
            {
                ungetc(caracterLeido,programa);
                pos=0;
            }
        if (estado==1)
            {
                palabra[pos]=caracterLeido;
                pos++;
                palabra[pos]='\0';
            }
        tokens(estado,palabra);
    }
    }
    fclose(programa);

}


int main(int argc,char *argv[])
{
        devolverTokens("programaDePrueba.txt");
}
// Compilador-micro
