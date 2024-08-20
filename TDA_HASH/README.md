<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de (Florencia Pratto) - (110416) - (fnpratto@fi.uba.ar)

- Para compilar:

```bash
gcc src/*.c pruebas_chanutron.c -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -g prueba_chanutron
```

- Para ejecutar:

```bash
./pruebas_chanutron
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./p
```

---

## Respuestas a las preguntas teóricas
### Conceptos , Graficos 

Una tabla hash se compone de entradas con claves únicas, lo que permite identificar de manera única a cada entrada en la tabla. Cada entrada está formada por una clave y la información asociada.

En ocasiones , se producen colisiones en las tablas hash, que ocurren cuando dos elementos diferentes obtienen la misma clave. Para solucionar se usa un Encadenamiento separado en un hash abierto: Las colisiones se resuelven insertando los elementos en una lista. En esta estructura, se utiliza un vector de listas, donde el factor de carga (número promedio de claves por lista) se mantiene cercano a 1.
La gestión de colisiones mediante listas encadenadas es una solución común para implementar tablas hash. Cada posición de la tabla almacena la cabeza de una lista encadenada que contiene los elementos con la misma clave. Si una posición de la tabla no tiene elementos, contiene un puntero a NULL.

En general, las tablas hash ofrecen un tiempo de búsqueda promedio constante O(1), independientemente del número de elementos en la tabla. Sin embargo, en casos extremos, el tiempo de búsqueda puede aumentar a O(n) en función del número de elementos.

## Diferencias con un hash cerrado;

En este tda se usa un hash abierto pero en un hash Cerrado como todos los valores se guardan dentro de la misma tabla el tamaño de tabla >= nro. de clave. Si hay colisión,  sigo recorriendo el array hasta encontrar el próximo espacio libre (ver siguiente slide) Por esto se conoce como “direccionamiento abierto”.
Primero el borrado es simple y segundo el crecimiento de la tabla puede ser pospuesto durante mucho más tiempo dado que el rendimiento disminuye mucho más lentamente incluso cuando todas las casillas ya están ocupadas. De hecho, muchas tablas hash encadenadas pueden no requerir crecimiento nunca, dado que la degradación de rendimiento es lineal en la medida que se va llenando la tabla. Por ejemplo, una tabla hash encadenada con dos veces el número de elementos recomendados, será dos veces más lenta en promedio que la misma tabla a su capacidad recomendada.

# Funcionamiento

**Detalles de implementación**

*Aclaraciones generales*

- No hay duplicación de entradas
- Se usa un hash abierto 
- si dos cosas son iguales deberia retornear el mismo valor siempre devuelve el mismo valor por un objeto durante una corritda de codigo es podesible devolver diferentes valores para un objeto en diferentes corrigasd de codigo
- Tratamos de minimizar colisiones
- Para usar una tabla hash se necesita:Una estructura de acceso directo (normalmente un array).Una estructura de datos con una clave.Una función hash (hash) Una función “hash” que recibe la clave y devuelve un índice para acceder a una posición de la tabla
- Gestión de colisiones mediante listas encadenadas
- En la implementacion vamos a usar FACTOR de CARGA MAXIMO. Estos umbrales determinan el nivel de ocupación de la tabla. Si el factor supera el valor máximo(0.7), se reserva espacio para una tabla más grande y se reinsertan los elementos. Esto permite optimizar las operaciones de búsqueda.
- Factor de carga : α = número de claves almacenadas actualmente / capacidad de la tabla de hash 
- En un hash Abierto Para encontrar una clave con su correspondiente valor en caso de colisión: O(n) donde n es la cantidad de elementos que colisionaron. Es decir, voy a tener que recorrer la lista enlazada. Sino es O(1)

---

## Estructuras desarrolladas

#### Hash;

```c
typedef struct hash {
	struct nodo **vector;
	size_t capacidad;
	size_t cantidad;
} hash;

```

#### Nodo;

```c
typedef struct nodo {
	char *clave;
	void *elemento;
	struct nodo *siguiente;
} nodo_t;
```

## Aclaraciones del funcionamiento

## Funciones del hash.h

### hash_crear
Crea el hash reservando la memoria necesaria para el. Capacidad indica la capacidad inicial con la que se crea el hash. La capacidad inicial no puede ser menor a 3. Si se solicita una capacidad menor, el hash se creará con una capacidad de 3. Devuelve un puntero al hash creado o NULL en caso de no poder crearlo.

### hash_insertar

La función permite insertar o actualizar un elemento en una tabla hash asociada a una clave específica. Si la clave ya existe en la tabla, se reemplaza el elemento y se guarda un puntero al elemento reemplazado en *anterior (si anterior no es NULL). Si la clave no existe y anterior no es NULL, se almacena NULL en *anterior. La función almacena una copia de la clave proporcionada por el usuario.

Para almacenar un elemento en la tabla hash, se aplica una función hash a la clave del elemento para convertirla en un número. Luego, se mapea el resultado de la función hash al espacio de direcciones del arreglo utilizado como soporte mediante la función módulo. Esto proporciona un índice válido para la tabla.

El elemento se almacena en la posición de la tabla obtenida en el paso anterior. Si esa posición ya contiene otro elemento, se produce una colisión. Para eso voy a tratarlo como una lista de nodos enlazados y voy a insertar en la primera posicion y "mover" esa lista

La función devuelve el hash si pudo guardar el elemento correctamente, o NULL si no pudo hacerlo.

<div align="center">
<img width="100%" src="img/insertar.drawio.svg">
</div>

-Rehash-

La funcion tambien contempla si se supera el factor de carga a la hora de insertar y cuando el factor de carga es >= 0.75. Si se supera se rehashea y despues se inserta el nuevo elemento

<div align="center">
<img width="100%" src="img/rehasheo_nueva.svg">
</div>


### hash_quitar
Permite eliminar un elemento de la tabla hash y devuelve el elemento eliminado. En caso de no encontrar el elemento o si se produce un error, la función devuelve NULL. Para realizar esta operación, se proporciona la clave del objeto que se desea eliminar. Luego, se procede a eliminar el valor asociado a esa clave de la tabla.

A la hora de ser un espacio de la tabla hash donde hay mas de un elemento , se recorre esa "lista" y se tiene en cuenta el anterior asi no se pierde el hilo de la lista enlazada. Por eso la complejidad es O(N) N siendo la cantidad de nodos en la lista enlazada

<div align="center">
<img width="100%" src="img/quitar.drawio.svg">
</div>

### hash_obtener

Devuelve un elemento de la tabla hash que corresponde a la clave proporcionada, o NULL si dicho elemento no existe o en caso de error. Para recuperar los datos, solo se necesita conocer la clave del elemento. Se aplica la función hash a la clave para obtener un valor que se mapea al espacio de direcciones de la tabla.

Luego, se verifica si el elemento existente en la posición obtenida tiene la misma clave que la empleada. Si la clave coincide, se ha encontrado el elemento deseado. Sin embargo, si la clave es diferente, se debe buscar el elemento utilizando la técnica empleada para resolver colisiones al almacenar elementos en la tabla.

### hash_contiene
Devuelve true si el hash contiene un elemento almacenado con la clave dada o false en caso contrario (o en caso de error).

### hash_cantidad
Devuelve la cantidad de elementos almacenados en el hash o 0 en caso de error.

### hash_destruir
Destruye el hash liberando la memoria reservada.


### hash_destruir_todo
Destruye el hash liberando la memoria reservada y asegurandose deinvocar la funcion destructora con cada elemento almacenado en elhash.

### hash_con_cada_clave
Recorre cada una de las claves almacenadas en la tabla de hash e invoca a lafunción f, pasandole como parámetros la clave, el valor asociado a la clave y el puntero auxiliar.Mientras que queden mas claves o la funcion retorne true, la iteración continúa. Cuando no quedan mas claves o la función devuelve false, la iteración se corta y la función principal retorna.
Devuelve la cantidad de claves totales iteradas (la cantidad de
veces que fue invocada la función) o 0 en caso de error.


