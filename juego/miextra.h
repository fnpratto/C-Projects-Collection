#ifndef __MIEXTRA_H__
#define __MIEXTRA_H__

#define MAX_LASERS 100
#define MAX_ROBOTS 10
#define MAX_PERSONAJES 10
#define MAX_PINZAS 100
#define MAX_SUPERTRAJES 10

//contraseña
static const int RES_CORRECTA_LONG_LASER = 3;
static const int RES_INCORRECTA_LONG_LASER = 5;

//CUADRANTES
static const int CUADRANTE_1 =1; 
static const int CUADRANTE_2 =2; 
static const int CUADRANTE_3 =3; 
static const int CUADRANTE_4 =4; 

/*PERSONAJES*/
static const char MR_INCREIBLE ='I'; 
static const char VIOLETA ='V'; 
static const char DASH ='D'; 
static const char ELASTICGIRL ='E'; 

/*MOVIMIENTOS*/
static const char ARRIBA ='W';
static const char ABAJO ='S';
static const char DERECHA ='D';
static const char IZQUIERA ='A';
static const char ACTIVAR_PODER ='C';

//ID (El campo id_personaje_actual comienza en 1)
static const int ID_MR_INCREIBLE =4; 
static const int ID_VIOLETA =2; 
static const int ID_DASH =3;
static const int ID_ELASTICGIRL =1;

//POSICION EN EL VECTOR

static const int POS_MR_INCREIBLE =3; 
static const int POS_VIOLETA =1; 
static const int POS_DASH =2;
static const int POS_ELASTICGIRL =0;

//CANTIDAD_DE_MOVIMIENTOS
static const int CANT_MOV_ELAST =25; 
static const int CANT_MOV_VIOLETA =30; 
static const int CANT_MOV_DASH =20; 
static const int CANT_MOV_MRI =15; 

//OBSTACULOS
static const char ROBOT ='R';
static const char LASER ='L';
static const char PINZA ='P';
static const char SALIDA ='S';
static const char SUPERTRAJE ='T';
static const char VACIO ='-';

//ESTADO DEL JUEGO
static const int GANO_EL_JUEGO = 1;
static const int PERDIO_EL_JUEGO = -1;
static const int SIGUE_EN_JUEGO = 0;

//COORDENADA SALIDA
static const int COL_SALIDA = 19;
static const int FIL_SALIDA = 0;

//TABLERO
static const int MAX_TABLERO = 20;
static const int MIN_TABLERO = 0;
static const int MITAD_TABLERO = 10;

//VALORES
static const int VALOR_NO_VALIDO = -12;
static const int CANT_MOV_PODER = 5;
static const int CANT_DE_PINZAS = 16;


typedef struct coordenada{
    int fila;
    int columna;
} coordenada_t;

typedef struct robot{
    coordenada_t posicion;
    coordenada_t lasers[MAX_LASERS];
    int tope_lasers;
} robot_t;

typedef struct supertraje{
    coordenada_t posicion;
    int cuadrante;
    bool recolectado;
    bool usado;
} supertraje_t;

typedef struct personaje{
    bool poder_activado;
    bool tiene_supertraje;
    coordenada_t posicion;
    int movimientos;
    int movimientos_con_poder;
    int cuadrante_inicial;
} personaje_t;

typedef struct juego{
    personaje_t personajes [MAX_PERSONAJES];
    int tope_personajes;
    robot_t robots [MAX_ROBOTS];
    int tope_robots;
    coordenada_t pinzas [MAX_PINZAS];
    int tope_pinzas;
    supertraje_t supertrajes [MAX_SUPERTRAJES];
    int tope_supertraje;
    int longitud_laser;
    int id_personaje_actual;
} juego_t;

/*COORDENADAS*/
//PRE: 
//POST: True si esta en el tablero (mayor/ igual a 0 y menor a 20)
bool esta_en_rango(int coordenada);

//PRE:Dar numero del 1 al 4 inclusive 
//POST:Da un numero random que pertenesca a la posicion del cuadrante ingresado
int coordenada_fila_segun_cuadrante(int i);

//PRE:Dar numero del 1 al 4 inclusive
//POST:Da un numero random que pertenesca a la posicion del cuadrante ingresado
int coordenada_colummna_segun_cuadrante(int i);

//PRE: Se debe mandar un char correspondiente con el tipo de elemento que es
//POST: devuelve true si posicion esta ocupada
bool posicion_ocupada(juego_t* juego ,int fila ,int columna,char tipo);

//PRE: 
//POST:Da 1 o 2
int coordenada_rango_robot();

//PRE: 
//POST: True si las coordenadas coinciden con las coordenadas de la salida
bool hay_salida(int i, int j);

//PRE: 
//POST: True si las coordenadas coinciden con las coordenadas de los robots
bool hay_robot(juego_t* juego, int fil, int col);

//PRE: 
//POST: True si las coordenadas coinciden con las coordenadas de los lasers
bool hay_laser(juego_t* juego, int fil, int col); 

//PRE: 
//POST: True si las coordenadas coinciden con las coordenadas de la salida
bool hay_pinza(juego_t* juego, int fil, int col);

//PRE: 
//POST: Da un valor negativo si no coinciden con las coordenadas de un traje o Devuelve el id del traje encontrado     
int hay_traje(juego_t* juego,int fil, int col);

/*LASERS*/
//PRE: Tienen que estar inicializado los lasers
//POST: Devuelve un numero que representa la posicion que estan los lasers en ese turno
int figura_anterior(juego_t* juego , int i);

//PRE: 
//POST: Guarda posiciones del laser que no esten ocupadas por un robot o salida
void figura_uno (juego_t* juego, int robot);

//PRE: 
//POST: Guarda posiciones del laser que no esten ocupadas por un robot o salida
void figura_dos (juego_t* juego, int robot);

//PRE: 
//POST: Guarda posiciones del laser que no esten ocupadas por un robot o salida
void figura_tres (juego_t* juego, int robot);

//PRE: 
//POST: Guarda posiciones del laser que no esten ocupadas por un robot o salida
void figura_cuatro (juego_t* juego, int robot);

//PRE: 
//POST: Guarda posiciones del laser que no esten ocupadas por un robot o salida
void figura_cinco (juego_t* juego, int robot);

//PRE: 
//POST: Guarda posiciones del laser que no esten ocupadas por un robot o salida
void figura_seis (juego_t* juego, int robot);

//PRE: 
//POST: Guarda posiciones del laser mientras que las posiciones no esten ocupadas por un robot o salida
void figura_siete (juego_t* juego, int robot);

//PRE: 
//POST: Guarda posiciones del laser mientras que las posiciones no esten ocupadas por un robot o salida
void figura_ocho (juego_t* juego, int robot);

//PRE: 
//POST: Si true devuelve 3 sino devuelve 5
int LongitudLaser(bool contrasenia_completa);


/*SUPERPODERES*/

//PRE: Tienen que estar inicializados los personajes y trajes
//POST: Hace que dash se traslade al cuarto cuadrante.
void activar_poder_dash(juego_t* juego);

//PRE: Tienen que estar inicializados los personajes y trajes
//POST: Chequea que el poder sea habil para usar
bool poder_elastigirl_activado(juego_t* juego);

//PRE: Tienen que estar inicializados los personajes y trajes
//POST: Chequea que el poder sea habil para usar
bool poder_violeta_activado(juego_t* juego);

//PRE: Tienen que estar inicializados los personajes y trajes
//POST: Chequea que el poder sea habil para usar
bool poder_mrincreible_activado(juego_t* juego);

//PRE: Tienen que estar inicializados los personajes y trajes
//POST: cambia las condiciones para que se pueda usar los poderes
void recoger_traje( juego_t* juego, int supertraje_encontrado);

//PRE: Tienen que estar inicializados los personajes y trajes
//POST: Chequea que el poder sea habil para usar
void activar_poder(juego_t *juego);

//PRE: Tienen que estar inicializados las pinzas y personajes
//POST: Mueve a posicion de cuadrante inicial que no sea la salida
void mover_posicion_pinzas(juego_t *juego);

//PRE: Tiene que pasarle dos parametros dentro del tablero y estar inicializado los trajes, robots, personajes y lasers 
//POST: segun la posicion va a cambiar personaje, quedarse sin movimiento , ganar o nada.
void chequear_posicion_ocupada(juego_t *juego,int fil, int col);

/*INICIALIZAR*/

/*MATRIZ*/

//PRE: se le deben pasar parametros de topes dentro del maximo de la matriz
//POST: 
void inicializar_matriz(char matriz[MAX_LASERS][MAX_LASERS],int tope_columna, int tope_fila);

//PRE: 
//POST:
void inicializar_lasers(juego_t* juego, bool contrasenia_completa);

//PRE: 
//POST:
void inicializar_personajes(juego_t* juego);

//PRE: 
//POST:
void inicializar_pinzas(juego_t* juego);

//PRE: 
//POST:
void inicializar_traje(juego_t* juego);

//PRE: 
//POST:
void inicializar_robot(juego_t* juego);

//PRE: Tienen que estar inicializados las pinzas,robot, personajes, matriz y traje
//POST: Guarda todas las posiciones en una matriz
void guardar_posiciones(juego_t juego, char matriz[MAX_LASERS][MAX_LASERS]);


/*MOVIMIENTO USUARIO*/

//PRE: El id_personaje_actual tiene que ser de 0 a 3
//POST: Aumenta el id_personaje_actual
void cambiar_personaje(juego_t *juego);

//PRE: Tienen que estar inicializados los lasers
//POST:
void mover_lasers(juego_t *juego);

//PRE: El movimiento tiene que ser 'A','W', 'S','D','C' y Tienen que estar inicializados las pinzas,robot, personajes, matriz y traje
//POST: Si hay movimientos Se mueve o activa el poder e se disminuye un movimiento 
void caminar_por_mapa(juego_t *juego, char movimiento);



#endif /* __MIEXTRA_H__ */