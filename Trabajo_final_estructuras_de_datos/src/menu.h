#ifndef __MENU_H__
#define __MENU_H__

#include <stdbool.h>
#include <stddef.h>

enum resultado_menu { INEXISTENTE, OK, ERROR };

typedef struct menu menu_t;

menu_t *menu_crear();

menu_t *menu_agregar_sinonimo(menu_t *menu, const char *texto,
			      const char *descripcion, bool (*funcion)(void *));

void menu_destruir(menu_t *menu);

menu_t *menu_agregar_opcion(menu_t *menu, const char *texto,
			    const char *descripcion, bool (*funcion)(void *));

enum resultado_menu menu_ejecutar_opcion(menu_t *menu, const char *texto,
					 void *aux);
void menu_mostrar(menu_t *menu);

#endif /*__MENU_H__ */
