<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA LISTA

## Repositorio de (Florencia Pratto) - (110416) - (fnpratto@fi.uba.ar)

- Para compilar:

```bash
gcc src/*.c pruebas_chanutron.c -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -g pruebba_chanutron
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
# Funcionamiento

**Detalles de implementación**

*Aclaraciones generales*
- Las estructuras de pilas y colas son privadas y no nos interesan ya que las tratamos como listas con ciertas restricciones
- Para las pilas y colas se  usa las funciones provistas por listas.h.
- Lo que esta adentro del nodo que el usario quiera guardar en las listas, no nos interesa. Nada le prohibe al usuario guardar NULL como elemento. Asi que no deberia verificarse el elemento pero si verificar los punteros mandados.

- Se usa nodos simplemente enlazados

---

## Estructuras desarrolladas
#### Nodos;

```c
typedef struct nodo{
    void* elemento;
    void* siguiente; 
} nodo_t;
```
<div align="center">
<img width="50%" src="img/nodo_estructura.svg">
</div>

#### Listas;

```c
typedef struct lista{
	size_t cantidad;
	nodo_t *nodo_inicio;
	nodo_t *nodo_fin;
} lista;
```
<div align="center">
<img width="70%" src="img/lista.drawio.svg">
</div>


#### Iterador externo;

```c
typedef struct lista_iterador {
	nodo_t* nodo_actual;
	lista_t *lista;
} lista_iterador;
```

<div align="center">
<img width="70%" src="img/iterador_externo_estructura.drawio.svg">
</div>


## Aclaraciones del funcionamiento

## Funciones del lista.h
**1. Lista_crear**
Crea la lista reservando la memoria necesaria e inecializa todas . Devuelve un puntero a la lista creada o NULL en caso de error. Uso un return calloc por que si no se crea el calloc me devuelve NULL y ya me inicializa los datos del struct.

<div align="center">
<img width="70%" src="img/crear_lista.drawio.svg">
</div>

**2. Lista_insertar**
Inserta un elemento al final de la lista. Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito. 

**3. Lista_insertar_en_posicion**
Inserta un elemento en la posicion indicada, donde 0 es insertar como primer elemento y 1 es insertar luego del primer elemento. 
En caso de no existir la posicion indicada, lo inserta al final. Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito.

<div align="center">
<img width="70%" src="img/insertar.drawio.svg">
</div>
En el caso I y II se usa la funcion lista_insertar

**4. Lista_quitar**
Quita de la lista el elemento que se encuentra en la ultima posición.Devuelve el elemento removido de la lista o NULL en caso de error. 

<div align="center">
<img width="70%" src="img/quitar.drawio.svg">
</div>

**5. Lista_quitar_de_posicion**
Quita de la lista el elemento que se encuentra en la posición indicada, donde 0 es el primer elemento de la lista. En caso de no existir esa posición se intentará borrar el último elemento. Devuelve el elemento removido de la lista o NULL en caso de error


<div align="center">
<img width="70%" src="img/QUITAR_POSICION.drawio(1).svg">
</div>

**6. lista_elemento_en_posicion**
Devuelve el elemento en la posicion indicada, donde 0 es el primer elemento. Si no existe dicha posicion devuelve NULL.

<div align="center">
<img width="70%" src="img/lista_elemento_en_posicion.drawio.svg">
</div>

**7. lista_buscar_elemento**
Devuelve el primer elemento de la lista que cumple la condición comparador(elemento, contexto) == 0. Si no existe el elemento devuelve NULL.

**8. lista_destruir**
Libera la memoria reservada por la lista. Y para reutilizar funciones llamamos lista_destruir_todo y como no tenemos que eliminar los elementos adentro de la lista, le mandamos una funcion NULL ya que de ese modo no aplica una funcin destructora a cada uno de los elementos de la lista.


**9. lista_destruir_todo**
Libera la memoria reservada para la lista y sus nodos pero además aplica la función destructora dada (si no es NULL) a cada uno de los elementos presentes en la lista.

<div align="center">
<img width="70%" src="img/eliminacion.drawio.svg">
</div>

## Funciones de iterador externo
Para ver en mejor detalle el funcionamiento de los iterador ir a conceptos-> iteradores_externos

**1. lista_iterador_crear**
Crea un iterador para una lista. El iterador creado es válido desde el momento de su creación hasta que no haya mas elementos por recorrer o se modifique la lista iterada (agregando o quitando elementos de la lista)

**2. lista_iterador_tiene_siguiente**
Avanza el iterador al siguiente elemento. Devuelve true si pudo avanzar el iterador o false en caso de q ue no queden elementos o en caso de error.Una vez llegado al último elemento, si se invoca a lista_iterador_elemento_actual, el resultado siempre será NULL.

**3. lista_iterador_avanzar**
Devuelve true si pudo avanzar el iterador o false en caso deque no queden elementos o en caso de error. Una vez llegado al último elemento, si se invoca alista_iterador_elemento_actual, el resultado siempre será NULL. Para eso chequeamos que el nodo_actual del interador no sea NULL y a su vez tambien chequeamos el siguiente para saber si es el ultimo nodo. 

**4. lista_iterador_elemento_actual**
Devuelve el elemento actual del iterador o NULL en caso de que no exista dicho elemento o en caso de error.
Es muy importante chequear que el actual no sea null en vez del siguiente ya que sino me quedaria un nodo sin iterar 

**5. lista_iterador_destruir**
Libera la memoria reservada por el iterador. Cuando liberás la estructura iterador estás liberando sus campos, es un mismo procedimiento. Es importante aclarar que se elimina el pointer a la lista y su nodo actual , la lista y nodo actual siguen teniendo su mismo tamaño en el heap.

<div align="center">
<img width="70%" src="img/eliminar_iterador_externo.drawio.svg">
</div>
 
**6. lista_con_cada_elemento (Iterador Interno)**
Iterador interno. Recorre la lista e invoca la funcion con cada elemento de la misma como primer parámetro. Dicha función puede devolver true si se deben seguir recorriendo elementos o false si se debe dejar de iterar elementos. El puntero contexto se pasa como segundo argumento a la función del usuario. La función devuelve la cantidad de elementos iterados o 0 en caso de error (errores de memoria, función o lista NULL, etc).
[GRAFICO ]

## Funciones del cola.h
**1. cola_crear**
Crea una cola vacía y la devuelve. En caso de error devuelve NULL

**2. cola_encolar**
Encola un elemento en la cola. Devuelve la cola o NULL en caso de error. Para reutilizar las funciones de listas , usamos lista insertar (que inserta al final de la lista) y le mandamos la cola casteada como lista lo cual podemos hacer ya que sus structs son iguales y esa funcion de la lista funciona como encolar en una cola. 

**3. cola_desencolar**
Desencola un elemento de la cola y lo devuelve.Devuelve NULL en caso de error. Para reutilizar las funciones de listas , usamos lista_quitar_de_posicion  (que si se manda posicion 0 , se quita el primer elemento) y le mandamos la cola casteada como lista lo cual podemos hacer ya que sus structs son iguales y esa funcion de la lista funciona como desencolar en una cola

**4. cola_frente**
Devuelve el elemento en el frente de la cola o NULL en caso de que no exista. Para eso uso la funcion lista_primero y casteo la cola como lista.
 
**5.  cola_tamanio**
Devuelve la cantidad de elementos de la cola o 0 si no existe. Para eso uso la funcion lista_tamanio y casteo la cola como lista.

**6. cola_vacia**
Devuelve true si la cola tiene 0 elementos. Para eso uso la funcion lista_vacia y casteo la cola como lista.

**7.cola_destruir**
Libera la memoria reservada por la cola. Para eso uso la funcion lista_destruir y casteo la cola como lista.

## Funciones del pila.h
**1. pila_crear**
Crea una pila vacía y la devuelve. En caso de error devuelve NULL

**2. pila_apilar**
Apila un elemento en la pila. Devuelve la pila o NULL en caso de error. Para reutilizar las funciones de listas , usamos lista insertar (que inserta al final de la lista) y le mandamos la cola casteada como lista lo cual podemos hacer ya que sus structs son iguales y esa funcion de la lista funciona como encolar en una cola

**3. pila_desapilar**
Desapila un elemento de la pila y lo devuelve.Devuelve NULL en caso de error.Para reutilizar las funciones de listas , usamos lista_quitar  (que quita el ultimo elemento de la lista) y le mandamos la cola casteada como lista lo cual podemos hacer ya que sus structs son iguales y esa funcion de la lista funciona como desencolar en una cola

**4. pila_tope**
Devuelve el elemento en el tope de la pila o NULL en caso de que no exista. Para eso uso la funcion lista_primero y casteo la pila como lista.
 
**5. pila_tamanio**
Devuelve la cantidad de elementos de la pila o 0 si no existe.Para eso uso la funcion lista_tamanio y casteo la pila como lista.

**6. pila_vacia**
Devuelve true si la pila tiene 0 elementos.Para eso uso la funcion lista_vacia y casteo la pila como lista.

**7. pila_destruir**
Libera la memoria reservada por la pila.Para eso uso la funcion lista_destruir y casteo la pila como lista.

## Respuestas a las preguntas teóricas

### Conceptos , Graficos 

* Lista Simplemenete enlazada: Una lista es una secuencia de nodos que almacena data, el cual señala a otro nodo el cual tambien tiene data y el ultimo señala a null.Es muy importante a la hora de usar lista de siempre tener referencia de la direccion de el comienzo. La implementación de nodos enlazados hace que cada nodo pueda estar ubicado en distintas partes de la memoria,sin que sea requisito que esta sea contigua. 

Los elementos en la listas son;
  - Head: el primer nodo en una lista enlazada
  - Cola: el último nodo en una lista de "me gusta"
  - Puntero: referencia a otro nodo
  - Node: un objeto que contiene data y puntero(s) Obviamente al solo tener referencia del proximo nodo , no se puede ir para atras (Al contrario que la lista doblemente enlazada donde se tiene que cada nodo posee un enlace con el nodo siguiente )

<div align="center">
<img width="70%" src="img/func_lista.svg">
</div>

* Pila: La pila funciona con un orden LIFO(Last In, First Out), lo que quiere decir que el último elemento que fue apilado será el primero en salir, denominado tope.

<div align="center">
<img width="70%" src="img/pila.drawio.svg">
</div>

* Cola: posee un orden FIFO (First In, First Out), lo que implica que primer elemento que entró a la cola será el primer elemento en salir de ella, se tiene un "frente" de la cola, se puede hacer analogía a una cola de supermercado, donde el que llegó primero será el primero en salir.

<div align="center">
<img width="70%" src="img/COLA.drawio.svg">
</div>

* Iterador Interno: un iterador interno es una forma de recorrer toda una lista condicionada por una función o parámetro que el usuario decide. No requiere de estas primitivas externas

* Iterador Externo: El iterador externo como indica su nombre utiliza cosas externas para recorrer la lista. Este cuenta con una serie de primitivas propias que utiliza para recorrerla. En la aplicacion normalmente posee un campo en el cual tiene al elemento al que apunta y con sus primitivas puede saber si tiene o no siguiente, puede avanzar entre otras cosas. el iterador deja de servir cuando llega al fin de la lista o cuando la lista es modificada.

<div align="center">
<img width="70%" src="img/iterador externo.drawio.svg">
</div>

###  Complejidad
- En una lista simplemente enlazada;
Insertar al inicio y al final es O(1) ya que tenemos punteros en esas posiciones. Lo mismo con su busqueda/obtener en esas posiciones pero en general, La busqueda/obtener en su peor caso que es el medio donde no tengo informacion es O(N) ya que tiene que revisar todos los elementos uno por uno. La eliminacion al inicio es O(1) y la eliminacion al final es O(n).

*La complejidada de la pila y cola como las trato como listas simplemente enlazadas; tienen la misma complejidad que las explicadas anteriormente respecivamente usando como sinonimo apilar a insertar al final y desapilar como quitar al final, encolar como insertar al final y desencolar como quitar al inicio pero en vez de un puntero llamado nodo_final , en la pila tengo un tope y en la cola, cola_frente.

- En una lista doblemente enlazada se tiene la misma complejidad ya que tenemos solo los extremos , la unica variante es que nos podemos mover de atras para adelante y empezar de cualquiera de los dos extremos.

- En un vector dinámico las operaciones push y pull son o(n) y de eliminar al principio O(1) y al final o(n)

