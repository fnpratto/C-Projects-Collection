# TDA ABB

## Repositorio de (Florencia Pratto) - (110416) - (fnpratto@fi.uba.ar)

*Árbol Binario de Búsqueda*

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
- Lo que el usario quiera guardar en los nodos del arbol , es privado y le dejamos la responsabilidad de liberar memoria si la ocupa
- Los elementos menores del ABB van a estar del lado izquierdo y los mayores del lado derecho
- Al borrar nodos con dos hijos no nulos, se reemplaza dicho nodo con el predecesor inorden
- Funcionamiento del comparador; Al árbol binario se le agrega un comparador y cada nodo del árbol posee un valor .Determina la relación de orden de los diferentes punteros, sin necesidad de tener información extra , devuelve 0,<0 o >0
- Para determinar si un ́arbol binario esta equilibrado, se calcula su factor de equilibrio. El factor de equilibrio de un ́arbol binario es la diferencia en altura entre los sub ́arboles derecho e izquierdo. Si la altura del sub ́arbol izquierdo es hi y la altura del sub ́arbol derecho como hd , entonces el factor de equilibrio del ́arbol binario se determina por la siguiente formula: ```Fe = hd − hi```

---

## Estructuras desarrolladas

#### abb;

```c
struct abb {
	nodo_abb_t *nodo_raiz;
	abb_comparador comparador;
	size_t tamanio;
};
```

#### Nodo;

```c
struct nodo_abb {
	void *elemento;
	struct nodo_abb *izquierda;
	struct nodo_abb *derecha;
};
```

<div align="center">
<img width="50%" src="img/estructura.drawio.svg">
</div>

*celeste indica que es un struct nodo_abb 

## Aclaraciones del funcionamiento

## Funciones del abb.h

### abb_con_cada_elemento

Recorre el arbol e invoca la funcion con cada elemento almacenado en el mismo como primer parámetro. El puntero aux se pasa como segundo parámetro a la función. Si la función devuelve false, se finaliza el recorrido aun si quedan elementos por recorrer. Si devuelve true se sigue recorriendo mientras queden elementos. Recorrido especifica el tipo de recorrido a realizar. Devuelve la cantidad de veces que fue invocada la función.
Para eso uso una funcion recursiva segun el recorrido elegido.

### abb_recorrer

Recorre el arbol según el recorrido que se le manda por parametro y va almacenando los elementos en el array hasta completar el recorrido o quedarse sin espacio en el array atravez de una funcion booleana;rellenar_array. Devuelve el tamaño de el array con los elementos guardados.

<div align="center">
<img width="50%" src="img/abb_recorrer.svg">
</div>

En el ejemplo se recorre el mismo array con 3 recorridos diferentes y devuelven 7.

## Respuestas a las preguntas teóricas
### Conceptos , Graficos 

Un árbol es una colección de nodos. Los nodos son elementos o vértices del árbol. Los arboles estan compuestos por una raiz la cual es unica esta conectado a sus sub-arboles mediante el nodo hijo. Y el nodo hijo esta conectado, a la raíz mediante el nodo padre. El nodo raíz esta solamente conectado a dos sub-arboles, lo cual nos permite determinar la noción de izquierda y derecha.
Un árbol puede estar FULL y complete.
Lo importante es saber como implementeamors el arbol y que tipo de arbol usamos ya que diferentes arboles tienen diferentes usos y no tienen la misma complejidad para la misma funcion.

Un árbol binario es una esctructura de datos donde cada elemento tendra como maximo 2 hijos. Un árbol Binario de Busqueda es un tipo de arbol binario que cumple la condicion de estar ordenado, de manera que todos los nodos a la derecha de un nodo cumpliran cierta condicion al compararlos ( eg. ser mayores ) y los que no iran a la izquierda.

###  Complejidad/ Funcionamiento del TDA

- abb_crear: O(1), la funcion reservara memoria para el arbol, independiente del tamaño del arbol
<div align="center">
<img width="70%" src="img/crear_abbdrawio.svg">
</div>

- abb_insertar: O(n), el peor caso sera cuando el arbol se degenere como una lista y halla que intertar un elemento al final, por lo que habra que recorrer todos los elementos. Para un arbol balanceado la complejidad es O(logN)

Funcionamiento;
Primero creo el nodo que voy a insertar
<div align="center">
<img width="70%" src="img/crear_nodo.drawio.svg">
</div>
 
Tengo varios escenarios
I)El esenario donde no tengo nodos y el arbol es vacio, aca solo asignamos la raiz del arbol al nodo nuevo.
II) Recorro el arbol con el comparador hasta llgar a que un nodo actual a la derecha o izquierda sea NULL

<div align="center">
<img width="70%" src="img/INSERTAR.drawio.svg">
</div>

En el ejemplo que quiero introducir 20, empiezo por 70 , voy a la izquierda y tomo ese nodo izquierdo como actual (35), lo mismo; entre 30/50. EL comparador me da menor a 0 y tomo el 30 como nodo actual. Una vez aca el comparador me da mayor a 0 entonces analizo si su siguiente nodo a la derecha es NULL , si lo es(como es el caso), el nodo de la derecha ahora va estar ocupado por el nuevo nodo y para cortar la iteracion digo que el actual es NULL.(Condicion de corte)


- abb_buscar: O(N), el peor caso sera cuando el arbol se degenere como una lista y halla que buscar un elemento al final, por lo que habra que recorrer todos los elementos. Para un arbol balanceado la complejidad es O(logN)

<div align="center">
<img width="70%" src="img/buscar.drawio.svg">
</div>

Por ejemplo quiero buscar el 90;

En el tp a la hora de buscar primero se compara que no este vacio y que el comparador sea no nulo.Empieza en el 70(raiz) y lo define como nodo_actual (el cual va iterar hasta llegar al nodo buscado o devuelve null si no lo encuentra) segun la comparacion del numero buscado como es mayor el que buscamos , va ir por el nodo derecho; 100, como es menor el valor buscado , va moverse al nodo izquierda, lo compara y una vez encontrado devuelve el elemento del nodo.

- abb_quitar: La complejidad de sus operaciones  en un arbol binario es O(log(n)) pero en su peor caso el cual es que el arbol no este balanceado y termine siendo una lista , en ese caso su complejidad es O(n). 

Los 3 casos posibles;

I)El nodo a borrar no tiene hijos( es un nodo hoja). Se borra

II)El nodo a borrar tiene un hijo. El nodo hijo pasa a tomar el lugar del padre y se borra al padre.

III)El nodo a borrar tiene 2 hijos. Se busca a su predecesor, que puede ser el mayor de los menores o el menor de los mayores convención que se tiene que tomar a lo largo de todo la implementación del árbol. Ese nodo sera la nueva raíz del árbol y se borra la raíz vieja


<div align="center">
<img width="100%" src="img/quitar.drawio(1).svg">
</div>
En el ejemplo para quitar primero tenemos que buscar el elemento y despues ver si necesitamos remmplazarlo por un nodo sucessor para mantener la continuidad ( en este caso tomamos de sub arbol izquierdo el nodo que este mas a la derecha). El reemplazo es mas intuitivo cuando es un nodo hoja ya que no hay reemplazo como en el ejemplo seria el nodo 20 , tambien puede pasar que el nodo que eliminamos tenga nodos hojas entonces solo reemplazamos por el nodo izquierda. Pero el caso mas complicado seria a la hora como pasa en el ejemplo de quitar una raiz, va por sub arbol izquierdo(nodo 50) y ahi va a la derecha ->60->70. Una  vez que se encuentra que el nodo actual no tiene mas nodo a la derecha , reemplaza este.


- abb_vacio: O(1), chequea el tamaño y que el arbol sea no nulo 

- abb_destruir_todo: O(N), el peor caso sera cuando el arbol se degenere como una lista y halla que eliminar un elemento al final, por lo que habra que recorrer todos los elementos. para un arbol balanceado la complejidad es O(logN)
El objetivo de la funcion de destruccion es facilitar la liberacion de memoria dinamica que el usuario debe hacer. Sin ella el usuario deberia buscar el elemento que quiera eliminar, guardar una referencia, eliminarlo del arbol y luego liberar la referencia. Implementando la funcion de destruccion, el usuario solo necesita eliminarlo del arbol y la funcion liberara la memoria, simplificando el proceso.

<div align="center">
<img width="100%" src="img/eliminacion.drawio(2).svg">
</div>
En la implementacion tenemos un abb_destruir que llama a destruir_todo donde ahi va ir destruyendo los nodos de manera recursiva , donde cuando si estamos en el nodo raiz , se divide en dos,los nodos por la izquierda y derecha y va avanzando hasta llegar a un nodo nulo. Y va de "atras" para "adelante"(abajo para arriba) y se destruye el nodo primero aplicandole el destructor que manda el usuario por si quiere hacer algun free como en el ejemplo seria 1'era eliminacion bis y 2'da eliminacion bis, y despues se libera la memoria de el nodo , asi hasta la raiz y despues se libera el arbol.
Aclaracion: Primero se libera los sub arborles izquierdos.

- recorrido_preorden/inorden/postorden: O(N), para recorrer el arbol debe pasar por cada uno de sus elementos

Se puede recorrer de 3 maneras ; 

Inorden: Primero se visita el sub- ́arbol izquierdo, luego el nodo actual y por ́ultimo el sub- ́arbol derecho.

```c
 if (! nodo )
       return ;

   if ( nodo - > izquierda )
       inorden ( nodo - > izquierda ) ;

   process ( nodo ) ;

   if ( nodo - > derecha )
       inorden ( nodo - > derecha ) ;
```

Postorden: Primero se visita el sub- ́arbol izquierdo, luego al sub-arbol derecho y por ́ultimo al nodo actual

```c
if (! nodo )
       return ;

   if ( nodo - > izquierda )
       postorden ( nodo - > izquierda ) ;

   if ( nodo - > derecha )
       postorden ( nodo - > derecha ) ;

   process ( nodo ) ;
```

Preorden: Primero se visita en nodo actual luego el sub- ́arbol izquierdo y luego el derecho

```c
if (! nodo )
       return ;

   process ( nodo ) ; 

   if ( nodo - > izquierda )
       preorden ( nodo - > izquierda ) ;

   if ( nodo - > derecha )
       preorden ( nodo - > derecha ) ;
```

