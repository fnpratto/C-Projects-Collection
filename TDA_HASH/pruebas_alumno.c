#include "pa2m.h"
#include "src/hash.h"
#include <stdlib.h>

#define CAPACIDAD 10

typedef struct pokemon {
	char nombre[10];
	int nivel;
	int dex, str, spc, spd;
} pokemon_t;

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}

void creacion_hash()
{
	hash_t *hash = hash_crear(CAPACIDAD);

	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "Al crear hash la cantidad de elementos es 0");
	pa2m_afirmar(
		!hash_obtener(hash, "X"),
		"Devuelve null al buscar un elemento que no esta en la lista");
	pa2m_afirmar(
		!hash_contiene(hash, "x"),
		"Devuelve null al buscar un elemento que no esta en la lista");
	pa2m_afirmar(
		!hash_quitar(hash, "x"),
		"Devuelve null al buscar un elemento que no esta en la lista");

	hash_destruir(hash);
}

void insertar_elemento_y_encontrarlo()
{
	hash_t *hash = hash_crear(CAPACIDAD);

	char *clave1 = "uno", *valor1 = "a";
	char *clave2 = "dos", *valor2 = "b";
	char *clave3 = "tres", *valor3 = "c";
	char *clave4 = "cuatro", *valor4 = "d";
	char *clave5 = "cinco";

	hash_insertar(hash, clave1, valor1, NULL);
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "se inserta correctamente un elemento");
	pa2m_afirmar(hash_contiene(hash, clave1), "y se puede encontrar");
	pa2m_afirmar(hash_obtener(hash, clave1) == valor1,
		     "me devuelve el valor si lo busco con la clave dada");

	hash_insertar(hash, clave2, valor2, NULL);
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "se inserta correctamente un nuevo elemento");
	pa2m_afirmar(hash_contiene(hash, clave2), "y se puede encontrar");
	pa2m_afirmar(hash_obtener(hash, clave2) == valor2,
		     "me devuelve el valor si lo busco con la clave dada");

	hash_insertar(hash, clave3, valor3, NULL);
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "se inserta correctamente un nuevo elemento");
	pa2m_afirmar(hash_contiene(hash, clave3), "y se puede encontrar");
	pa2m_afirmar(hash_obtener(hash, clave3) == valor3,
		     "me devuelve el valor si lo busco con la clave dada");

	hash_insertar(hash, clave4, valor4, NULL);
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "se inserta correctamente un nuevo elemento");
	pa2m_afirmar(hash_contiene(hash, clave4), "y se puede encontrar");
	pa2m_afirmar(hash_obtener(hash, clave4) == valor4,
		     "me devuelve el valor si lo busco con la clave dada");

	pa2m_afirmar(!hash_contiene(hash, clave5),
		     "Un elemento no insertado no se puede encontrar");
	pa2m_afirmar(hash_obtener(hash, clave5) == NULL,
		     "me devuelve el valor si lo busco con la clave dada");

	hash_destruir(hash);
}

void insertar_misma_clave_y_reemplazarlo()
{
	hash_t *hash = hash_crear(CAPACIDAD);

	char *clave1 = "uno", *valor1 = NULL, *valor2 = "b";

	hash_insertar(hash, clave1, valor1, NULL); // se puede usar anteriorr
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "se inserta correctamente un elemento null");
	pa2m_afirmar(hash_contiene(hash, clave1), "y se puede encontrar");
	pa2m_afirmar(hash_obtener(hash, clave1) == valor1,
		     "me devuelve el valor si lo busco con la clave dada");

	hash_insertar(hash, clave1, valor2, NULL);
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "se reemplaza y la cantidad sigue igual");
	pa2m_afirmar(!hash_contiene(hash, clave1), " se puede encontrar");
	pa2m_afirmar(
		hash_obtener(hash, clave1) == valor2,
		"se devuelve el valor nuevo si lo busco con la clave nula");

	hash_destruir(hash);
}

void insertar_NULL_y_encontrarlo()
{
	hash_t *hash = hash_crear(CAPACIDAD);

	char *clave1 = "uno", *valor1 = NULL;
	char *clave2 = NULL, *valor2 = "b";

	hash_insertar(hash, clave1, valor1, NULL);
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "se inserta correctamente un elemento null");
	pa2m_afirmar(hash_contiene(hash, clave1), "y se puede encontrar");
	pa2m_afirmar(hash_obtener(hash, clave1) == valor1,
		     "me devuelve el valor si lo busco con la clave dada");

	hash_insertar(hash, clave2, valor2, NULL);
	pa2m_afirmar(
		hash_cantidad(hash) == 1,
		" no se puede insertar correctamente un nuevo elemento si la clave es nula");
	pa2m_afirmar(!hash_contiene(hash, clave2), "y no se puede encontrar");
	pa2m_afirmar(hash_obtener(hash, clave2) == NULL,
		     "no me devuelve el valor si lo busco con la clave nula");

	hash_destruir(hash);
}

void quitar_hash()
{
	hash_t *hash = hash_crear(CAPACIDAD);

	char *clave1 = "uno", *valor1 = "a";
	char *clave2 = "dos", *valor2 = "b";
	char *clave3 = "tres", *valor3 = "c";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);
	hash_insertar(hash, clave3, valor3, NULL);

	pa2m_afirmar(hash_cantidad(hash) == 3, "se inserta correctamente");

	hash_quitar(hash, clave1);
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "se quita correctamente un elemento");
	pa2m_afirmar(!hash_contiene(hash, clave1), "y no se puede encontrar");
	pa2m_afirmar(!hash_obtener(hash, clave1),
		     "no me devuelve el valor si lo busco con la clave dada");
	pa2m_afirmar(!hash_quitar(hash, clave1),
		     "no se puede quitar elemento ya quitado");

	hash_quitar(hash, clave2);
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "se quita correctamente un elemento");
	pa2m_afirmar(!hash_contiene(hash, clave1), "y no se puede encontrar");
	pa2m_afirmar(!hash_obtener(hash, clave1),
		     "no me devuelve el valor si lo busco con la clave dada");

	hash_quitar(hash, clave3);
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "se quita correctamente un elemento");
	pa2m_afirmar(!hash_contiene(hash, clave1), "y no se puede encontrar");
	pa2m_afirmar(!hash_obtener(hash, clave1),
		     "no me devuelve el valor si lo busco con la clave dada");

	pa2m_afirmar(
		hash_quitar(hash, clave1) == NULL,
		"no se puede eliminar un elemento que no esta en la tabla");
	pa2m_afirmar(hash_cantidad(hash) == 0, "sigue vacia la lista");

	hash_destruir(hash);
}
/*void liberar_memoria_en_quitar()
{
	hash_t *hash = hash_crear(CAPACIDAD);

	char *clave1 = "uno", *valor1 = malloc(sizeof(char)),
	     *valor2 = malloc(sizeof(char));

	hash_insertar(hash, clave1, valor1, NULL); // se puede usar anteriorr
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "se inserta correctamente un elemento null");
	pa2m_afirmar(hash_contiene(hash, clave1), "y se puede encontrar");
	pa2m_afirmar(hash_obtener(hash, clave1) == valor1,
		     "me devuelve el valor si lo busco con la clave dada");

	hash_insertar(hash, clave1, valor2, NULL);
	pa2m_afirmar(
		hash_cantidad(hash) == 1,
		"se reemplaza, se libera memoria y la cantidad sigue igual");
	pa2m_afirmar(hash_contiene(hash, clave1), " se puede encontrar");
	pa2m_afirmar(
		hash_obtener(hash, clave1) == valor2,
		"se devuelve el valor nuevo si lo busco con la clave nula");

	hash_destruir(hash);
}*/

bool no_son_iguales(const char *clave, void *elemento, void *elemento1)
{
	return (elemento == elemento1);
}

void funcionamiento_iterador_funcion_comparadora()
{
	hash_t *hash = hash_crear(CAPACIDAD);

	char *clave1 = "2452", *valor1 = "aa";
	char *clave2 = "2352", *valor2 = "bb";

	hash_insertar(hash, clave1, valor1, NULL);
	hash_insertar(hash, clave2, valor2, NULL);

	pa2m_afirmar(hash_con_cada_clave(hash, NULL, valor1) == 0,
		     "No itera con funcion null");
	pa2m_afirmar(hash_con_cada_clave(hash, no_son_iguales, valor1) == 1,
		     "Itera 1 elementos");
	pa2m_afirmar(hash_con_cada_clave(hash, no_son_iguales, valor2) == 2,
		     "Itera 2 elementos");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== XXX ========================");
	pa2m_nuevo_grupo("Pruebas de creacion");
	creacion_hash();

	pa2m_nuevo_grupo("Insercion, Busqueda");
	insertar_elemento_y_encontrarlo();
	pa2m_nuevo_grupo("Insercion, Busqueda NULL");
	insertar_NULL_y_encontrarlo();

	pa2m_nuevo_grupo("Pruebas sobre quitar");
	quitar_hash();
	pa2m_nuevo_grupo("Pruebas de borrado y memoria");
	//liberar_memoria_en_quitar();

	pa2m_nuevo_grupo("\nPruebas de iterador externo / hash_con_cada_clave");
	funcionamiento_iterador_funcion_comparadora();

	return pa2m_mostrar_reporte();
}