#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

const size_t ERROR = 0;

typedef struct nodo {
	void *elemento;
	void *siguiente;
} nodo_t;

typedef struct lista {
	size_t cantidad;
	nodo_t *nodo_inicio;
	nodo_t *nodo_fin;
} lista;

typedef struct lista_iterador {
	nodo_t *nodo_actual;
	lista_t *lista;
} lista_iterador;

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL)
		return NULL;

	nodo_t *nodo = malloc(sizeof(nodo_t) * 1);
	if (nodo == NULL)
		return NULL;
	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	if (lista->cantidad == 0) {
		lista->nodo_inicio = nodo;
	} else {
		lista->nodo_fin->siguiente = nodo;
	}

	lista->nodo_fin = nodo;
	(lista->cantidad)++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (lista == NULL)
		return NULL;

	if (posicion >= lista->cantidad) {
		return lista_insertar(lista, elemento);
	}

	nodo_t *nodo_agregar = malloc(sizeof(nodo_t) * 1);
	if (nodo_agregar == NULL)
		return NULL;

	nodo_agregar->elemento = elemento;
	nodo_agregar->siguiente = NULL;

	if (lista->nodo_inicio == NULL)
		lista->nodo_inicio = nodo_agregar;

	if (posicion == 0) {
		nodo_agregar->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_agregar;

	} else {
		nodo_t *nodo_actual = lista->nodo_inicio;

		for (int i = 0; i < (posicion - 1); i++)
			nodo_actual = nodo_actual->siguiente;

		nodo_agregar->siguiente = nodo_actual->siguiente;
		nodo_actual->siguiente = nodo_agregar;
	}

	(lista->cantidad)++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (lista_vacia(lista))
		return NULL;

	void *elemento_nodo_eliminado = lista->nodo_fin->elemento;

	if (lista->cantidad == 1) {
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		free(lista->nodo_inicio);
	} else {
		lista->nodo_fin = lista->nodo_inicio;

		for (int i = 0; i < (lista->cantidad) - 2; i++) {
			lista->nodo_fin = lista->nodo_fin->siguiente;
		}

		lista->nodo_fin->siguiente = NULL;
		free(lista->nodo_fin->siguiente);
	}

	(lista->cantidad)--;
	return elemento_nodo_eliminado;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (lista_vacia(lista))
		return NULL;

	if (posicion >= (lista->cantidad) - 1) {
		return lista_quitar(lista);
	}

	nodo_t *nodo_eliminado = lista->nodo_inicio;
	void *elemento = nodo_eliminado->elemento;

	if (posicion == 0) {
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		free(nodo_eliminado);
	} else {
		nodo_t *nodo_actual = lista->nodo_inicio;

		for (int i = 0; i < posicion - 1; i++)
			nodo_actual = nodo_actual->siguiente;

		nodo_eliminado = nodo_actual->siguiente;
		elemento = nodo_eliminado->elemento;
		nodo_actual->siguiente = nodo_eliminado->siguiente;
		free(nodo_eliminado);
	}

	(lista->cantidad)--;
	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL || posicion >= lista->cantidad)
		return NULL;

	nodo_t *actual = lista->nodo_inicio;

	for (int i = 0; i < posicion; i++)
		actual = actual->siguiente;

	return actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (lista == NULL || comparador == NULL)
		return NULL;

	nodo_t *actual = lista->nodo_inicio;

	for (int i = 0; i < lista->cantidad; i++) {
		if (comparador(actual->elemento, contexto) == 0)
			return actual->elemento;
		actual = actual->siguiente;
	}
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (lista_vacia(lista))
		return NULL;
	return (lista->nodo_inicio->elemento);
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista_vacia(lista))
		return (lista->nodo_fin->elemento);
	return NULL;
}

bool lista_vacia(lista_t *lista)
{
	return (lista == NULL || lista->cantidad == 0);
}

size_t lista_tamanio(lista_t *lista)
{
	if (lista_vacia(lista))
		return 0;
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista_vacia(lista)) {
		while (lista->nodo_inicio) {
			nodo_t *nodo_borrar = lista->nodo_inicio;
			lista->nodo_inicio = nodo_borrar->siguiente;

			if (funcion != NULL)
				funcion(nodo_borrar->elemento);

			(lista->cantidad)--;
			free(nodo_borrar);
		}
	}

	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (lista == NULL)
		return NULL;

	lista_iterador_t *iterador = calloc(1, sizeof(lista_iterador_t));
	if (iterador == NULL)
		return NULL;

	iterador->lista = lista;

	if (lista->cantidad != 0)
		iterador->nodo_actual = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (iterador == NULL || iterador->lista == NULL)
		return false;
	return (iterador->nodo_actual != NULL);
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (iterador == NULL || iterador->lista == NULL)
		return false;
	if (iterador->nodo_actual && iterador->nodo_actual->siguiente) {
		iterador->nodo_actual = iterador->nodo_actual->siguiente;
		return true;
	} else if (iterador->nodo_actual &&
		   iterador->nodo_actual->siguiente == NULL) {
		iterador->nodo_actual = iterador->nodo_actual->siguiente;
	}

	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (iterador == NULL || iterador->nodo_actual == NULL ||
	    iterador->lista == NULL)
		return NULL;

	return (iterador->nodo_actual->elemento);
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (funcion == NULL || lista == NULL)
		return ERROR;

	nodo_t *nodo_actual = lista->nodo_inicio;

	size_t i = 0;
	while (nodo_actual) {
		i++;
		if (!funcion(nodo_actual->elemento, contexto))
			return i;
		nodo_actual = nodo_actual->siguiente;
	}

	return i;
}
