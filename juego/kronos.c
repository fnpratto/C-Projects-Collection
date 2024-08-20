#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "miextra.h"

void inicializar_juego(juego_t* juego,bool contrasenia_completa){
    juego->id_personaje_actual=ID_ELASTICGIRL;
    inicializar_robot(juego);
    inicializar_lasers(juego,contrasenia_completa);
    inicializar_pinzas(juego);
    inicializar_traje(juego);
    inicializar_personajes(juego);
}

void realizar_jugada(juego_t* juego , char movimiento){
    mover_lasers(juego);
    caminar_por_mapa(juego, movimiento);
}


void imprimir_terreno(juego_t juego){
	char matriz[MAX_LASERS][MAX_LASERS];
    int tope_fila =MAX_TABLERO;
    int tope_columna=MAX_TABLERO;

    inicializar_matriz(matriz,tope_columna,tope_fila);
    guardar_posiciones(juego, matriz);


	//IMPRIMO MATRIZ
		for(int i=0;i<tope_fila;i++){
	       int j=0;
           printf(" \n");
	    for (; j < tope_columna; j++){
	       char k=matriz[i][j];
	       printf("%c",k);
	    }
	  }printf(" \n");
}

int estado_juego(juego_t juego){ 
    if((juego.personajes[juego.id_personaje_actual-1].movimientos)<=0){
        return( PERDIO_EL_JUEGO);
    }else if((juego.personajes[juego.id_personaje_actual-1].movimientos)>CANT_MOV_VIOLETA && juego.id_personaje_actual==ID_MR_INCREIBLE){
        return(GANO_EL_JUEGO);
    }else {
        return(SIGUE_EN_JUEGO);       
    }
}