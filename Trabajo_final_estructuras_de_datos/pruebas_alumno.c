#include "pa2m.h"
#include <stdlib.h>
#include "string.h"
#include <stdbool.h>

#define CAPACIDAD 10

struct menu_hospitales {
	menu_t *menu;
	hash_t *hospitales;
	char *id_hospital_activo;
	size_t cantidad;
};

void prueba_simple()
{
	int i = 14;
	int j = 16;
	pa2m_afirmar(i != j, "i=14 es diferente de j=16");
}
void test_archivos()
{
	menu_hospitales_t *menu = menu_hospitales_crear();

	pa2m_afirmar((menu->cantidad == 0), "Puedo crear un menu vacio");

	/*cargar_hospital(menu, "nombre_raro.txt");

	pa2m_afirmar((menu->cantidad==0),"Si inserto un hospital que no tenga un archivo valido no se agrega");

	cargar_hospital(menu, "ejemplos/hospital1.txt");

	pa2m_afirmar((menu->cantidad==1),"Si inserto un hospital que tenga un archivo valido se agrega al menu");*/

	menu_hospitales_destruir(menu);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n========================  PRUEBAS COMANDOS ========================");

	pa2m_nuevo_grupo("test_archivos");
	test_archivos();

	return pa2m_mostrar_reporte();
}
