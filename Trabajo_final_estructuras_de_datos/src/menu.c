#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "hash/hash.h"

#define CAPACIDAD_MINIMA 10
#define MAX_NOMBRE 70

struct menu {
	hash_t *comandos;
	hash_t *sinonimos_comandos;
};

struct comando {
	const char *nombre;
	const char *descripcion;
	bool (*funcion)(void *);
};

struct comando *comando_crear(const char *nombre, const char *descripcion,
			      bool (*funcion)(void *))
{
	struct comando *comando = malloc(sizeof(struct comando));
	if (!comando)
		return NULL;
	comando->nombre = duplicar_clave(nombre);
	comando->descripcion = duplicar_clave(descripcion);
	comando->funcion = funcion;
	return comando;
}

menu_t *menu_agregar_sinonimo(menu_t *menu, const char *texto,
			      const char *descripcion, bool (*funcion)(void *))
{
	struct comando *sinonimo = comando_crear(texto, descripcion, funcion);
	if (!sinonimo)
		return NULL;
	void *aux =
		hash_insertar(menu->sinonimos_comandos, texto, sinonimo, NULL);
	if (!aux) {
		free(sinonimo);
		return NULL;
	}
	return menu;
}

menu_t *menu_agregar_opcion(menu_t *menu, const char *texto,
			    const char *descripcion, bool (*funcion)(void *))
{
	struct comando *comando = comando_crear(texto, descripcion, funcion);
	if (!comando)
		return NULL;
	void *aux = hash_insertar(menu->comandos, texto, comando, NULL);
	;
	if (!aux) {
		free(comando);
		return NULL;
	}
	return menu;
}

menu_t *menu_crear()
{
	menu_t *menu = calloc(1, sizeof(menu_t));
	if (!menu)
		return NULL;
	menu->comandos = hash_crear(CAPACIDAD_MINIMA);
	if (!menu->comandos) {
		free(menu);
		return NULL;
	}
	menu->sinonimos_comandos = hash_crear(CAPACIDAD_MINIMA);
	if (!menu->sinonimos_comandos) {
		free(menu->sinonimos_comandos);
		free(menu);
		return NULL;
	}
	return menu;
}

enum resultado_menu menu_ejecutar_opcion(menu_t *menu, const char *texto,
					 void *aux)
{
	struct comando *comando = hash_obtener(menu->comandos, texto);
	if (!comando)
		comando = hash_obtener(menu->sinonimos_comandos, texto);
	if (!comando)
		return INEXISTENTE;
	if (comando->funcion(aux))
		return OK;
	return ERROR;
}

bool mostrar_opcion(const char *nombre, void *_comando, void *ignorame)
{
	struct comando *comando = _comando;

	printf("   - %s: %s\n", comando->nombre, comando->descripcion);

	return true;
}

void menu_mostrar(menu_t *menu)
{
	hash_con_cada_clave(menu->comandos, mostrar_opcion, NULL);
}

void destruir_sinonimos(void *_sinonimo)
{
	struct comando *sinonimo = _sinonimo;
	free((char *)sinonimo->nombre);
	free((char *)sinonimo->descripcion);
	free(sinonimo);
}

void destruir_comandos(void *_comando)
{
	struct comando *comando = _comando;
	free((char *)comando->nombre);
	free((char *)comando->descripcion);
	free(comando);
}

void menu_destruir(menu_t *menu)
{
	hash_destruir_todo(menu->sinonimos_comandos, destruir_sinonimos);
	hash_destruir_todo(menu->comandos, destruir_comandos);
	free(menu);
}
