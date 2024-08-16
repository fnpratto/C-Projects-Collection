
#include <stdio.h>
#include <stdbool.h>

#include "increidle.h"

const char RESPUESTA_CORRECTA_UNO = 'K';
const char RESPUESTA_CORRECTA_DOS = 'R';
const char RESPUESTA_CORRECTA_TRES = 'O';
const char RESPUESTA_CORRECTA_CUATRO = 'N';
const char RESPUESTA_CORRECTA_CINCO = 'S';
const char RESPUESTA_INCORRECTA = 'X';

const int NUMERO_MAX = 100;
const int NUMERO_MIN = 1;

const char CODIGO_EMERGENCIA = 'A';
const char PATO = 'C';
const int RAYO_MCQUEEN = 95;
const char TIGRE_JAZMIN = 'C';

//RESPUESTA CORRECTA
#define LONGITUD_RESPUESTA 6
static const char RESPUESTA_CORRECTA[LONGITUD_RESPUESTA]={'K','R','O','N','O','S'};


/*BOOLEANOS Y FUNCIONES*/


    bool respuesta_novalida(char letra){
        if(letra=='A' || letra=='B' || letra =='C' || letra =='D'){
            return false;
        } return true;
    }

    
    bool numero_noen_rango(int numero){
        return((numero>NUMERO_MAX)||(numero<NUMERO_MIN));
    }


    int cantidad_numero_primos(int numero[MAX_NUMERO_PRIMOS]){
        int numeros_primos=0;

        for(int i=0; i < MAX_NUMERO_PRIMOS; i++){

            int contador = 0;
            
            for(int j=1; j <= numero[i]; j++){ 
                if((numero[i]%j==0)){ 
                    contador ++;
                }
            }if(contador==2){
                numeros_primos ++;
            }
            
        }return numeros_primos;
    }

/*PREGUNTAS*/

    void preguntar_código_de_emergencia(char* codigo){
            do{
            printf("¿Cuál es el código de emergencia utilizado en Monsters Inc. cuando uno de los personajes tiene una media humana pegada a su cuerpo? A.3312 B.3317 C.2312 D.2031 \n");
            scanf(" %c",codigo);
            }while(respuesta_novalida(*codigo));
    }


    void preguntar_mascota_lilo(char* nombre_mascota){
        do{
            printf("¿Cuál era el nombre del pez mascota de Lilo?A.Stich  B.Pez C.Pato D.Aurelio\n");
            scanf(" %c",nombre_mascota);
        }while(respuesta_novalida(*nombre_mascota));
    }

    void preguntar_numeros_tadashi (int numeros_tadashi[MAX_NUMERO_PRIMOS]){
        for(int tope=0; tope < MAX_NUMERO_PRIMOS; tope++){
            int numero_ingresado;
            do{
                printf("Ingrese su numero:");
                scanf("%i",&numero_ingresado);
                numeros_tadashi[tope]= numero_ingresado;
            }while(numero_noen_rango(numero_ingresado));     
        }
    } 


    void preguntar_numero_RayoMcQueen(int* numero_auto){
        do{
            printf("¿Qué número lleva el Rayo McQueen?\n ");
            scanf("%i",numero_auto);
        }while(numero_noen_rango(*numero_auto));
    }


    void preguntar_nombre_tigre_jazmin(char* tigre){
        do{
            printf("¿Cómo se llama el tigre de la princesa Jazmín? A.Zafiro B.Abú C. Rajah D.Jafar\n");
            scanf(" %c",tigre);
        }while(respuesta_novalida(*tigre));
    }

/*VERIFICAR RESPUESTAS*/

    char verificar_numeros_tadashi(int numeros[MAX_NUMERO_PRIMOS]){
        if(cantidad_numero_primos(numeros)== MAX_NUMERO_PRIMOS){
            return RESPUESTA_CORRECTA_TRES;
        }return RESPUESTA_INCORRECTA; 
    }

    char verificar_numero_RayoMcQueen(int respuesta){
        if(respuesta == RAYO_MCQUEEN){ //95
            return RESPUESTA_CORRECTA_CUATRO; 
        }return RESPUESTA_INCORRECTA; 
    }
     

    char verificar_código_de_emergencia(char respuesta){
        if(respuesta == CODIGO_EMERGENCIA){
            return RESPUESTA_CORRECTA_UNO;
        } return RESPUESTA_INCORRECTA;
    }


    char verificar_mascota_lilo(char respuesta){
        if(respuesta == PATO){ 
        return RESPUESTA_CORRECTA_DOS;
        }return RESPUESTA_INCORRECTA;
    }

    char verificar_tigre_princesa(char nombre){
        if(nombre == TIGRE_JAZMIN){
            return RESPUESTA_CORRECTA_CINCO;
        } return RESPUESTA_INCORRECTA;
    }

/*IMPRIMIR RESPUESTA*/

    void imprimir_vector_respuesta(char respuesta[MAX_NUMERO_RESPUESTA],int tope_respuesta){
        printf("-");
        for(int i=0; i<tope_respuesta;i++){
            printf("%c",respuesta[i]);
        }
        printf("-");
    }


bool respuesta(){
    char respuesta[MAX_NUMERO_RESPUESTA];
    int tope_respuesta = 0;

    //1
    char codigo_emergencia;
    preguntar_código_de_emergencia(&codigo_emergencia);
    respuesta[0]=verificar_código_de_emergencia(codigo_emergencia);
    tope_respuesta++;

    //2
    char nombre_mascota;
    preguntar_mascota_lilo(&nombre_mascota);
    respuesta[1] =verificar_mascota_lilo(nombre_mascota);
    tope_respuesta++;
    
    //3
    int numeros_tadashi[MAX_NUMERO_PRIMOS];
    preguntar_numeros_tadashi(numeros_tadashi);
    respuesta[2] = verificar_numeros_tadashi(numeros_tadashi);
    tope_respuesta++;
    respuesta[4] = verificar_numeros_tadashi(numeros_tadashi);
    tope_respuesta++;
    
    //4
    int numero_auto = 0;
    preguntar_numero_RayoMcQueen(&numero_auto);
    respuesta[3] = verificar_numero_RayoMcQueen(numero_auto);
    tope_respuesta++;

    //5
    char tigre='Z';
    preguntar_nombre_tigre_jazmin(&tigre);
    respuesta[5]= verificar_tigre_princesa(tigre);
    tope_respuesta++;

    imprimir_vector_respuesta(respuesta,tope_respuesta);

    //chequear_respuesta

    bool correcto= false;
    int contador_letras_correctas=0;
    for(int i=0;i<LONGITUD_RESPUESTA;i++){
        if(respuesta[i]==RESPUESTA_CORRECTA[i]){
        contador_letras_correctas++;
        }
    }

    if(contador_letras_correctas==5){
        correcto= true;
    }

    return(correcto);
}