#include "pa2m.h"
#include "src/pila.h"
#include "src/cola.h"
#include "src/lista.h"

void sumar_uno(void *numero)
{
	int *n = numero;
	(*n)++;
}

void crear_una_lista_devuelve_no_nulo()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Una lista creada es diferente a NULL");
	lista_destruir(lista);
}

void una_lista_recien_creada_tiene_tamaño_0()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "Una lista creada tiene tamaño 0");
	lista_destruir(lista);
}

void obtener_luego_de_insertar_devuelve_el_elemento_y_insertar_elemento_hace_crecer_la_lista()
{
	lista_t *lista = lista_crear();

	int p1 = 0;
	int p2 = 20;
	int p3 = 30;

	pa2m_afirmar(
		lista_insertar(lista, &p1) == lista &&
			lista_elemento_en_posicion(lista, 0) == &p1,
		"Obtener un elemento recien insertado me devuelve el mismo elemento");
	pa2m_afirmar(
		lista_tamanio(lista) == 1,
		"Al insertar un elemento en la lista, el tamaño se incrementa en uno");

	pa2m_afirmar(lista_insertar(lista, &p2) == lista &&
			     lista_elemento_en_posicion(lista, 1) == &p2,
		     "Puedo insertar un segundo elemento");
	pa2m_afirmar(
		lista_tamanio(lista) == 2,
		"Al insertar un elemento en la lista, el tamaño se incrementa en uno");

	pa2m_afirmar(lista_insertar(lista, &p3) == lista &&
			     lista_elemento_en_posicion(lista, 2) == &p3,
		     "Puedo insertar un tercer elemento");

	pa2m_afirmar(
		lista_tamanio(lista) == 3,
		"Al insertar un elemento en la lista, el tamaño se incrementa en uno");

	lista_destruir(lista);
}

void destruir_todos_los_elementos()
{
	int p1 = 0;
	int p2 = 0;
	int p3 = 30;

	lista_t *lista = lista_crear();
	lista_insertar(lista, &p1);
	lista_insertar(lista, &p2);
	lista_insertar(lista, &p3);

	lista_destruir_todo(lista, sumar_uno);

	pa2m_afirmar(p1 == 1, "Primer elemento se borro corectamente");
	pa2m_afirmar(p2 == 21, "Segundo elemento se borro corectamente");
	pa2m_afirmar(p3 == 31, "Tercer elemento se borro corectamente");
}

void puedo_quitar_de_la_lista()
{
	int p1 = 0;
	int p2 = 20;
	int p3 = 30;
	int p4 = 3;
	int p5 = 200;
	int p6 = 300;

	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_quitar(lista) == NULL &&
			     (lista_elemento_en_posicion(lista, 0) == NULL) &&
			     (lista_tamanio(lista) == 0),
		     "No puedo borrar algo de una lista nula.");

	pa2m_afirmar((lista_quitar(lista) == NULL) &&
			     (lista_elemento_en_posicion(lista, 0) == NULL) &&
			     (lista_tamanio(lista) == 0),
		     "No puedo borrar algo de una lista vacía.");

	lista_insertar(lista, &p1);
	lista_insertar(lista, &p2);
	lista_insertar(lista, &p3);
	lista_insertar(lista, &p4);
	lista_insertar(lista, &p5);
	lista_insertar(lista, &p6);

	pa2m_afirmar((lista_quitar_de_posicion(lista, 0) == &p1) &&
			     (lista_elemento_en_posicion(lista, 0) == &p2),
		     "Puedo borrar un elemento de la posición 0.");
	pa2m_afirmar(lista_tamanio(lista) == 5, "Tengo 5 elementos.");

	pa2m_afirmar((lista_quitar_de_posicion(lista, 0) == &p2) &&
			     (lista_elemento_en_posicion(lista, 0) == &p3),
		     "Puedo borrar otro elemento de la posición 0.");
	pa2m_afirmar(lista_tamanio(lista) == 4, "Tengo 4 elementos.");

	pa2m_afirmar((lista_quitar_de_posicion(lista, 1) == &p4) &&
			     (lista_elemento_en_posicion(lista, 1) == &p5),
		     "Puedo borrar un elemento de la posición 1.");
	pa2m_afirmar(lista_tamanio(lista) == 3, "Tengo 3 elementos.");

	pa2m_afirmar((lista_quitar_de_posicion(lista, 1) == &p5) &&
			     (lista_elemento_en_posicion(lista, 1) == &p6),
		     "Puedo borrar otro elemento de la posición 1.");
	pa2m_afirmar(lista_tamanio(lista) == 2, "Tengo 2 elementos.");

	pa2m_afirmar(lista_quitar(lista) == &p6 &&
			     lista_elemento_en_posicion(lista, 0) == &p3,
		     "Puedo borrar el último elemento presente en la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 1, "Tengo 1 elemento.");

	pa2m_afirmar(lista_quitar(lista) == &p3 &&
			     lista_elemento_en_posicion(lista, 0) == NULL,
		     "Puedo borrar el último elemento presente en la lista.");
	pa2m_afirmar(lista_tamanio(lista) == 0, "Tengo 0 elementos.");

	pa2m_afirmar((lista_quitar_de_posicion(lista, 0) == NULL) &&
			     (lista_elemento_en_posicion(lista, 0) == NULL),
		     "No puedo borrar elementos de una lista que quedó vacía.");

	lista_destruir(lista);
}

void obtener_elemento_inexistencia_devuelve_null()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 0) == NULL,
		"Obtener el primer delenteto de un alista vacia me devuelve NULL");
	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 100) == NULL,
		"Obtener el delenteto 100 de un alista vacia me devuelve NULL");
	lista_destruir(lista);
}

void funcionamiento_iterador_externo_lista_nula()
{
	lista_t *lista = NULL;
	lista_iterador_t *iterador = NULL;

	pa2m_afirmar(lista_iterador_crear(lista) == NULL,
		     "No puedo crear un iterador con una lista nula.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == false,
		     "Un iterador nulo no tiene siguiente.");
	pa2m_afirmar(lista_iterador_avanzar(iterador) == false,
		     "Un iterador nulo no puede ser avanzado.");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == NULL,
		     "El elemento actual de un iterador nulo es nulo.");

	lista_iterador_destruir(iterador);
}

void funcionamiento_iterador_externo_lista_vacia()
{
	lista_t *lista = lista_crear();

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(iterador != NULL,
		     "Puedo crear un iterador con una lista no nula.");
	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == false,
		     "Un iterador de lista vacía no tiene siguiente.");
	pa2m_afirmar(lista_iterador_avanzar(iterador) == false,
		     "Un iterador de lista vacía no puede ser avanzado.");
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == NULL,
		"El elemento actual de un iterador de lista vacía es nulo.");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void funcionamiento_iterador_externo_con_elementos()
{
	int p1 = 0;
	int p2 = 20;
	int p3 = 30;

	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(!lista_iterador_avanzar(iterador),
		     "No avanza con una lista vacía");

	lista_iterador_destruir(iterador);

	lista_insertar(lista, &p1);
	lista_insertar(lista, &p2);
	lista_insertar(lista, &p3);

	iterador = lista_iterador_crear(lista);

	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == &p1,
		"Me duevuelve el primer elemento de una lista el iterador");
	pa2m_afirmar(
		lista_iterador_avanzar(iterador) &&
			lista_iterador_tiene_siguiente(iterador),
		"se puede avanzar con el iterador cuando hay elementos todavia");
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == &p2,
		"Me duevuelve el segundo elemento de una lista el iterador");
	pa2m_afirmar(
		lista_iterador_avanzar(iterador) &&
			lista_iterador_tiene_siguiente(iterador),
		"se puede avanzar con el iterador cuando hay elementos todavia");
	pa2m_afirmar(
		lista_iterador_elemento_actual(iterador) == &p3,
		"Me duevuelve el tercer elemento de una lista el iterador");
	pa2m_afirmar(!lista_iterador_avanzar(iterador) &&
			     !lista_iterador_tiene_siguiente(iterador),
		     "No puedo seguir avanzando");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

bool no_son_iguales(void *elemento, void *elemento1)
{
	return (elemento != elemento1);
}

void funcionamiento_iterador_funcion_comparadora()
{
	size_t p1 = 7;
	size_t p2 = 20;
	size_t p3 = 30;
	size_t p4 = 3;
	size_t p5 = 200;
	size_t p6 = 300;

	lista_t *lista = lista_crear();

	lista_insertar(lista, &p1);
	lista_insertar(lista, &p2);
	lista_insertar(lista, &p3);
	lista_insertar(lista, &p4);
	lista_insertar(lista, &p5);
	lista_insertar(lista, &p6);

	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, &p6) == 0,
		     "Devuelve 0 si funcion es NULL");

	printf("%li", lista_con_cada_elemento(lista, no_son_iguales, &p1));

	pa2m_afirmar(lista_con_cada_elemento(lista, no_son_iguales, &p1) == 1,
		     "Itera 1 elementos");

	printf("%li", lista_con_cada_elemento(lista, no_son_iguales, &p4));

	pa2m_afirmar(lista_con_cada_elemento(lista, no_son_iguales, &p4) == 4,
		     "Itera 5 elementos");

	printf("%li", lista_con_cada_elemento(lista, no_son_iguales, &p6));

	pa2m_afirmar(lista_con_cada_elemento(lista, no_son_iguales, &p6) == 6,
		     "Itera 6 elementos");

	lista_destruir(lista);
}

void se_puede_apilar_desapilar()
{
	pila_t *pila = NULL;

	pa2m_afirmar((pila_desapilar(pila) == NULL) &&
			     (pila_tope(pila) == NULL),
		     "No puedo desapilar de una pila nula");

	pila = pila_crear();

	pa2m_afirmar((pila_desapilar(pila) == NULL) &&
			     (pila_tope(pila) == NULL),
		     "No puedo desapilar de una pila vacía");

	int p1 = 0x123;
	int p2 = 20;
	int p3 = 0x123;

	pa2m_afirmar((pila_apilar(pila, &p1) == pila) &&
			     (pila_tope(pila) == &p1),
		     "Puedo apilar un elemento sobre una pila vacía");

	pa2m_afirmar((pila_apilar(pila, &p2) == pila) &&
			     (pila_tope(pila) == &p2),
		     "Puedo apilar otro elemento en la pila");

	pa2m_afirmar((pila_apilar(pila, &p3) == pila) &&
			     (pila_tope(pila) == &p3),
		     "Puedo apilar un un tercer elemento en la pila");

	pa2m_afirmar(pila_desapilar(pila) == &p3 && pila_tope(pila) == &p2,
		     "Puedo desapilar un elemento");
	pa2m_afirmar(pila_desapilar(pila) == &p2 && pila_tope(pila) == &p1,
		     "Puedo desapilar otro elemento");
	pa2m_afirmar(pila_desapilar(pila) == &p1 && pila_tope(pila) == NULL,
		     "Puedo desapilar el último elemento de la pila");
	pa2m_afirmar(pila_desapilar(pila) == NULL && pila_vacia(pila) == true &&
			     pila_tope(pila) == NULL,
		     "No puedo desapilar de una pila que quedó vacía");

	pila_destruir(pila);
}

void se_puede_encolar_desencolar()
{
	cola_t *cola = NULL;
	int p1 = 0;
	int p2 = 20;
	int p3 = 30;

	pa2m_afirmar(cola_encolar(cola, &p1) == NULL &&
			     (cola_frente(cola) == NULL),
		     "No puedo encolar en una cola nula");

	cola = cola_crear();

	pa2m_afirmar((cola_desencolar(cola) == NULL) &&
			     (cola_frente(cola) == NULL),
		     "No puedo desencolar de una cola vacia");

	pa2m_afirmar(cola_encolar(cola, &p1) == cola &&
			     (cola_frente(cola) == &p1),
		     "Puedo encolar un elemento en una cola vacía");
	cola_encolar(cola, &p2);
	pa2m_afirmar(cola_encolar(cola, &p2) == cola &&
			     (cola_frente(cola) == &p1),
		     "Encolo otro elemento y el primero sigue siendo correcto");
	cola_encolar(cola, &p3);
	pa2m_afirmar(
		cola_encolar(cola, &p3) == cola && (cola_frente(cola) == &p1),
		"Encolo otro elemento más y el primero sigue siendo correcto");

	pa2m_afirmar(
		cola_desencolar(cola) == &p1 && cola_frente(cola) == &p2,
		"Desencolo un elemento y el nuevo primer elemento es el correcto");
	cola_desencolar(cola);
	pa2m_afirmar(
		cola_desencolar(cola) == &p2 && (cola_frente(cola) == &p3),
		"Desencolo otro elemento y el nuevo primer elemento es el correcto");
	cola_desencolar(cola);
	pa2m_afirmar(cola_desencolar(cola) == &p3 &&
			     (cola_frente(cola) == NULL),
		     "Desencolo el ultimo elemento");
	pa2m_afirmar(cola_desencolar(cola) == NULL &&
			     (cola_frente(cola) == NULL),
		     "No puedo desencolar de una cola que quedó vacía");

	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("\nPruebas de creacion de lista");
	crear_una_lista_devuelve_no_nulo();
	una_lista_recien_creada_tiene_tamaño_0();

	pa2m_nuevo_grupo("\nPruebas de insercion");
	obtener_luego_de_insertar_devuelve_el_elemento_y_insertar_elemento_hace_crecer_la_lista();

	pa2m_nuevo_grupo("\nPruebas de borrado");
	destruir_todos_los_elementos();
	puedo_quitar_de_la_lista();

	pa2m_nuevo_grupo("\nPruebas de iterador externo");
	funcionamiento_iterador_externo_lista_nula();
	funcionamiento_iterador_externo_lista_vacia();
	funcionamiento_iterador_externo_con_elementos();

	pa2m_nuevo_grupo("\nPruebas de iterador interno");
	funcionamiento_iterador_funcion_comparadora();

	pa2m_nuevo_grupo("\nPruebas de pila");
	se_puede_apilar_desapilar();

	pa2m_nuevo_grupo("\nPruebas de cola");
	se_puede_encolar_desencolar();

	pa2m_nuevo_grupo("\nPruebas de NULL");
	obtener_elemento_inexistencia_devuelve_null();

	return pa2m_mostrar_reporte();
}
