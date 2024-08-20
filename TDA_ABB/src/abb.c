#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

struct array_con_tamanio {
	void **array;
	size_t tamanio;
	size_t cantidad;
};

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;

	abb_t *arbol = malloc(sizeof(abb_t) * 1);
	if (!arbol)
		return NULL;
	arbol->tamanio = 0;
	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	return arbol;
}

nodo_abb_t *crear_nodo(void *elemento)
{
	nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t) * 1);

	if (!nodo)
		return NULL;

	nodo->elemento = elemento;
	nodo->izquierda = NULL;
	nodo->derecha = NULL;

	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol || !arbol->comparador) {
		return NULL;
	}

	nodo_abb_t *nodo_nuevo = crear_nodo(elemento);
	if (!nodo_nuevo)
		return NULL;

	if (arbol->nodo_raiz == NULL) {
		arbol->nodo_raiz = nodo_nuevo;
		(arbol->tamanio)++;
		return arbol;
	}

	struct nodo_abb *actual = arbol->nodo_raiz;
	while (actual != NULL) {
		if (arbol->comparador(elemento, actual->elemento) <= 0) {
			if (actual->izquierda == NULL) {
				actual->izquierda = nodo_nuevo;
				actual = NULL;
			} else
				actual = actual->izquierda;
		} else {
			if (actual->derecha == NULL) {
				actual->derecha = nodo_nuevo;
				actual = NULL;
			} else
				actual = actual->derecha;
		}
	}

	(arbol->tamanio)++;
	return arbol;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (abb_vacio(arbol) || !arbol->comparador) {
		return NULL;
	}

	struct nodo_abb *actual = arbol->nodo_raiz;

	while (actual != NULL) {
		int comparacion = arbol->comparador(elemento, actual->elemento);
		if (comparacion < 0)
			actual = actual->izquierda;
		else if (comparacion > 0)

			actual = actual->derecha;
		else
			return actual->elemento;
	}
	return NULL;
}

nodo_abb_t *extraer_nodo_mas_derecha(nodo_abb_t *raiz, void **extraido)
{
	if (raiz->derecha == NULL) {
		*extraido = raiz->elemento;
		nodo_abb_t *izq = raiz->izquierda;
		free(raiz);
		return izq;
	}

	raiz->derecha = extraer_nodo_mas_derecha(raiz->derecha, extraido);

	return raiz;
}

void *abb_quitar_recursivo(nodo_abb_t *raiz, void *elemento,
			   abb_comparador comparador, void **extraido,
			   bool encontrado)
{
	if (!raiz)
		return NULL;

	int comparacion = comparador(elemento, raiz->elemento);

	if (comparacion == 0) {
		nodo_abb_t *izq = raiz->izquierda;
		nodo_abb_t *der = raiz->derecha;
		*extraido = raiz->elemento;
		encontrado = true;

		if (izq != NULL && der != NULL) {
			void *elemento_derecho = NULL;
			raiz->izquierda = extraer_nodo_mas_derecha(
				raiz->izquierda, &elemento_derecho);
			raiz->elemento = elemento_derecho;
			return raiz;
		} else {
			free(raiz);
			if (izq == NULL)
				return der;
			return izq;
		}

	} else if (comparacion < 0)
		raiz->izquierda = abb_quitar_recursivo(raiz->izquierda,
						       elemento, comparador,
						       extraido, encontrado);
	else
		raiz->derecha = abb_quitar_recursivo(raiz->derecha, elemento,
						     comparador, extraido,
						     encontrado);

	return raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (abb_vacio(arbol) || !arbol->comparador)
		return NULL;

	void *extraido = NULL;
	abb_comparador comparador = arbol->comparador;

	bool encontrado = false;
	arbol->nodo_raiz = abb_quitar_recursivo(
		arbol->nodo_raiz, elemento, comparador, &extraido, encontrado);

	//if(encontrado)//
	(arbol->tamanio)--;
	return extraido;
}

bool abb_vacio(abb_t *arbol)
{
	return (!arbol || arbol->tamanio == 0);
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol)
		return 0;
	return arbol->tamanio;
}

void destruir_un_nodo(nodo_abb_t *nodo, void (*destructor)(void *))
{
	if (destructor)
		destructor(nodo->elemento);
	free(nodo);
}

void destruir_nodos(nodo_abb_t *nodo, void (*destructor)(void *))
{
	if (nodo != NULL) {
		destruir_nodos(nodo->izquierda, destructor);
		destruir_nodos(nodo->derecha, destructor);
		destruir_un_nodo(nodo, destructor);
	}
}

void abb_destruir(abb_t *arbol)
{
	abb_destruir_todo(arbol, NULL);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol) {
		destruir_nodos(arbol->nodo_raiz, destructor);
		free(arbol);
	}
}

bool recorrido_inorden(nodo_abb_t *raiz, bool (*funcion)(void *, void *),
		       void *aux, size_t *contador)
{
	if (!raiz)
		return true;

	bool continuar =
		recorrido_inorden(raiz->izquierda, funcion, aux, contador);

	if (!continuar)
		return false;

	(*contador)++;

	if (funcion(raiz->elemento, aux) == false) {
		return false;
	}

	return recorrido_inorden(raiz->derecha, funcion, aux, contador);
}

bool recorrido_preorden(nodo_abb_t *raiz, bool (*funcion)(void *, void *),
			void *aux, size_t *contador)
{
	if (!raiz)
		return true;

	(*contador)++;
	if (funcion(raiz->elemento, aux) == false) {
		return false;
	}

	bool continuar =
		recorrido_preorden(raiz->izquierda, funcion, aux, contador);
	if (!continuar)
		return false;

	return recorrido_preorden(raiz->derecha, funcion, aux, contador);
}

bool recorrido_postorden(nodo_abb_t *raiz, bool (*funcion)(void *, void *),
			 void *aux, size_t *contador)
{
	if (!raiz)
		return true;

	bool continuar =
		recorrido_postorden(raiz->izquierda, funcion, aux, contador);
	if (!continuar)
		return false;

	continuar = recorrido_postorden(raiz->derecha, funcion, aux, contador);

	if (!continuar)
		return false;

	(*contador)++;

	if (funcion(raiz->elemento, aux) == false) {
		return false;
	}

	return continuar;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (!arbol || !funcion)
		return 0;

	size_t contador = 0;

	if (recorrido == INORDEN) {
		recorrido_inorden(arbol->nodo_raiz, funcion, aux, &contador);

	} else if (recorrido == PREORDEN) {
		recorrido_preorden(arbol->nodo_raiz, funcion, aux, &contador);

	} else if (recorrido == POSTORDEN) {
		recorrido_postorden(arbol->nodo_raiz, funcion, aux, &contador);
	} else
		return 0;

	return contador;
}

bool rellenar_array(void *elemento, void *aux)
{
	struct array_con_tamanio *vct = aux;

	if (vct->cantidad >= vct->tamanio)
		return false;

	vct->array[vct->cantidad] = elemento;
	vct->cantidad++;
	return true;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol || !array)
		return 0;

	struct array_con_tamanio auxiliar;
	auxiliar.array = array;
	auxiliar.tamanio = tamanio_array;
	auxiliar.cantidad = 0;

	abb_con_cada_elemento(arbol, recorrido, rellenar_array, &auxiliar);
	return auxiliar.cantidad;
}
