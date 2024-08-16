#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "kronos.h"
#include "increidle.h"

/*MOVIMIENTOS*/
static const char ARRIBA ='W';
static const char ABAJO ='S';
static const char DERECHA ='D';
static const char IZQUIERA ='A';
static const char ACTIVAR_PODER ='C';


char movimiento_usuario(){
    char movimiento;
    printf("\nMovimiento:");
    do{
        scanf("%c",&movimiento);
    }while(!(movimiento==ARRIBA||movimiento==ABAJO||movimiento==DERECHA||movimiento==IZQUIERA ||movimiento==ACTIVAR_PODER));
        return(movimiento);
}


int main(){
    srand (( unsigned)time(NULL));

    juego_t juego;

   // bool contrasenia_completa = respuesta();
    bool contrasenia_completa= true;
    inicializar_juego(&juego,contrasenia_completa);

    printf("EL ESTADO DEL JUEGO: \n");
    printf("Si 0 ,keep playing darling \n");
    printf("Si -1 ,sorry dude :(\n");
    printf("Si 1 ,yey ganaste\n");
    imprimir_terreno(juego);
    while(juego.personajes[juego.id_personaje_actual-1].movimientos>0 && juego.personajes[juego.id_personaje_actual-1].movimientos<31){
        printf("Tenes %i turnos \n ",juego.personajes[juego.id_personaje_actual-1].movimientos);
        char movimiento= movimiento_usuario();
        realizar_jugada(&juego, movimiento);
        imprimir_terreno(juego);
        int j =estado_juego(juego);
        printf("\nEstado_de_juego:%i\n",j);
    }

    //system("clear"); // Limpiamos la pantalla   
return 0;
}