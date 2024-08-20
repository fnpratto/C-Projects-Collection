#include "pokemon.h"
#include "pokemon_privado.h"
#include <stdio.h>
#include <string.h>

#define LECTURA "%zx,%[^,],%zu,%s"
#define CANT_DATOS_XLINEA 4
#define LEER "r"

pokemon_t *pokemon_crear_desde_string(const char *string)
{
	if (string == NULL) {
		return NULL;
	}

	pokemon_t *pokemones = malloc(sizeof(pokemon_t) * 1);

	if (pokemones == NULL) {
		return NULL;
	}

	int leidos = sscanf(string, LECTURA, &pokemones->id, pokemones->nombre,
			    &pokemones->salud, pokemones->nombre_entrenador);

	if (leidos != CANT_DATOS_XLINEA) {
		pokemon_destruir(pokemones);
		return NULL;
	}

	return pokemones;
}

pokemon_t *pokemon_copiar(pokemon_t *poke)
{
	if (poke == NULL)
		return NULL;

	pokemon_t *copia_poke = malloc(sizeof(pokemon_t) * 1);
	if (copia_poke == NULL) {
		return NULL;
	}

	copia_poke->id = poke->id;
	strcpy(copia_poke->nombre, poke->nombre);
	copia_poke->salud = poke->salud;
	strcpy(copia_poke->nombre_entrenador, poke->nombre_entrenador);

	return copia_poke;
}

bool pokemon_son_iguales(pokemon_t *pokemon1, pokemon_t *pokemon2)
{
	if (pokemon1 == NULL || pokemon2 == NULL)
		return false;

	if ((strcmp(pokemon_nombre(pokemon1), pokemon_nombre(pokemon2)) == 0) &&
	    (pokemon_id(pokemon1) == pokemon_id(pokemon2)) &&
	    (pokemon_salud(pokemon1) == pokemon_salud(pokemon2)))
		return true;
	return false;
}

char *pokemon_nombre(pokemon_t *pokemon)
{
	if (pokemon == NULL)
		return 0;
	return pokemon->nombre;
}

char *pokemon_entrenador(pokemon_t *pokemon)
{
	if (pokemon == NULL)
		return 0;
	return pokemon->nombre_entrenador;
}

size_t pokemon_salud(pokemon_t *pokemon)
{
	if (pokemon == NULL)
		return 0;
	return pokemon->salud;
}

size_t pokemon_id(pokemon_t *pokemon)
{
	if (pokemon == NULL)
		return 0;
	return pokemon->id;
}

void pokemon_destruir(pokemon_t *pkm)
{
	free(pkm);
}