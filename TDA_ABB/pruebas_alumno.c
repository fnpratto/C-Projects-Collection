#include "src/abb.h"
#include "pa2m.h"

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

int comparar_int(void *_i1, void *_i2)
{
	int *i1 = _i1;
	int *i2 = _i2;
	return *i1 - *i2;
}

int comparar_char(void *_c1, void *_c2)
{
	char *c1 = _c1;
	char *c2 = _c2;

	return (*c1) - (*c2);
}

void creacion_abb()
{
	abb_t *abb = abb_crear(NULL);
	pa2m_afirmar(abb == NULL, "Un arbol sin funcion comparadora da NULL");
	abb_destruir(abb);

	abb = abb_crear(comparar_char);
	pa2m_afirmar(abb != NULL && abb_vacio(abb),
		     "Se puede crear un arbol y esta vacio");

	abb_destruir(abb);
}

void insertar_elemento_igual_y_encontrarlo()
{
	abb_t *abb = abb_crear(comparar_char);

	char a = 'a';
	char otro_a = 'a';

	abb_insertar(abb, &a);
	pa2m_afirmar(abb_buscar(abb, &a) == &a,
		     "se inserta correctamente y se puede encontrar");
	pa2m_afirmar(abb_buscar(abb, &a) == &otro_a,
		     "se inserta correctamente y se puede encontrar");
	pa2m_afirmar(abb_buscar(abb, &otro_a) == &otro_a,
		     "se inserta correctamente y se puede encontrar");

	abb_destruir(abb);
}

void insertar_elemento_y_encontrarlo()
{
	abb_t *abb = abb_crear(comparar_int);

	int p1 = 0;
	int p2 = 20;
	int p3 = 30;

	abb_insertar(abb, &p1);
	pa2m_afirmar(abb_tamanio(abb) == 1,
		     "se inserta correctamente y el tamanio de la lista es 1");

	abb_insertar(abb, &p2);
	pa2m_afirmar(abb_tamanio(abb) == 2,
		     "se inserta correctamente y el tamanio de la lista es 2");

	abb_insertar(abb, &p3);
	pa2m_afirmar(abb_tamanio(abb) == 3,
		     "se inserta correctamente y el tamanio de la lista es 3");

	int p4 = -10;
	int p5 = 200;

	abb_insertar(abb, &p4);
	pa2m_afirmar(abb_tamanio(abb) == 4, "se inserta un elemento menor");

	abb_insertar(abb, &p5);
	pa2m_afirmar(abb_tamanio(abb) == 5, "se inserta un elemento mayor");

	pa2m_afirmar(abb_buscar(abb, &p5) == &p5,
		     "se encuentra el que esta mas a la derecha (el mayor)");
	pa2m_afirmar(abb_buscar(abb, &p4) == &p4,
		     "se encuentra el que esta mas a la izquierda (el menor)");
	pa2m_afirmar(abb_buscar(abb, &p2) == &p2,
		     "se encuentra en un lugar random");

	abb_destruir(abb);
}

void insertar_NULL_y_encontrarlo()
{
	abb_t *abb = abb_crear(comparar_int);

	void *p1 = NULL;
	void *p2 = NULL;
	void *p3 = NULL;

	abb_insertar(abb, &p1);
	pa2m_afirmar(abb_tamanio(abb) == 1,
		     "se inserta correctamente y el tamanio de la lista es 1");

	abb_insertar(abb, &p2);
	pa2m_afirmar(abb_tamanio(abb) == 2,
		     "se inserta correctamente y el tamanio de la lista es 2");

	abb_insertar(abb, &p3);
	pa2m_afirmar(abb_tamanio(abb) == 3,
		     "se inserta correctamente y el tamanio de la lista es 3");

	pa2m_afirmar(abb_buscar(abb, &p1) == &p1,
		     "se encuentra en un lugar random");

	abb_destruir(abb);
}

void quitar_abb()
{
	abb_t *abb = abb_crear(comparar_int);

	for (int i = 0; i < 10; i++) {
		int p1 = i;
		abb_insertar(abb, &p1);
	}

	pa2m_afirmar(abb_tamanio(abb) == 10, "se inserta correctamente");

	abb_quitar(abb, "5");
	pa2m_afirmar(
		abb_tamanio(abb) == 9,
		"se quita 1 nodo correctamente y el tamanio de la lista es 9");

	abb_quitar(abb, "5");
	pa2m_afirmar(abb_tamanio(abb) == 8,
		     "se quita correctamente y el tamanio de la lista es 8");

	abb_quitar(abb, "8");
	abb_quitar(abb, "2");
	abb_quitar(abb, "3");
	pa2m_afirmar(
		abb_tamanio(abb) == 5,
		"se quita 3 elementos correctamente y el tamanio de la lista es 5");

	abb_destruir(abb);
}

int main()
{
	prueba_simple();

	pa2m_nuevo_grupo("Pruebas de creacion");
	creacion_abb();

	pa2m_nuevo_grupo("Insercion, Busqueda");
	insertar_elemento_y_encontrarlo();
	insertar_elemento_igual_y_encontrarlo();
	insertar_NULL_y_encontrarlo();

	pa2m_nuevo_grupo("Quitar");
	quitar_abb();

	return pa2m_mostrar_reporte();
}
