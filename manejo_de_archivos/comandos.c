#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "comandos.h"

static int ERROR_ARCHIVO = -1;
static int ID_NEGATIVO = 4;
static int EDAD_NO_CORRECTA = 8;
static int ESTADO_NO_CORRECTO = 9;
static int ID_REPETIDO = 10;
static char CARACTER_NO_VALIDO = 'Z';
static int CANT_VAR_XLINEA = 4;
static int EDAD_MAX = 100;
static int VALOR_MIN = 0;

bool verificar_edad(int edad){
    if (edad>EDAD_MAX || edad<VALOR_MIN){
        obtener_informacion(EDAD_NO_CORRECTA);
        return false;
    }return true;
}

bool verificar_id(int id){
    return(id>VALOR_MIN);
}

char verificar_estado(char* estado){
    if(strcmp(estado,S_VIVO)== TRUE){
        return VIVO;
    }else if(strcmp(estado,S_MUERTO)== TRUE){
        return MUERTO;
    }else{
        obtener_informacion(ESTADO_NO_CORRECTO);
        return CARACTER_NO_VALIDO;
    }
}

int listar_superheroes (int argc, char* argv[]){
    FILE* superheroes = fopen(argv[2],LEER);
    if(!superheroes){
        printf("No puedo abrir el archivo");
        return ERROR_ARCHIVO;
    }
    
    superheroe_t superheroe;

    int leidos=fscanf(superheroes,LECTURA,&superheroe.ID,superheroe.nombre,&superheroe.edad,&superheroe.estado);
    printf("Hola! Gracias por confiar en nosotros, si necesitas ayuda usa el comando ./ayuda :)\n");
    printf("ID|NOMBRE|EDAD|ESTADO\n");
    while (leidos==CANT_VAR_XLINEA){
        printf(ESCRITURA,superheroe.ID,superheroe.nombre, superheroe.edad, superheroe.estado);
        leidos=fscanf(superheroes,LECTURA,&superheroe.ID,superheroe.nombre,&superheroe.edad,&superheroe.estado);
    }

    fclose(superheroes);
    return TODO_BENE;
}

int contactar_superheroe(int argc, char* argv[]){

    FILE* superheroes = fopen(argv[3],LEER);
    if(!superheroes){
        printf("No puedo abrir el archivo %s", argv[3]);
        return ERROR_ARCHIVO;
    }

    FILE* auxiliar = fopen(ARCHIVO_AUX,ESCRIBIR);
    if(!auxiliar){
        printf("No se pudo abrir el auxiliar");
        fclose(superheroes);
        return ERROR_ARCHIVO;
    }

    bool id_en_lista=false;
    superheroe_t superheroe;
    int id_buscado = atoi(argv[2]);

    int leidos=fscanf(superheroes,LECTURA,&superheroe.ID,superheroe.nombre,&superheroe.edad,&superheroe.estado);

    while (leidos==CANT_VAR_XLINEA){
        if(id_buscado!=superheroe.ID){
            fprintf(auxiliar,ESCRITURA,superheroe.ID,superheroe.nombre, superheroe.edad, superheroe.estado);
        }

        if(id_buscado==superheroe.ID){
            id_en_lista=true;
            bool vivo=false;
            if(superheroe.estado==VIVO){
                vivo= true;
            }

        printf("****SUPERHEROE ELEGIDO****\n");
        printf("-ID:%i\n",superheroe.ID);
        printf("-NOMBRE:%s\n",superheroe.nombre);
        printf("-EDAD:%i\n",superheroe.edad);

        if(vivo){
            printf("-ESTADO:vivo\n");
        }else{
            printf("-ESTADO:muerto\n");
        }
            printf("**************************\n");
        }

        leidos=fscanf(superheroes,LECTURA,&superheroe.ID,superheroe.nombre,&superheroe.edad,&superheroe.estado);
    }

    if(!id_en_lista){
        printf("Oh No ha habido un problema!!\n");
        printf("No esta libre el superheroe elegido , si queres saber quien esta en servicio usa el comando -listar- o para mas informacion usa el comando ./ejecutable ayuda\n");
    }

    fclose(superheroes);
    fclose(auxiliar);
    rename(ARCHIVO_AUX,argv[3]);
    return TODO_BENE;
}

int modificar_status_superheroe(int argc, char* argv[]){
    FILE* superheroes = fopen(argv[5],LEER);
    if(!superheroes){
        printf("No puedo abrir el archivo%s", argv[5]);
        return ERROR_ARCHIVO;
    }

    FILE* auxiliar = fopen(ARCHIVO_AUX,ESCRIBIR);
    if(!auxiliar){
        printf("No se pudo abrir el auxiliar");
        fclose(superheroes);
        return ERROR_ARCHIVO;
    }

    bool id_en_lista=false;
    int id_buscado = atoi(argv[2]);
    int edad = atoi(argv[3]);
    char* argumento_estado = argv[4];

    if(!verificar_edad(edad)){
        return ERROR_ARCHIVO;
    }

    char estado= verificar_estado(argumento_estado);
    if(estado!=MUERTO && estado!=VIVO){
        return ERROR_ARCHIVO;
    }

    superheroe_t superheroe;
    int leidos=fscanf(superheroes,LECTURA,&superheroe.ID,superheroe.nombre,&superheroe.edad,&superheroe.estado);

    while (leidos==CANT_VAR_XLINEA){
        if(id_buscado!=superheroe.ID){
            fprintf(auxiliar,ESCRITURA,superheroe.ID,superheroe.nombre, superheroe.edad, superheroe.estado);
        }else{
            id_en_lista=true;
            fprintf(auxiliar,ESCRITURA,superheroe.ID,superheroe.nombre,edad,estado);
        }

        leidos=fscanf(superheroes,LECTURA,&superheroe.ID,superheroe.nombre,&superheroe.edad,&superheroe.estado);
    }

    if(!id_en_lista){
        printf("Oh No ha habido un problema!!\n");
        printf("No puedes modificar a alguien quien no existe, vive solo en tu imaginacion , si queres saber quien esta en servicio usa el comando -listar- o para mas informacion usa el comando -ayuda-\n");
    }

    fclose(superheroes);
    fclose(auxiliar);
    rename(ARCHIVO_AUX,argv[5]);
    return TODO_BENE;
}

int agregar_superheroe(int argc, char* argv[]){

    FILE* superheroes = fopen(argv[6],LEER);
    if(!superheroes){
        printf("No puedo abrir el archivo%s", argv[6]);
        //crea 
        FILE* superheroes = fopen(argv[6],ABRIR_AL_FINAL);
        if(!superheroes){
            printf("No puedo abrir el archivo");
            return ERROR_ARCHIVO;
        }
    }

    FILE* auxiliar = fopen(ARCHIVO_AUX,ESCRIBIR);
    if(!auxiliar){
        printf("No se pudo abrir el auxiliar");
        fclose(superheroes);
        return ERROR_ARCHIVO;
    }

    superheroe_t superheroe;
    int id_buscado = atoi(argv[2]);
    int edad = atoi(argv[4]);
    char* argumento_estado = argv[5];

    if(!verificar_edad(edad)){
        return ERROR_ARCHIVO;
    }

    if(!verificar_id(id_buscado)){
        obtener_informacion(ID_NEGATIVO); 
        return ERROR_ARCHIVO;  
    }     

   char estado= verificar_estado(argumento_estado);
    if(estado!=MUERTO && estado!=VIVO){
        return ERROR_ARCHIVO;
    }

    bool id_agregado=false;

    int leidos=fscanf(superheroes,LECTURA,&superheroe.ID,superheroe.nombre,&superheroe.edad,&superheroe.estado);

    while (leidos==CANT_VAR_XLINEA){
        if(id_buscado==superheroe.ID){
            obtener_informacion(ID_REPETIDO);
            return ERROR_ARCHIVO;
        }else if(id_buscado>superheroe.ID){
            fprintf(auxiliar,ESCRITURA,superheroe.ID,superheroe.nombre, superheroe.edad, superheroe.estado);
        }else if(id_buscado<superheroe.ID){
            if(!id_agregado){
                fprintf(auxiliar,ESCRITURA,id_buscado,argv[3], edad, estado);
                fprintf(auxiliar,ESCRITURA,superheroe.ID,superheroe.nombre, superheroe.edad, superheroe.estado);
                id_agregado=true;
            }else{
                fprintf(auxiliar,ESCRITURA,superheroe.ID,superheroe.nombre, superheroe.edad, superheroe.estado);
            }
        }else if(id_buscado==superheroe.ID){
           obtener_informacion(ESTADO_NO_CORRECTO);
        }
        leidos=fscanf(superheroes,LECTURA,&superheroe.ID,superheroe.nombre,&superheroe.edad,&superheroe.estado);
    }
        
    if(!id_agregado){
        fprintf(auxiliar,ESCRITURA,id_buscado,argv[3], edad, estado);
    }

    printf("*****Se agrego con exito el superheroe %s a la lista*****\n",argv[3]);
    fclose(superheroes);
    fclose(auxiliar);
    rename(ARCHIVO_AUX,argv[6]);
    return 0;
    }

void  obtener_informacion(int estado){

	if(estado==FALTA_COMANDO){
		printf("No escribiste ningun comando, si necesitas ayuda la linea; ./ejecutable ayuda \n");
	}else if(estado==CONT_FALTA_DATOS){
		printf("cantidad de parametros no correcta al contactar , recuerde el comando; ./ejecutable contactar ID archivo.csv \n");
	}else if(estado==MOD_FALTA_DATOS){
		printf("cantidad de parametros no correctos al modificar , recuerde la linea de comando;./ejecutable modificar ID EDAD ESTADO archivo.csv\n");
	}else if(estado==ID_NEGATIVO){
        printf("ID no es correcto debe ser del 0 al 100\n");
    }else if(estado==AGR_FALTA_DATOS){
        printf("cantidad de parametros no correctos al agregar , recuerde la linea de comando;./ejecutable agregar ID NOMBRE EDAD ESTADO archivo.csv\n");
	}else if(estado==AYUDA){
		printf("Lineas de Comandos:\n");
        printf(" Listar_Superheroes: ./ejecutable listar archivo.csv\n");
        printf(" Contactar_Superheroe: ./ejecutable contactar ID archivo.csv\n");
        printf(" Modificar_Status_Superheroe: ./ejecutable modificar ID EDAD ESTADO archivo.csv\n");
        printf(" Agregar_Superheroe: ./ejecutable agregar ID NOMBRE EDAD ESTADO archivo.csv.\n");
	}else if(estado==COMANDO_NO_CORRECTO){
        printf("No te entiendo , ese comando no existe, si necesitas ayuda la linea; ./ejecutable ayuda\n");
	}else if(estado==EDAD_NO_CORRECTA){
        printf("Edad ingresada no esta en el parametro recuerde que debe ser mayor a 0 y menor a 100\n");
    }else if(estado==ESTADO_NO_CORRECTO){
        printf("Tiene que escribir vivo o muerto\n");
    }else if(estado==ID_REPETIDO){
        printf("Ese ID ya esta en uso , intenta con otro numero, si no sabes cuales estan en uso podes usar el comando; ./ejecutable listar o si necesitas ayuda ./ejecutable ayuda");
    }
}
