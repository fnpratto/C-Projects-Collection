<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP1

## Repositorio de (Florencia Pratto) - (110416) - (fnpratto@gmail.com)

- Para compilar:

```bash
gcc src/*.c src/tp1/*.c src/hash/*.c src/texto/*.c pruebas_chanutron.c -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 
```

- Para ejecutar:

```bash
./tp2
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
```

---
# PRIMERA PARTE #

*Utilice el tp1.c ya implementado en el TP1. Explique cómo se podría reemplazar el vector dinámico de pokemones en la estructura hospital_t por algún otro TDA visto en la materia. ¿Que TDA conviene utilizar? ¿Que problema habría la reemplazar dicha estructura? ¿Habría algún problema con las pruebas? Justificar la respuesta. Selecciones por lo menos 2 TDA de los vistos en la materia y arme una tabla con la complejidad de cada una de las operaciones de tp1.h si se utilizara dicho TDA. (Por ejemplo, si usaramos una lista enlazada, la complejidad de crear el hospital es tanto por tal cosa, de recorrer el hospital es tal otra complejidad, etc).*


Para reemplazar el vector dinámico de pokemones en la estructura hospital_t, se podría utilizar una estructura de árbol binario de búsqueda (ABB). Este TDA sería adecuado en este caso, ya que proporciona una búsqueda mas eficiente

El problema principal al reemplazar el vector dinámico con un ABB sería la inserción y el mantenimiento del árbol balanceado y ordenado. La inserción de nuevos pokemones requeriría realizar las operaciones necesarias para mantener la propiedad del ABB, lo cual puede ser más complejo que en el caso de un vector dinámico. Sin embargo, la búsqueda y eliminación de elementos serían mucho más rápidas y eficientes en comparación con un vector dinámico.

A continuación, se presentan dos TDA adicionales que podrían ser utilizados como alternativas al vector dinámico y una tabla que muestra la complejidad de cada operación en tp1.h si se utilizaran dichos TDA:

```bash

 |     Tarea         | Lista enlazada |     AVL     |
 |-------------------|----------------|-------------|
 |Crear el hospital  |    O(1)        |    O(1)     |
 |Recorrer el hospita|    O(n)        |    O(n)     |
 |Agregar un Pokémon |    O(1)        |  O(log n)   |
 |Buscar un Pokémon  |    O(n)        |  O(log n)   |
 |Eliminar un Pokémon|    O(n)        |  O(log n)   |
 |-------------------|----------------|-------------|

 ```

La complejidad de cada operación puede variar según la implementación específica de cada TDA. En el caso del ABB, si se utiliza un árbol AVL, se garantiza el balanceo automático, lo que mejora la eficiencia de las operaciones de búsqueda, inserción y eliminación en comparación con un ABB no balanceado.

Reemplazar el vector dinámico de pokemones con un TDA como un árbol binario de búsqueda o una lista enlazada tiene sus ventajas. La elección depende de las necesidades específicas del programa, considerando factores como la frecuencia de operaciones de búsqueda, inserción y eliminación.


---
# SEGUNDA PARTE #

**Detalles del TDA Menú**
Tenemos una estructura de datos llamada tda_menu que utiliza un hash para almacenar comandos. Cada comando se representa como una clave en el hash y tiene asociados una descripción de su funcionalidad y la función correspondiente que ejecuta dicho comando. 

```c
struct menu {
	hash_t *comandos;
	//hash_t * sinonimos_comandos;
};
```

```c
struct comando {
	const char *nombre;
	const char *descripcion;
	bool (*funcion)(void *);
};
```

***Primitivas del TDA_MENU;***

- menu_t  *menu_agregar_opcion(menu_t * menu, const char *nombre, bool (*funcion)(void*));
crea un comando reservando memoria e inserta el puntero de el comando en el menu

- menu_t *menu_crear(); 
reserva memoria para el menú 

- bool menu_continua(menu_t *menu);

- void menu_cortar(menu_t * menu);

- void menu_activar(menu_t* menu);

- bool ejecutar_comando(menu_t *menu, const char *comando);
obteniene el nombre del comando recibida en el hash de comandos, de lo contrario prueba con hash sinónimos y devuelve la acción enviando por parámetro el auxiliar recibido, si fuera encontrado.

- void pedir_comando(menu_t * menu, void* aux);

- ejecutar_comando(menu,comando, aux); // el auxiliar es el menu_hospitales el cual se van a hacer las modificaciones

- size_t menu_cantidad(menu_t *menu);

- void menu_destruir(menu_t *menu);

**Detalles del TP2**

El TDA Menú se utiliza en el Trabajo Práctico 2 como parte de la estructura de menu_hospitales. Esta estructura incluye un hash con la información de los hospitales, así como el menú correspondiente. Además, se guarda la cantidad de hospitales y el ID del hospital activo para facilitar la ejecución de ciertos comandos.

```c
struct menu_hospitales {
	menu_t * menu;
	hash_t * hospitales;
	char * id_hospital_activo;
	size_t cantidad;
};

struct nodo {
	char * id; 
	hospital_t * hospital; 
    const char *nombre;
	struct nodo *siguiente;
};
```

## Aclaraciones del funcionamiento

El funcionamiento del TP2 se basa en los siguientes puntos:

1. Crear la estructura menu_hospitales, que incluye la definición de los comandos que se utilizarán en el TP2 y la creación del hash de hospitales.
2. Solicitar al usuario que ingrese un comando.
3.  Buscar el comando seleccionado en la estructura menu_hospitales, específicamente en el hash de comandos. Una vez encontrado, se ejecuta el comando correspondiente y se realizan las modificaciones necesarias en la tabla de datos de menu_hospitales.
4.  Evaluar si es posible solicitar otro comando, lo cual se determina revisando el valor booleano dentro de la estructura menu_hospitales. Si este valor es true, se puede seguir solicitando comandos; si es false, se finaliza el proceso.

En resumen, el TP2 se centra en la creación y gestión de un menú de hospitales, donde los comandos ejecutados a través del menú modifican la tabla de datos del menú y permiten al usuario interactuar con la información de los hospitales.

A continuación se presentan los 8 comandos que se agregaron y usaron para el tp2:

**S (salir/exit)**
Este comando permite salir del programa y se encarga de destruir todo el menú llamando a una función destructora.

**H (ayuda/help)**
Al seleccionar esta opción, se proporciona información sobre posibles problemas según el estado actual del programa.

**C (cargar)**
Al ingresar el nombre de un archivo, se crea un hospital. Es importante realizar una copia de este nombre, ya que es un dato ingresado por el usuario y podría perderse. Una vez creado el hospital, se inserta en el menú utilizando su nombre como clave y el propio hospital como elemento.

**E (estado)**
Este comando itera sobre todo el menú utilizando una función similar a la implementada en el hash. Cuando encuentra un nodo no nulo, imprime el nombre del elemento (hospital) y muestra si está activo o no.

**A (activar)**
Se solicita el número de identificación de un hospital para activarlo. Para ello, se utiliza la función "menu_con_cada_clave" dos veces: una para verificar si hay un hospital activo y desactivarlo (ya que solo puede haber uno activo a la vez), y otra vez para buscar el hospital con el número de identificación proporcionado y activarlo.

**M (mostrar) // L (listar)**
Estos comandos iteran sobre el menú utilizando la función "menu_con_cada_clave" para buscar el hospital activo. Una vez encontrado, se itera sobre cada Pokémon en el hospital y se muestra o lista según el formato correspondiente.

**D (destruir)**
En primer lugar, se busca la clave del hospital activo iterando sobre el menú. Luego, se llama a la función "menu_quitar", que requiere la clave y el menú para eliminar un nodo del menú.
