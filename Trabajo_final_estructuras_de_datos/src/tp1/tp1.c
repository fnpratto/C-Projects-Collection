#include "tp1.h"

#include "pokemon.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEER "r"
#define LECTURA "%s"
#define CANT_DATOS_XLINEA 1
#define MAX_LETRAS 100

struct _hospital_pkm_t {
	pokemon_t **pokemones;
	size_t cantidad_pokemon;
	size_t cantidad_entrenadores;
};

hospital_t *hospital_inicializar()
{
	hospital_t *hospital = malloc(sizeof(hospital_t) * 1);

	if (hospital == NULL) {
		return NULL;
	}

	hospital->cantidad_pokemon = 0;
	hospital->cantidad_entrenadores = 0;
	hospital->pokemones = NULL;

	return hospital;
}

bool pokemon_agregado(hospital_t *hospital, pokemon_t *pokemon)
{
	if (pokemon != NULL) {
		pokemon_t **agrando_pointer =
			realloc(hospital->pokemones,
				(sizeof(pokemon_t *) *
				 (hospital->cantidad_pokemon + 1)));

		if (agrando_pointer == NULL) {
			return false;
		}

		hospital->pokemones = agrando_pointer;

		hospital->pokemones[hospital->cantidad_pokemon] = pokemon;
		hospital->cantidad_pokemon += 1;
		hospital->cantidad_entrenadores += 1;

		return true;

	} else {
		return false;
	}
}

void ordenar_pokemones_prioridad(hospital_t *hospital)
{
	pokemon_t *poke_aux;
	for (size_t i = 0; i < hospital->cantidad_pokemon; i++) {
		for (size_t i = 0; i < hospital->cantidad_pokemon - 1; i++) {
			size_t j = i + 1;
			if (pokemon_salud(hospital->pokemones[i]) >
			    pokemon_salud(hospital->pokemones[j])) {
				poke_aux = hospital->pokemones[j];
				hospital->pokemones[j] = hospital->pokemones[i];
				hospital->pokemones[i] = poke_aux;
			}
		}
	}
}

hospital_t *hospital_crear_desde_archivo(const char *nombre_archivo)
{
	if (nombre_archivo == NULL)
		return NULL;

	FILE *lista_pokes = fopen(nombre_archivo, LEER);
	if (!lista_pokes) {
		return NULL;
	}

	hospital_t *hospital = hospital_inicializar();

	char string[MAX_LETRAS];
	int leidos = fscanf(lista_pokes, LECTURA, string);

	while (leidos == CANT_DATOS_XLINEA) {
		pokemon_t *nuevo_poke = pokemon_crear_desde_string(string);

		if (!pokemon_agregado(hospital, nuevo_poke)) {
			fclose(lista_pokes);
			hospital_destruir(hospital);
			return NULL;
		}
		leidos = fscanf(lista_pokes, LECTURA, string);
	}

	fclose(lista_pokes);

	if (hospital_cantidad_pokemones(hospital) < 1) {
		hospital_destruir(hospital);
		return NULL;
	}

	ordenar_pokemones_prioridad(hospital);
	return hospital;
}

size_t hospital_cantidad_pokemones(hospital_t *hospital)
{
	if (hospital == NULL)
		return 0;
	return hospital->cantidad_pokemon;
}

size_t hospital_a_cada_pokemon(hospital_t *hospital,
			       bool (*funcion)(pokemon_t *p, void *aux),
			       void *aux)
{
	if (hospital == NULL || funcion == NULL)
		return 0;

	size_t contador = 0;
	for (size_t i = 0; i < hospital->cantidad_pokemon; i++) {
		contador++;
		if (!funcion(hospital->pokemones[i], aux))
			return contador;
	}
	return contador;
}

int hospital_aceptar_emergencias(hospital_t *hospital,
				 pokemon_t **pokemones_ambulancia,
				 size_t cant_pokes_ambulancia)
{
	if (hospital == NULL || pokemones_ambulancia == NULL)
		return ERROR;

	int cant_pokes_transferidos = 0;

	for (int i = 0; i < cant_pokes_ambulancia; i++) {
		if (pokemones_ambulancia[i] != NULL) {
			if (pokemon_agregado(hospital,
					     pokemones_ambulancia[i])) {
				cant_pokes_transferidos++;
			} else {
				hospital_destruir(hospital);
			}
		}
	}

	if (cant_pokes_transferidos != cant_pokes_ambulancia)
		return ERROR;

	ordenar_pokemones_prioridad(hospital);
	return EXITO;
}

pokemon_t *hospital_obtener_pokemon(hospital_t *hospital, size_t prioridad)
{
	if (hospital == NULL && prioridad > hospital->cantidad_pokemon)
		return NULL;
	return hospital->pokemones[prioridad];
}

void hospital_destruir(hospital_t *hospital)
{
	for (int i = 0; i < hospital->cantidad_pokemon; i++) {
		pokemon_destruir(hospital->pokemones[i]);
	}
	free(hospital->pokemones);
	free(hospital);
}