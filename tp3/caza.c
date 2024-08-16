#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.h"

int main(int argc, char* argv[]){
    int estado=0;
    if(argc==1){
        estado=FALTA_COMANDO;
    }else if(strcmp(argv[1], LISTAR) == TRUE){
        listar_superheroes(argc, argv);
    }else if(strcmp(argv[1], CONTACTAR) == TRUE){
        if(argc==4){
            contactar_superheroe(argc, argv);
        }else{
            estado=CONT_FALTA_DATOS;
        }
    }else if(strcmp(argv[1], MODIFICAR)== TRUE){
        if(argc==6){
            modificar_status_superheroe(argc, argv);
        }else{ 
            estado=MOD_FALTA_DATOS;
        }
    }else if(strcmp(argv[1], AGREGAR)== TRUE){
        if(argc==7){
                agregar_superheroe(argc, argv);
        }else{
            estado=AGR_FALTA_DATOS;
        }
    }else if(strcmp(argv[1], AYUDAR)== TRUE){
            estado=AYUDA;  
    }else{
        estado=COMANDO_NO_CORRECTO;
    }

    if(estado!=TODO_BENE){
        obtener_informacion(estado);
    }
    
	return 0;
}
