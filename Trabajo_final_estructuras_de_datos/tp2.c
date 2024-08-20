#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "src/menu.h"
#include "src/hash/hash.h"
#include "src/tp1/tp1.h"
#include "src/texto/textos.h"

#define MAX_LINEA 200
#define CAPACIDAD_MINIMA 50
#define SALIR01 "salir"
#define SALIR02 "exit"
#define SALIR03 "S"
#define SALIR04 "SALIR"

#define ESTADO01 "estado"
#define ESTADO02 "E"
#define ESTADO03 "ESTADO"

#define ACTIVAR01 "activar"
#define ACTIVAR02 "A"
#define ACTIVAR03 "ACTIVAR"

#define MOSTRAR01 "mostrar"
#define MOSTRAR02 "M"
#define MOSTRAR03 "MOSTRAR"

#define LISTAR02 "listar"
#define LISTAR01 "L"
#define LISTAR03 "LISTAR"

#define CARGAR01 "cargar"
#define CARGAR02 "C"
#define CARGAR03 "agregar"
#define CARGAR04 "CARGAR"

#define AYUDAR03 "ayuda"
#define AYUDAR02 "help"
#define AYUDAR01 "H"
#define AYUDAR04 "AYUDA"

#define DESTRUIR01 "destruir"
#define DESTRUIR02 "D"
#define DESTRUIR03 "DESTRUIR"

struct menu_hospitales {
	bool salir;
	size_t cantidad_ingresada;
	menu_t *menu;
	hash_t *hospitales;
	size_t id_hospital_activo;
};

struct hospital_con_id {
	char *id;
	hospital_t *hospital;
	const char *nombre;
};

void liberar_hospital(void *_actual)
{
	if (!_actual)
		return;
	struct hospital_con_id *actual = _actual;
	free((char *)actual->nombre);
	free(actual->id);
	if (actual->hospital)
		hospital_destruir(actual->hospital);
	free(actual);
}

void menu_hospitales_destruir(struct menu_hospitales *menu_hospitales)
{
	if (!menu_hospitales)
		return;
	menu_destruir(menu_hospitales->menu);

	hash_destruir_todo(menu_hospitales->hospitales, liberar_hospital);

	free(menu_hospitales);
}

bool salir(void *_datos)
{
	if (!_datos)
		return false;

	struct menu_hospitales *menu_hospitales = _datos;
	imprimir_salida();
	menu_hospitales->salir = true;
	return true;
}

char *id_a_string(size_t id)
{
	if (!id)
		return NULL;

	char *str_id = (char *)malloc(21);
	if (!str_id)
		return NULL;

	sprintf(str_id, "%zu", id);
	return str_id;
}

char *leer_linea(char *donde, int maximo)
{
	donde[0] = 0;
	char *resultado = fgets(donde, maximo, stdin);

	if (resultado)
		resultado[strlen(resultado) - 1] = 0;

	return resultado;
}

char *id_hospital_con_id(struct hospital_con_id *hospital)
{
	if (!hospital)
		return NULL;
	return hospital->id;
}

bool hospital_activo(char *id_actual, char *id_h_activo)
{
	if (!id_actual || !id_h_activo)
		return false;
	return (strcmp(id_actual, id_h_activo) == 0);
}

bool imprimir_hospitales(const char *nombre, void *_actual, void *_menu)
{
	if (!nombre || !_actual || !_menu)
		return false;
	struct hospital_con_id *actual = _actual;
	struct menu_hospitales *menu = _menu;
	char *resultado = id_a_string(menu->id_hospital_activo);
	if (hospital_activo(actual->id, resultado)) {
		printf("    Hospital id:%s. Nombre: %s [ESTA ACTIVO]\n",
		       actual->id, actual->nombre);
	} else {
		printf("    Hospital id: %s. Nombre: %s [NO ESTA ACTIVO]\n",
		       actual->id, actual->nombre);
	}
	free(resultado);
	return true;
}

bool mostrar_estado(void *_datos)
{
	if (!_datos)
		return false;
	struct menu_hospitales *datos = _datos;
	hash_con_cada_clave(datos->hospitales, imprimir_hospitales,
			    (void *)datos);
	return true;
}

bool imprimir_nombres_pokemones(pokemon_t *p, void *aux)
{
	if (!p)
		return false;
	printf("\n");
	printf("NOMBRE:%s\n", pokemon_nombre(p));
	printf("-------------------------------------------\n");
	return true;
}

bool imprimir_pokemones(pokemon_t *p, void *aux)
{
	if (!p)
		return false;
	printf("-------------------------------------------\n");
	printf("ID:%li\n", pokemon_id(p));
	printf("SALUD:%li\n", pokemon_salud(p));
	printf("NOMBRE DE ENTRENADOR %s\n", pokemon_entrenador(p));
	printf("NOMBRE:%s\n", pokemon_nombre(p));
	printf("-------------------------------------------\n");
	return true;
}

bool mostrar_nombres_pokemones(void *_datos)
{
	if (!_datos)
		return false;
	struct menu_hospitales *datos = _datos;
	char *resultado = id_a_string(datos->id_hospital_activo);
	struct hospital_con_id *hospital =
		hash_obtener(datos->hospitales, resultado);
	free(resultado);
	if (!hospital)
		return false;
	hospital_a_cada_pokemon(hospital->hospital, imprimir_nombres_pokemones,
				NULL);
	return true;
}

//Muestra un listado detallado de todos los pokemones en el hospital.
bool mostrar_pokemones(void *_datos)
{
	if (!_datos)
		return false;
	struct menu_hospitales *datos = _datos;
	char *resultado = id_a_string(datos->id_hospital_activo);
	struct hospital_con_id *hospital =
		hash_obtener(datos->hospitales, resultado);
	free(resultado);
	if (!hospital)
		return false;
	hospital_a_cada_pokemon(hospital->hospital, imprimir_pokemones, NULL);
	return true;
}

/*void leer_numero(int numero) {
    char num[MAX_LINEA];
    fgets(num, sizeof(num), stdin);
    numero = atoi(num);
}*/

bool activar_hospital(void *_datos)
{
	if (!_datos)
		return false;
	struct menu_hospitales *datos = _datos;
	printf("    Hola! Ingrese el numero de identificacion del hospital que desea activar:\n");
	int num;
	//leer_numero(num);
	scanf("%d", &num);
	char *resultado = id_a_string((size_t)num);
	if (hash_contiene(datos->hospitales, resultado)) {
		datos->id_hospital_activo = (size_t)num;
		printf("se activo correctamente\n");
	} else {
		printf("No se activo correctamente\n");
	}
	free(resultado);
	return true;
}

struct hospital_con_id *crear_hospital_con_id(const char *nombre, size_t id)
{
	hospital_t *hospital = hospital_crear_desde_archivo(nombre);
	if (hospital == NULL)
		return NULL;

	struct hospital_con_id *hospital_id =
		malloc(sizeof(struct hospital_con_id));

	if (hospital == NULL) {
		return NULL;
	}
	hospital_id->hospital = hospital;

	hospital_id->nombre = duplicar_clave(nombre);
	char *resultado = id_a_string((size_t)id);
	hospital_id->id = duplicar_clave(resultado);
	free(resultado);

	return hospital_id;
}

bool cargar_hospital(void *_datos)
{
	struct menu_hospitales *menu = _datos;

	printf("    Inserte nombre del hospital que desea ingresar:\n");
	char nombre[MAX_LINEA];
	leer_linea(nombre, MAX_LINEA);

	size_t id = menu->cantidad_ingresada + 1;
	struct hospital_con_id *hospital_con_id =
		crear_hospital_con_id(nombre, id);

	if (!hospital_con_id) {
		imprimir_error();
		return false;
	}

	void *aaux = NULL;
	void *aux = hash_insertar(menu->hospitales, hospital_con_id->id,
				  hospital_con_id, &aaux);
	if (!aux) {
		liberar_hospital(hospital_con_id); // destruir hospital
		imprimir_error();
		return false;
	} else {
		menu->cantidad_ingresada++;
		printf("\n");
		printf("    Se cargo correctamente el hospital ID: %s NOMBRE: %s \n",
		       hospital_con_id->id, hospital_con_id->nombre);
		imprimir_cargar();
	}
	return true;
}
bool destruir_hospital(void *_datos)
{
	if (!_datos)
		return false;
	struct menu_hospitales *datos = _datos;
	char *resultado = id_a_string(datos->id_hospital_activo);
	struct hospital *hospital = hash_obtener(datos->hospitales, resultado);
	if (hospital)
		liberar_hospital(hospital);
	void *aux = hash_quitar(datos->hospitales, resultado);
	free(resultado);
	if (aux) {
		datos->id_hospital_activo = 99;
		printf("\n");
		printf("			Has destruido el hospital con exito :)\n");
		printf("	Felicitaciones ha dejado un par de pokemones en la calle\n");
		printf("\n");
	} else {
		printf("error en eliminar");
	}
	return true;
}

bool mostrar_ayuda(void *_datos)
{
	if (!_datos)
		return false;
	struct menu_hospitales *datos = _datos;
	imprimir_problema();
	menu_mostrar(datos->menu);

	return true;
}

void menu_agregar_sinonimos(menu_t *menu)
{
	if (!menu)
		return;
	menu_agregar_sinonimo(
		menu, SALIR01,
		"Sale del programa (obviamente que libera toda la memoria).",
		salir);
	menu_agregar_sinonimo(
		menu, SALIR02,
		"Sale del programa (obviamente que libera toda la memoria).",
		salir);
	menu_agregar_sinonimo(
		menu, SALIR03,
		"Sale del programa (obviamente que libera toda la memoria).",
		salir);
	menu_agregar_sinonimo(
		menu, ESTADO01,
		"Muestra un listado con los hospitales cargados (y el activo, si alguno).",
		mostrar_estado);
	menu_agregar_sinonimo(
		menu, ESTADO02,
		"Muestra un listado con los hospitales cargados (y el activo, si alguno).",
		mostrar_estado);
	menu_agregar_sinonimo(
		menu, ACTIVAR01,
		"Pide un número de identificación y activa el hospital.",
		activar_hospital);
	menu_agregar_sinonimo(
		menu, ACTIVAR02,
		"Pide un número de identificación y activa el hospital.",
		activar_hospital);
	menu_agregar_sinonimo(
		menu, MOSTRAR01,
		"Muestra un listado detallado de todos los pokemones en el hospital.",
		mostrar_pokemones);
	menu_agregar_sinonimo(
		menu, MOSTRAR02,
		"Muestra un listado detallado de todos los pokemones en el hospital.",
		mostrar_pokemones);
	menu_agregar_sinonimo(
		menu, LISTAR01,
		"Muestra un listado con los nombres de todos los pokemones",
		mostrar_nombres_pokemones);
	menu_agregar_sinonimo(
		menu, LISTAR02,
		"Muestra un listado con los nombres de todos los pokemones",
		mostrar_nombres_pokemones);
	menu_agregar_sinonimo(menu, CARGAR01, "Carga un hospital al sistema",
			      cargar_hospital);
	menu_agregar_sinonimo(menu, CARGAR02, "Carga un hospital al sistema",
			      cargar_hospital);
	menu_agregar_sinonimo(menu, CARGAR03, "Carga un hospital al sistema",
			      cargar_hospital);
	menu_agregar_sinonimo(
		menu, AYUDAR01,
		"Muestra un menú de ayuda con los comandos disponibles.",
		mostrar_ayuda);
	menu_agregar_sinonimo(
		menu, AYUDAR02,
		"Muestra un menú de ayuda con los comandos disponibles.",
		mostrar_ayuda);
	menu_agregar_sinonimo(
		menu, AYUDAR03,
		"Muestra un menú de ayuda con los comandos disponibles.",
		mostrar_ayuda);
	menu_agregar_sinonimo(menu, DESTRUIR01, "Destruye el hospital activo",
			      destruir_hospital);
	menu_agregar_sinonimo(menu, DESTRUIR02, "Destruye el hospital activo",
			      destruir_hospital);
}

void menu_agregar_opciones(menu_t *menu)
{
	if (!menu)
		return;
	menu_agregar_opcion(
		menu, SALIR04,
		"Sale del programa (obviamente que libera toda la memoria).",
		salir);
	menu_agregar_opcion(
		menu, ESTADO03,
		"Muestra un listado con los hospitales cargados (y el activo, si alguno).",
		mostrar_estado);
	menu_agregar_opcion(
		menu, ACTIVAR03,
		"Pide un número de identificación y activa el hospital.",
		activar_hospital);
	menu_agregar_opcion(
		menu, MOSTRAR03,
		"Muestra un listado detallado de todos los pokemones en el hospital.",
		mostrar_pokemones);
	menu_agregar_opcion(
		menu, LISTAR03,
		"Muestra un listado con los nombres de todos los pokemones",
		mostrar_nombres_pokemones);
	menu_agregar_opcion(menu, CARGAR04, "Carga un hospital al sistema",
			    cargar_hospital);
	menu_agregar_opcion(
		menu, AYUDAR04,
		"Muestra un menú de ayuda con los comandos disponibles.",
		mostrar_ayuda);
	menu_agregar_opcion(menu, DESTRUIR03, "Destruye el hospital activo",
			    destruir_hospital);
}

void inicializar_menu(struct menu_hospitales *menu_hospitales, menu_t *menu,
		      hash_t *hospitales)
{
	if (!menu_hospitales || !menu || !hospitales)
		return;
	menu_hospitales->salir = false;
	menu_hospitales->cantidad_ingresada = 0;
	menu_hospitales->menu = menu;
	menu_hospitales->hospitales = hospitales;
	menu_hospitales->id_hospital_activo = 99;
}

int main(int argc, char *argv[])
{
	imprimir_bienvenido();
	menu_t *menu = NULL;
	menu = menu_crear();
	if (!menu)
		return 0;

	hash_t *hospitales = hash_crear(CAPACIDAD_MINIMA);
	if (!hospitales)
		return 0;

	menu_agregar_opciones(menu);
	menu_agregar_sinonimos(menu);

	char linea[MAX_LINEA] = "";

	enum resultado_menu resultado = 0;

	struct menu_hospitales *menu_hospitales =
		malloc(sizeof(struct menu_hospitales));
	if (!menu_hospitales)
		return 0;
	inicializar_menu(menu_hospitales, menu, hospitales);

	menu_mostrar(menu);

	while (!menu_hospitales->salir) {
		printf("\n");
		printf("\n");
		printf("    ┌──❀*̥˚──◌──────────────────────────◌──❀*̥˚─┐   \n");
		printf("                                             \n");
		printf("        Ingrese un nuevo comando;");

		do {
			leer_linea(linea, MAX_LINEA);
		} while (strcmp(linea, "") == 0);

		printf("                                             \n");
		printf("    └◌───❀*̥˚───◌───────────────────────────❀*̥˚┘  \n");
		printf("\n");
		printf(" \n");

		resultado = menu_ejecutar_opcion(menu, linea, menu_hospitales);

		if (resultado == INEXISTENTE) {
			printf("Ese comando no existe.");

		} else if (resultado == ERROR) {
			printf("Error al ejecutar el comando");
		}
	}

	menu_hospitales_destruir(menu_hospitales);
	return 0;
}
