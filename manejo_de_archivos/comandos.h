#ifndef __COMANDOS_H__
#define __COMANDOS_H__

#define ESCRITURA "%i;%s;%i;%c\n"
#define LECTURA "%i;%[^;];%i;%c\n"
#define ARCHIVO_AUX "aux.csv"
#define MAX_NOMBRE 75
#define TRUE 0
//MODOS PARA ABRIR ARCHIVOS
#define LEER "r"
#define ESCRIBIR "w"
#define ABRIR_AL_FINAL "a"
//COMANDOS
#define LISTAR "listar"
#define CONTACTAR "contactar"
#define MODIFICAR "modificar"
#define AGREGAR "agregar"
#define AYUDAR "ayudar"
//ESTADOS
#define VIVO 'V'
#define MUERTO 'M'
#define S_VIVO "vivo"
#define S_MUERTO "muerto"
//CODIGOS
static int TODO_BENE = 0;
static int FALTA_COMANDO = 1;
static int CONT_FALTA_DATOS = 2;
static int MOD_FALTA_DATOS = 3;
//static int ID_NEGATIVO = 4;
static int AGR_FALTA_DATOS = 5;
static int AYUDA = 6;
static int COMANDO_NO_CORRECTO = 7;
//static int EDAD_NO_CORRECTA = 8;
//static int ESTADO_NO_CORRECTO = 9;
//static int ID_REPETIDO = 10;

typedef struct superheroe{
	int ID;
	char nombre[MAX_NOMBRE];
    int edad;
    char estado;
}superheroe_t;

//PRE: Los superhéroes deberán estar cargados de forma creciente según ID y de manera correcta
//POST:Se muestra por pantalla todos los superhéroes con su ID, nombre, edad y estado.
//COMANDO: ./ejecutable listar archivo.csv
int  listar_superheroes (int argc, char* argv[]);


//PRE: Los superhéroes deberán estar cargados de forma creciente según ID y de manera correcta
//POST:Se deberá mostrar por pantalla la información del superhéroe contactado muestra mensaje que logro contratarlo. es eliminado de la lista manteniendo el orden de ID de los demás superhéroes. En caso de que el ID ingresado no se encuentre entre los superhéroes, entonces se le avisa al usuario que no existe un superhéroe con ese ID y por lo tanto no puede contactarlo
//COMANDO:./ejecutable contactar ID archivo.csv	
int  contactar_superheroe(int argc, char* argv[]);


//PRE: Los superhéroes deberán estar cargados de forma creciente según ID y de manera correcta
//POST:Se deberá modificar el estado y la edad del superhéroe.si el ID ingresado no se encuentre entre los superhéroes, entonces se le avisa al usuario que no existe un superhéroe con ese ID y por lo tanto no puede modificarlo.
//COMANDO:./ejecutable modificar ID EDAD ESTADO archivo.csv
int   modificar_status_superheroe(int argc, char* argv[]);

//PRE: Los superhéroes deberán estar cargados de forma creciente según ID y de manera correcta
//POST:se agrega el superhéroe de forma ordenada según ID y mostrar un mensaje que le permita saber al usuario . En caso de que el archivo no exista, deberá ser creado.
//COMANDO: ./ejecutable agregar ID NOMBRE EDAD ESTADO archivo.csv.
int   agregar_superheroe(int argc, char* argv[]);

//PRE: Los superhéroes deberán estar cargados de forma creciente según ID y de manera correcta
//POST:Se informa al usuario cuales son los comandos disponibles, como utilizarlos, que hace cada uno y que errores estaria presentando la ejecuccion si se presenta
//COMANDO:./ejecutable ayuda 
void  obtener_informacion(int estado);

#endif /* __COMANDOS_H__ */