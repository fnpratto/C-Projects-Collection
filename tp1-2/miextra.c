#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // Para usar rand
#include <time.h> // Para obtener una semilla desde el reloj
#include "miextra.h"

//condiciones de coordenadas 
bool esta_en_rango(int coordenada){
    return(coordenada>=MIN_TABLERO && coordenada <MAX_TABLERO);
}

int coordenada_fila_segun_cuadrante(int i){
                if(i==CUADRANTE_1 || i==CUADRANTE_4){
                    return(rand () % MITAD_TABLERO);   
                }else{
                    return((rand () % MITAD_TABLERO) +MITAD_TABLERO); 
                }
}

int coordenada_colummna_segun_cuadrante(int i){
                if(i==CUADRANTE_1 || i==CUADRANTE_3){
                    return(rand () % MITAD_TABLERO);   
                }else{
                    return((rand () % MITAD_TABLERO) +MITAD_TABLERO); 
                }           
}

bool posicion_ocupada(juego_t* juego, int fila, int columna,char tipo){
    if(tipo==LASER){
        return(hay_salida(fila,columna) /*|| hay_robot(juego,fila,columna)*/);
    }else if(tipo==PINZA){
        return(hay_robot(juego, fila,columna)||hay_laser(juego, fila,columna)|| hay_salida(fila,columna));
    }else if(tipo==SUPERTRAJE){
        return(hay_robot(juego, fila,columna)||hay_laser(juego, fila,columna) || hay_pinza(juego, fila,columna)|| hay_salida(fila,columna));
    }else{//PERSONAJES
        return(hay_robot(juego, fila,columna)||hay_laser(juego, fila,columna) || hay_pinza(juego, fila,columna)|| hay_traje(juego, fila,columna)>-1|| hay_salida(fila,columna));
    }
} 

int coordenada_rango_robot(){
    return(rand() % 2 );
}

bool hay_salida(int i, int j){
    return(i==FIL_SALIDA && j==COL_SALIDA);
}

bool hay_robot(juego_t* juego,int i, int j){
    for(int k=0; k<(juego->tope_robots);k++){
        if((juego->robots[k].posicion.fila)==i && (juego->robots[k].posicion.columna)==j){
            return(true);
        }
    }return(false);
}

bool hay_laser(juego_t* juego,int fil, int col){
    for(int i=0; i<juego->tope_robots;i++){
        for (int j = 0; j < juego->robots[i].tope_lasers; j++){
        if(juego->robots[i].lasers[j].fila==fil && juego->robots[i].lasers[j].columna==col){
            return(true);
        }
        }
    }return(false);
}

bool hay_pinza(juego_t* juego, int i, int j){
    for(int k=0; k<(juego->tope_pinzas);k++){
        if((juego->pinzas[k].fila)==i && (juego->pinzas[k].columna)==j){
            return(true);
        }
    }return(false);
}
        
int hay_traje(juego_t* juego, int i, int j){
    for(int k=0; k<(juego->tope_supertraje);k++){
        if(juego->supertrajes[k].posicion.fila==i && juego->supertrajes[k].posicion.columna==j){
            return(k);
        }
    }return(VALOR_NO_VALIDO);
}

int figura_anterior(juego_t* juego , int i){

    int primer_laser_columna = (juego->robots[i].lasers[0].columna);
    int primer_laser_fila = (juego->robots[i].lasers[0].fila);
    int segundo_laser_columna=(juego->robots[i].lasers[1].columna);
    int segundo_laser_fila=(juego->robots[i].lasers[1].fila);
    
    if (primer_laser_columna==segundo_laser_columna){ //figura uno || figura cinco
        if(primer_laser_fila> segundo_laser_fila) { 
            return 1;
        }else return 5;
    }else if(primer_laser_columna<segundo_laser_columna){ //figura dos |||tres || cuatro
        if (primer_laser_fila> segundo_laser_fila){ 
            return 2;
        }else if(primer_laser_fila== segundo_laser_fila){
            return 3;
        }else{//primer_laser_fila< segundo_laser_fila
            return 4;
        }
    }else {//(primer_laser_columna>segundo_laser_columna){ //figura seis || siete || ocho
        if(primer_laser_fila< segundo_laser_fila){
            return 6;
        }else if(primer_laser_fila== segundo_laser_fila){
            return 7;
        }else {// if(primer_laser_fila> segundo_laser_fila){
            return 8;
        }
    }
}

void figura_uno (juego_t* juego, int robot){ 
    int longitud_de_laser= juego->longitud_laser;
    for(int i=1; i<=(longitud_de_laser*2);i++){
        do{
        if(i>longitud_de_laser){
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)+(i-longitud_de_laser);
            (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila);
            (juego->robots[robot].tope_lasers)+=1;
        }else if(i<=longitud_de_laser){
            (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)-i;
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna);
            (juego->robots[robot].tope_lasers)+=1;

        }
        }while(posicion_ocupada(juego,juego->robots[robot].lasers[i].fila,juego->robots[robot].lasers[i].columna,LASER));
    }
}

void figura_dos (juego_t* juego, int robot){ 
    int longitud_de_laser= juego->longitud_laser;
    for(int i=1; i<=(longitud_de_laser*2);i++){
        do{
        if(i>longitud_de_laser){
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)+(i-longitud_de_laser);
            (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)+(i-longitud_de_laser);
            (juego->robots[robot].tope_lasers)+=1;
        }else if(i<=longitud_de_laser){
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)+i;
            (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)-i;
            (juego->robots[robot].tope_lasers)+=1;

        }
        }while(posicion_ocupada(juego,juego->robots[robot].lasers[i].fila,juego->robots[robot].lasers[i].columna,LASER));
    }
}

void figura_tres (juego_t* juego, int robot){
    int longitud_de_laser= juego->longitud_laser;
    for(int i=1; i<=(longitud_de_laser*2);i++){
        do{
        if(i>longitud_de_laser){
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna);
            (juego->robots[robot].lasers[i-1].fila)=(i-longitud_de_laser)+(juego->robots[robot].posicion.fila);
            (juego->robots[robot].tope_lasers)+=1;
        }else if(i<=longitud_de_laser){
            (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila);
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)+i;
            (juego->robots[robot].tope_lasers)+=1;
        }
        }while(posicion_ocupada(juego,juego->robots[robot].lasers[i].fila,juego->robots[robot].lasers[i].columna,LASER));
    }
}


void figura_cuatro (juego_t* juego, int robot){ 
    int longitud_de_laser= juego->longitud_laser;
    for(int i=1; i<=(longitud_de_laser*2);i++){
        do{
        if(i>longitud_de_laser){
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)-(i-longitud_de_laser);
            (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)+(i-longitud_de_laser);
            (juego->robots[robot].tope_lasers)+=1;
        }else if(i<=longitud_de_laser){
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)+i;
            (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)+i;
            (juego->robots[robot].tope_lasers)+=1;

        }
        }while(posicion_ocupada(juego,juego->robots[robot].lasers[i].fila,juego->robots[robot].lasers[i].columna,LASER));
    }
}

void figura_cinco (juego_t* juego, int robot){
    int longitud_de_laser= juego->longitud_laser;
    for(int i=1; i <= (longitud_de_laser*2); i++){
        do{
        if(i>longitud_de_laser){
                (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)-(i-longitud_de_laser);
                (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila);
                (juego->robots[robot].tope_lasers)+=1;
        }else if(i<=longitud_de_laser){
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna);
            (juego->robots[robot].lasers[i-1].fila)=i+(juego->robots[robot].posicion.fila);
            (juego->robots[robot].tope_lasers)+=1;
        }
        }while(posicion_ocupada(juego,juego->robots[robot].lasers[i].fila,juego->robots[robot].lasers[i].columna,LASER));
    }
}

void figura_seis (juego_t* juego, int robot){
    int longitud_de_laser= juego->longitud_laser;
    for(int i=1; i <= (longitud_de_laser*2); i++){
        do{
        if(i>longitud_de_laser){
                (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)-(i-longitud_de_laser);
                (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)-(i-longitud_de_laser);
                (juego->robots[robot].tope_lasers)+=1;
        }else if(i<=longitud_de_laser){
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)-i;
            (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)+i;
            (juego->robots[robot].tope_lasers)+=1;
        }
        }while(posicion_ocupada(juego,juego->robots[robot].lasers[i].fila,juego->robots[robot].lasers[i].columna,LASER));
    }

}

void figura_siete (juego_t* juego, int robot){
    int longitud_de_laser= juego->longitud_laser;
    for(int i=1; i <= (longitud_de_laser*2); i++){
        do{
        if(i>longitud_de_laser){
                    (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna);
                    (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)-(i-longitud_de_laser);
                    (juego->robots[robot].tope_lasers)+=1;
        }else if(i<=longitud_de_laser){
            (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)-i;
            (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila);
            (juego->robots[robot].tope_lasers)+=1;
        }
        }while(posicion_ocupada(juego,juego->robots[robot].lasers[i].fila,juego->robots[robot].lasers[i].columna,LASER));
    }
}

void figura_ocho (juego_t* juego, int robot){
    int longitud_de_laser= juego->longitud_laser;
    for(int i=1; i <= (longitud_de_laser*2); i++){
        do{
        if(i>longitud_de_laser){
                    (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)+(i-longitud_de_laser);
                    (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)-(i-longitud_de_laser);
                    (juego->robots[robot].tope_lasers)+=1;
        }else if(i<=longitud_de_laser){
                (juego->robots[robot].lasers[i-1].columna)=(juego->robots[robot].posicion.columna)-i;
                (juego->robots[robot].lasers[i-1].fila)=(juego->robots[robot].posicion.fila)-i;
                (juego->robots[robot].tope_lasers)+=1;
        }
        }while(posicion_ocupada(juego,juego->robots[robot].lasers[i].fila,juego->robots[robot].lasers[i].columna,LASER));   
    }
}

int LongitudLaser(bool contrasenia_completa){
    if(contrasenia_completa){
        return (RES_CORRECTA_LONG_LASER);
    }else return(RES_INCORRECTA_LONG_LASER);
}

void activar_poder_dash(juego_t *juego){
    if(juego->personajes[POS_DASH].movimientos_con_poder>0 && juego->supertrajes[POS_DASH].usado ==false){
        printf("Poder de DASH; Se mueve al 4to cuadrante por %i turno\n", juego->personajes[POS_DASH].movimientos_con_poder);
        juego->personajes[POS_DASH].movimientos_con_poder=-1;
        juego->personajes[POS_DASH].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_4);
        juego->personajes[POS_DASH].posicion.columna=coordenada_colummna_segun_cuadrante(CUADRANTE_4);
        juego->supertrajes[POS_DASH].usado = true;
        chequear_posicion_ocupada(juego,juego->personajes[POS_DASH].posicion.fila,juego->personajes[POS_DASH].posicion.columna);
    }
}

bool poder_elastigirl_activado(juego_t *juego){
    if(juego->personajes[juego->id_personaje_actual-1].poder_activado == true && juego->supertrajes[juego->id_personaje_actual-1].usado==false){

        if(juego->personajes[POS_ELASTICGIRL].movimientos_con_poder>0){
            juego->personajes[POS_ELASTICGIRL].movimientos_con_poder-=1;
        printf("Poder Elastigirl; se mueve tres casillas por %i turno/s\n", juego->personajes[POS_ELASTICGIRL].movimientos_con_poder);   
            return true;
        }else{
            printf("Se acabo el poder :(\n");
            juego->supertrajes[POS_ELASTICGIRL].usado =true;
            return false;
        }

    }return false;
}


bool poder_violeta_activado(juego_t* juego){
    if(juego->personajes[POS_VIOLETA].poder_activado == true && juego->supertrajes[POS_VIOLETA].usado ==false){

        if(juego->personajes[POS_VIOLETA].movimientos_con_poder >0){
            juego->personajes[POS_VIOLETA].movimientos_con_poder-=1;
            printf("Poder Violeta; No muere por lasers por %i turno/s\n", juego->personajes[POS_VIOLETA].movimientos_con_poder);
            return true; 
        }else{
            printf("-Se acabo el poder :(\n");
            juego->supertrajes[POS_VIOLETA].usado =true;
            return false;
        }
    } return false;
       
}

bool poder_mrincreible_activado(juego_t* juego){
     if(juego->id_personaje_actual==ID_MR_INCREIBLE && juego->personajes[juego->id_personaje_actual-1].poder_activado == true && juego->supertrajes[juego->id_personaje_actual-1].usado ==false){

        if(juego->personajes[juego->id_personaje_actual-1].movimientos_con_poder>0){
            juego->personajes[POS_MR_INCREIBLE].movimientos_con_poder-=1;
            printf("Poder Increible; Las pinzas no lo mueven por %i turno/s\n", juego->personajes[POS_VIOLETA].movimientos_con_poder);
            return true;  
        }else{
            printf("Se acabo el poder :(\n");
            juego->supertrajes[POS_MR_INCREIBLE].usado =true;
            return false;
        }
    }return false; 
}


void activar_poder(juego_t *juego){
    for(int i=0; i<juego->tope_supertraje;i++){
        if((juego->supertrajes[i].recolectado==true) && (juego->id_personaje_actual)==i+1 && juego->personajes[i].tiene_supertraje==true && juego->personajes[juego->id_personaje_actual-1].poder_activado == false){
            printf("Poder activado");
            juego->personajes[juego->id_personaje_actual-1].poder_activado = true;
        }
            if(juego->id_personaje_actual == ID_DASH){
                activar_poder_dash(juego);
            }
    }
}



void recoger_traje(juego_t* juego, int supertraje_encontrado){
    if(juego->id_personaje_actual-1 ==supertraje_encontrado){
        juego->supertrajes[supertraje_encontrado].recolectado=true;
        juego->personajes[juego->id_personaje_actual-1].tiene_supertraje=true;
        printf("Traje recogido, apreta C para activar tu poder :)\n");
    }
}

void mover_posicion_pinzas(juego_t *juego){
    int i=0;
    int j=0;
        int hi=(rand() % 2);
        if(hi==0){
            do{
                (juego->personajes[juego->id_personaje_actual-1].posicion.fila)=((juego->robots[juego->id_personaje_actual-1].posicion.fila)-coordenada_rango_robot());
                (juego->personajes[juego->id_personaje_actual-1].posicion.columna)=((juego->robots[juego->id_personaje_actual-1].posicion.columna)-coordenada_rango_robot());

            i=juego->personajes[juego->id_personaje_actual-1].posicion.fila;
            j=juego->personajes[juego->id_personaje_actual-1].posicion.columna;
            }while(/*hay_salida(i,j)||*/!esta_en_rango(i)|| !esta_en_rango(j));
        }else{
            do{
                (juego->personajes[juego->id_personaje_actual-1].posicion.fila)=((juego->robots[juego->id_personaje_actual-1].posicion.fila)+coordenada_rango_robot());
                (juego->personajes[juego->id_personaje_actual-1].posicion.columna)=((juego->robots[juego->id_personaje_actual-1].posicion.columna)+coordenada_rango_robot());

                i=juego->personajes[juego->id_personaje_actual-1].posicion.fila;
                j=juego->personajes[juego->id_personaje_actual-1].posicion.columna;

            }while(/*hay_salida(i,j)||*/!esta_en_rango(i)|| !esta_en_rango(j));
        }
}

void chequear_posicion_ocupada(juego_t *juego,int fil, int col){
    int supertraje_encontrado = hay_traje(juego,fil,col);

            if((hay_robot(juego, fil,col))){ 
                (juego->personajes[juego->id_personaje_actual-1].movimientos)=0;
            
            }else if(hay_laser(juego,fil,col)){
                if(juego->id_personaje_actual==ID_VIOLETA && poder_violeta_activado(juego)){
                }else{
                    (juego->personajes[juego->id_personaje_actual-1].movimientos)=0;
                }

            }else if(supertraje_encontrado>-1){
                recoger_traje(juego,supertraje_encontrado);

            }else if (hay_pinza(juego,fil,col)){
                if(juego->id_personaje_actual==ID_MR_INCREIBLE && poder_mrincreible_activado(juego)){

                }else{
                    mover_posicion_pinzas(juego);
                    chequear_posicion_ocupada(juego, juego->personajes[juego->id_personaje_actual-1].posicion.fila,juego->personajes[juego->id_personaje_actual-1].posicion.columna);       
                }
             
            }else if(hay_salida(fil, col) && (juego->id_personaje_actual)==ID_MR_INCREIBLE){

                juego->personajes[POS_MR_INCREIBLE].movimientos+=99;

            }else if(fil==(juego->personajes[POS_VIOLETA].posicion.fila) && col==(juego->personajes[POS_VIOLETA].posicion.columna) &&(juego->id_personaje_actual)==1){
                cambiar_personaje(juego);

            }else if(fil==(juego->personajes[POS_DASH].posicion.fila) && col==(juego->personajes[POS_DASH].posicion.columna) &&(juego->id_personaje_actual)==2){
                cambiar_personaje(juego);  

            }else if(fil==(juego->personajes[POS_MR_INCREIBLE].posicion.fila) && col==(juego->personajes[POS_MR_INCREIBLE].posicion.columna) &&(juego->id_personaje_actual)==3){
                cambiar_personaje(juego);     
            }
}

//INICIALIZO MATRIZ CON VACIOS	
void inicializar_matriz(char matriz[MAX_LASERS][MAX_LASERS],int tope_columna, int tope_fila){

	for(int i=0;i<tope_fila;i++){
    int j=0;
    	for (;j < tope_columna; j++){
      		matriz[i][j]= VACIO; 
    	}
	}
    matriz[FIL_SALIDA][COL_SALIDA]=SALIDA;
}

void inicializar_lasers(juego_t* juego, bool contrasenia_completa){
    juego->longitud_laser = LongitudLaser(contrasenia_completa);

    for(int robot =0; robot<(juego->tope_robots);robot++){
        int figura_laser=rand()%4;
        if(figura_laser==0){
             figura_uno(juego,robot);
        }else if(figura_laser==1){
            figura_tres(juego,robot);
        }else if(figura_laser==2){
            figura_cinco(juego,robot);
        }else{
            figura_siete(juego,robot);
        }
    }    
}


void inicializar_personajes(juego_t* juego){
        juego->tope_personajes=4;

        for(int i =0; i<(juego->tope_personajes);i++){
        do{
            if(i==0){
                juego->personajes[i].cuadrante_inicial=CUADRANTE_1;
                juego->personajes[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_1);
                juego->personajes[i].posicion.columna=coordenada_colummna_segun_cuadrante(CUADRANTE_1);
                juego->personajes[i].movimientos=CANT_MOV_ELAST;
                juego->personajes[i].movimientos_con_poder=CANT_MOV_PODER;
                juego->personajes[i].poder_activado = false;
                juego->personajes[i].tiene_supertraje =false;

            } else if(i==1){
                juego->personajes[i].cuadrante_inicial=CUADRANTE_2;
                juego->personajes[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_2);
                juego->personajes[i].posicion.columna=coordenada_colummna_segun_cuadrante(CUADRANTE_2);
                juego->personajes[i].movimientos=CANT_MOV_VIOLETA;
                juego->personajes[i].movimientos_con_poder=CANT_MOV_PODER;
                juego->personajes[i].poder_activado = false;
                juego->personajes[i].tiene_supertraje =false;
            } else if(i==2){
                juego->personajes[i].cuadrante_inicial=CUADRANTE_3;
                juego->personajes[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_3);
                juego->personajes[i].posicion.columna=coordenada_colummna_segun_cuadrante(CUADRANTE_3);
                juego->personajes[i].movimientos=CANT_MOV_DASH;
                juego->personajes[i].movimientos_con_poder=1;
                juego->personajes[i].poder_activado = false;
                juego->personajes[i].tiene_supertraje =false;
            } else /*if(i==4)*/ {
                juego->personajes[i].cuadrante_inicial=CUADRANTE_4;
                juego->personajes[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_4);
                juego->personajes[i].posicion.columna=coordenada_colummna_segun_cuadrante(CUADRANTE_4);
                juego->personajes[i].movimientos=CANT_MOV_MRI;
                juego->personajes[i].movimientos_con_poder=CANT_MOV_PODER;
                juego->personajes[i].poder_activado = false;
                juego->personajes[i].tiene_supertraje =false;
            }
        }while(posicion_ocupada(juego, juego->personajes[i].posicion.fila, juego->personajes[i].posicion.columna,VIOLETA));
    }
 }

void inicializar_pinzas(juego_t* juego){
    juego->tope_pinzas=0;
    for(int i=0;i<CANT_DE_PINZAS;i++){
    do{
        if(i<(4)){ 
            juego->pinzas[i].fila=coordenada_fila_segun_cuadrante(CUADRANTE_1);
            juego->pinzas[i].columna= coordenada_colummna_segun_cuadrante(CUADRANTE_1);
        }else if (i<8){ 
            juego->pinzas[i].fila=coordenada_fila_segun_cuadrante(CUADRANTE_2);
            juego->pinzas[i].columna= coordenada_colummna_segun_cuadrante(CUADRANTE_2);
        }else if (i<12){ 
            juego->pinzas[i].fila=coordenada_fila_segun_cuadrante(CUADRANTE_3);
            juego->pinzas[i].columna= coordenada_colummna_segun_cuadrante(CUADRANTE_3);
        }else{
            juego->pinzas[i].fila =coordenada_fila_segun_cuadrante(CUADRANTE_4);
            juego->pinzas[i].columna = coordenada_colummna_segun_cuadrante(CUADRANTE_4);
        }
    }while(posicion_ocupada(juego, juego->pinzas[i].fila, juego->pinzas[i].columna,PINZA));   
    juego->tope_pinzas+=1;
    }
}

void inicializar_traje(juego_t* juego){
    juego->tope_supertraje=0;
    for(int i=0;i<4;i++){
       do{
        if(i==0){ 
            juego->supertrajes[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_1);
            juego->supertrajes[i].posicion.columna= coordenada_colummna_segun_cuadrante(CUADRANTE_1);
            juego->supertrajes[i].cuadrante=CUADRANTE_1;
            juego->supertrajes[i].recolectado=false;
            juego->supertrajes[i].usado=false;
        }else if (i==1){ 
            juego->supertrajes[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_2);
            juego->supertrajes[i].posicion.columna= coordenada_colummna_segun_cuadrante(CUADRANTE_2);
            juego->supertrajes[i].cuadrante=CUADRANTE_2;
            juego->supertrajes[i].recolectado=false;
            juego->supertrajes[i].usado=false;
        }else if (i==2){ 
            juego->supertrajes[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_3);
            juego->supertrajes[i].posicion.columna= coordenada_colummna_segun_cuadrante(CUADRANTE_3);
            juego->supertrajes[i].cuadrante=CUADRANTE_3;
            juego->supertrajes[i].recolectado=false;
            juego->supertrajes[i].usado=false;
        } else if(i==3){
            juego->supertrajes[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_4);
            juego->supertrajes[i].posicion.columna= coordenada_colummna_segun_cuadrante(CUADRANTE_4);
            juego->supertrajes[i].cuadrante=CUADRANTE_4;
            juego->supertrajes[i].recolectado=false;
            juego->supertrajes[i].usado=false;
        }
    }while(posicion_ocupada(juego, juego->supertrajes[i].posicion.fila, juego->supertrajes[i].posicion.columna,SUPERTRAJE)); 
    juego->tope_supertraje+=1;
    }
}

void inicializar_robot(juego_t *juego){
    juego->tope_robots=0;
    for(int i=0;i<4;i++){
        (juego->robots[i].tope_lasers)=0;
        do{
        if(i==0){
            juego->robots[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_1);
            juego->robots[i].posicion.columna= coordenada_colummna_segun_cuadrante(CUADRANTE_1);
        }else if (i==1){ 
            juego->robots[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_2);
            juego->robots[i].posicion.columna= coordenada_colummna_segun_cuadrante(CUADRANTE_2);
            
        }else if (i==2){ 
            juego->robots[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_3);
            juego->robots[i].posicion.columna= coordenada_colummna_segun_cuadrante(CUADRANTE_3);
        } else{
            juego->robots[i].posicion.fila=coordenada_fila_segun_cuadrante(CUADRANTE_4);
            juego->robots[i].posicion.columna= coordenada_colummna_segun_cuadrante(CUADRANTE_4);
        }
    }while(juego->robots[i].posicion.fila==0 &&juego->robots[i].posicion.columna==19);
    juego->tope_robots+=1;
    }
}


 //GUARDO POSICIONES DE PERSONAJES
void guardar_posiciones(juego_t juego, char matriz[MAX_LASERS][MAX_LASERS]){

    //traje
    for(int i=0;i<juego.tope_supertraje;i++){
        if ((juego.supertrajes[i].recolectado)==false){
            matriz[juego.supertrajes[i].posicion.fila][juego.supertrajes[i].posicion.columna]=SUPERTRAJE;
        }
    }

    //pinzas
    for(int i=0;i<juego.tope_pinzas;i++){
        matriz[juego.pinzas[i].fila][juego.pinzas[i].columna]=PINZA;
    }

    //ROBOT y LASER
    for(int i=0;i<juego.tope_robots;i++){
        for(int j=0;j<(juego.robots[i].tope_lasers);j++){
            matriz[juego.robots[i].lasers[j].fila][juego.robots[i].lasers[j].columna]=LASER;
        }
         matriz[juego.robots[i].posicion.fila][juego.robots[i].posicion.columna]=ROBOT;
    }


    //personajes
    for(int i=0; i<=juego.tope_personajes;i++){

        if((juego.personajes[i].cuadrante_inicial)==CUADRANTE_1){
        matriz[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna]=ELASTICGIRL;    
        }else if((juego.personajes[i].cuadrante_inicial)==CUADRANTE_2){
        matriz[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna]=VIOLETA;    
        }else if((juego.personajes[i].cuadrante_inicial)==CUADRANTE_3){
        matriz[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna]=DASH;   
        }else if((juego.personajes[i].cuadrante_inicial)==CUADRANTE_4){
        matriz[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna]=MR_INCREIBLE;   
        }
    }
}

void cambiar_personaje(juego_t *juego){
    (juego->id_personaje_actual)+=1;
    printf("Cambio de personaje\n");
}

void mover_lasers(juego_t *juego){

    for(int i=0;i<(juego->tope_robots);i++){
    int figura_laser=figura_anterior(juego , i);

        if(figura_laser==1){
            figura_dos(juego , i);
        }else if(figura_laser==2){
            figura_tres(juego, i);
        }else if(figura_laser==3){
            figura_cuatro(juego, i);
        }else if(figura_laser==4){
            figura_cinco(juego,i);
        }else if(figura_laser==5){
            figura_seis(juego,i);
        }else if(figura_laser==6){
            figura_siete(juego,i);
        }else if(figura_laser==7){
            figura_ocho(juego,i);
        }else{
            figura_uno(juego,i);
        }
    }
}

void caminar_por_mapa(juego_t *juego, char movimiento){
    int i=(juego->personajes[juego->id_personaje_actual-1].posicion.fila);
    int j=(juego->personajes[juego->id_personaje_actual-1].posicion.columna);
    if(juego->personajes[juego->id_personaje_actual-1].movimientos>0){
        if(movimiento==ARRIBA && esta_en_rango(i-1)){

            if(juego->id_personaje_actual==ID_ELASTICGIRL && poder_elastigirl_activado(juego)){
                (juego->personajes[juego->id_personaje_actual-1].posicion.fila)-=3;
                chequear_posicion_ocupada(juego,i-3,j);
            }else{
                (juego->personajes[juego->id_personaje_actual-1].posicion.fila)-=1;
                chequear_posicion_ocupada(juego,i-1,j);
            }

        }else if(movimiento==ABAJO && esta_en_rango(i+1)){

            if(juego->id_personaje_actual==ID_ELASTICGIRL && poder_elastigirl_activado(juego)){
                (juego->personajes[juego->id_personaje_actual-1].posicion.fila)+=3;
                chequear_posicion_ocupada(juego,i+3,j);
            }else{
                (juego->personajes[juego->id_personaje_actual-1].posicion.fila)+=1;
                chequear_posicion_ocupada(juego,i+1,j);
            } 
        
        }else if(movimiento==IZQUIERA && esta_en_rango(j-1)){

            if(juego->id_personaje_actual==ID_ELASTICGIRL && poder_elastigirl_activado(juego)){
                (juego->personajes[juego->id_personaje_actual-1].posicion.columna)-=3;
                chequear_posicion_ocupada(juego,i,j-3);
            }else{  
                (juego->personajes[juego->id_personaje_actual-1].posicion.columna)-=1;
                chequear_posicion_ocupada(juego,i,j-1);
            }    

        }else if(movimiento==DERECHA && esta_en_rango(j+1)){
            
            if(juego->id_personaje_actual==ID_ELASTICGIRL && poder_elastigirl_activado(juego)){
                (juego->personajes[juego->id_personaje_actual-1].posicion.columna)+=3;
                chequear_posicion_ocupada(juego,i,j+3);
            }else{    
                (juego->personajes[juego->id_personaje_actual-1].posicion.columna)+=1;
                chequear_posicion_ocupada(juego,i,j+1);
            }    
            
        }else if(movimiento==ACTIVAR_PODER){
                activar_poder(juego);
                chequear_posicion_ocupada(juego,i,j);
        }   
        juego->personajes[juego->id_personaje_actual-1].movimientos--; 
    }else (juego->personajes[juego->id_personaje_actual-1].movimientos)=-99;
}