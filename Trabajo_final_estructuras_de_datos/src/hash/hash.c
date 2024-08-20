#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "hash.h"
#define FACTOR_CARGA_MAXIMO 0.7
#define CAPACIDAD_MINIMA 3

struct hash {
	struct nodo **vector;
	size_t capacidad;
	size_t cantidad;
};

typedef struct nodo {
	char *clave;
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash)
		return NULL;
	if (capacidad < CAPACIDAD_MINIMA)
		capacidad = CAPACIDAD_MINIMA;
	hash->vector = calloc(1, sizeof(nodo_t *) * capacidad);
	if (!hash->vector) {
		hash_destruir(hash);
		return NULL;
	}
	hash->capacidad = capacidad;
	return hash;
}
unsigned long funcion_hash(const char *str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = (unsigned long)c + (hash << 6) + (hash << 16) - hash;
	return hash;
}
char *duplicar_clave(const char *clave)
{
	if (!clave)
		return NULL;
	char *copia = malloc(strlen(clave) + 1);
	if (!copia)
		return NULL;
	strcpy(copia, clave);
	return copia;
}
bool igual_clave(const char *clave_actual, const char *clave)
{
	return strcmp(clave_actual, clave) == 0;
}

nodo_t *nodo_crear(const char *clave, void *valor)
{
	if (!clave)
		return NULL;

	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo)
		return NULL;
	nodo->clave = duplicar_clave(clave);
	nodo->elemento = valor;
	nodo->siguiente = NULL;
	return nodo;
}
bool necesita_rehash(hash_t *hash)
{
	float carga = (float)(hash->cantidad) / (float)(hash->capacidad);
	return (carga > FACTOR_CARGA_MAXIMO);
}
size_t posicion_hash(hash_t *hash, const char *clave)
{
	return (funcion_hash(clave) % hash->capacidad);
}
bool hash_rehash(hash_t *hash)
{
	hash_t *nuevo_hash = hash_crear((hash->capacidad) * 2);
	if (!nuevo_hash)
		return false;
	for (int n = 0; n < hash->capacidad; n++) {
		if (hash->vector[n]) {
			nodo_t *actual = hash->vector[n];
			while (actual) {
				if (!hash_insertar(nuevo_hash, actual->clave,
						   actual->elemento, NULL))
					return false;
				actual = actual->siguiente;
			}
		}
	}
	hash_t aux = *hash;
	*hash = *nuevo_hash;
	*nuevo_hash = aux;
	hash_destruir(nuevo_hash);
	return true;
}
hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;
	if (necesita_rehash(hash)) {
		if (!hash_rehash(hash))
			return NULL;
	}
	size_t posicion = posicion_hash(hash, clave);

	if (hash->vector[posicion] == NULL) {
		hash->vector[posicion] = nodo_crear(clave, elemento);
		if (!hash->vector[posicion])
			return NULL;
		if (anterior)
			*anterior = NULL;
		hash->cantidad++;
	} else {
		nodo_t *actual = hash->vector[posicion];

		while (actual) {
			if (igual_clave(actual->clave, clave)) {
				if (anterior)
					*anterior = actual->elemento;

				actual->elemento = elemento;
				return hash;
			}

			actual = actual->siguiente;
		}

		nodo_t *nodo = nodo_crear(clave, elemento);
		if (!nodo)
			return NULL;

		nodo->siguiente = hash->vector[posicion];
		hash->vector[posicion] = nodo;
		hash->cantidad++;
	}

	return hash;
}
void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;
	size_t posicion = posicion_hash(hash, clave);
	if (!hash->vector[posicion])
		return NULL;
	nodo_t *actual = hash->vector[posicion];
	nodo_t *anterior = NULL;
	while (actual) {
		if (igual_clave(actual->clave, clave)) {
			void *aux = actual->elemento;
			if (anterior) {
				anterior->siguiente = actual->siguiente;
			} else {
				hash->vector[posicion] = actual->siguiente;
			}
			free(actual->clave);
			free(actual);
			hash->cantidad--;
			return aux;
		}
		anterior = actual;
		actual = actual->siguiente;
	}
	return NULL;
}
void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;
	size_t posicion = posicion_hash(hash, clave);
	if (!hash->vector[posicion])
		return NULL;
	nodo_t *actual = hash->vector[posicion];
	while (actual) {
		if (igual_clave(actual->clave, clave)) {
			return actual->elemento;
		}
		actual = actual->siguiente;
	}
	return NULL;
}
bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;
	size_t posicion = posicion_hash(hash, clave);
	if (hash->vector[posicion] == NULL)
		return false;
	nodo_t *actual = hash->vector[posicion];
	while (actual) {
		if (igual_clave(actual->clave, clave))
			return true;
		actual = actual->siguiente;
	}
	return false;
}
size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;
	return hash->cantidad;
}
void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}
void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	nodo_t *actual;
	nodo_t *nodo_anterior = NULL;
	for (int i = 0; i < hash->capacidad; i++) {
		actual = hash->vector[i];
		while (actual) {
			if (destructor)
				destructor(actual->elemento);
			nodo_anterior = actual;
			actual = actual->siguiente;
			free(nodo_anterior->clave);
			free(nodo_anterior);
		}
		free(actual);
	}
	free(hash->vector);
	free(hash);
}
size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *elemento,
				     void *aux),
			   void *aux)
{
	size_t n = 0;
	if (!hash || !f)
		return n;
	for (int i = 0; i < hash->capacidad; i++) {
		nodo_t *actual = hash->vector[i];
		while (actual) {
			n++;
			if (!f(actual->clave, actual->elemento, aux))
				return n;
			actual = actual->siguiente;
		}
	}
	return n;
}