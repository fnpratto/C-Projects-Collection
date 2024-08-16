#ifndef __INCREIDLE_H__
#define __INCREIDLE_H__


#include <stdio.h>
#include <stdbool.h>


#define MAX_NUMERO_RESPUESTA 6
#define MAX_NUMERO_PRIMOS 5

/*BOOLEANOS Y FUNCIONES*/

//PRE: Recibe un caracter
//POST:Se devuelve true si el caracter es: 'A' , 'B' , 'C' , 'D' y false si no.
bool respuesta_novalida(char letra);


//PRE: SOLO ACEPTA NUMEROS
//POST: Se devuelve true si el numero esta en el rango [0,100] y false si no esta en el rango
bool numero_noen_rango(int numero);


//PRE: Se ingresa un vector inicializado con enteros 
//POST: Se devuelve cantidad de numeros primos en un vector
int cantidad_numero_primos(int numero[MAX_NUMERO_PRIMOS]);


/*PREGUNTAS*/

//PRE: Recibe caracteres A/B/C/D
//POST: Pide un character y guarda en una variable (si no cumple condicion de PREcondicion se vuelve a preguntar)
void preguntar_código_de_emergencia(char* codigo);



//PRE: Recibe caracteres A/B/C/D
//POST: Pide un character y guarda en una variable (si no cumple condicion de PREcondicion se vuelve a preguntar)
void preguntar_mascota_lilo(char* nombre_mascota);


//PRE: Acepta enteros que esten en el rango [0-100]
//POST: Pide enteros los cuales se usan para inicializar el vector 
void preguntar_numeros_tadashi (int numeros_tadashi[MAX_NUMERO_PRIMOS]);


//PRE: Acepta enteros que esten en el rango [0-100]
//POST: Pide un character y guarda en una variable (si no cumple condicion de PREcondicion se vuelve a preguntar)
void preguntar_numero_RayoMcQueen(int* numero_auto);


//PRE: Recibe caracteres A/B/C/D
//POST:Pide un character y guarda en una variable (si no cumple condicion de PREcondicion se vuelve a preguntar)
void preguntar_nombre_tigre_jazmin(char* tigre);



/*VERIFICAR RESPUESTAS*/

//PRE: Se ingresa un vector inicializado 
//POST:Se devuelve el caracter 'O' o 'X' respectivamente 
char verificar_numeros_tadashi(int numeros[MAX_NUMERO_PRIMOS]);


//PRE: Se ingresa un entero ,en el rango [0-100]
//POST: Se devuelve el caracter 'N'(si respuesta '95') o 'X' 
char verificar_numero_RayoMcQueen(int respuesta);


//PRE: Se ingresa un caracter (A/B/C/D)
//POST: Se devuelve el caracter 'K' (si respuesta 'A') o 'X' 
char verificar_código_de_emergencia(char respuesta);

//PRE: Se ingresa un caracter (A/B/C/D)
//POST: Se devuelve el caracter 'R'(si respuesta 'C') o 'X' 
char verificar_mascota_lilo(char respuesta);

//PRE: Se ingresa un caracter (A/B/C/D)
//POST: Se devuelve el caracter 'S' (si respuesta 'C')o 'X' respectivamente
char verificar_tigre_princesa(char nombre);

/*IMPRIMIR RESPUESTA*/

//PRE: Debe ingresarse un vector inicializado con caracteres
//POST: Imprime la respuesta por pantalla
void imprimir_vector_respuesta(char respuesta[MAX_NUMERO_RESPUESTA],int tope_respuesta);

bool respuesta();

#endif /* __INCREIDLE_H__ */