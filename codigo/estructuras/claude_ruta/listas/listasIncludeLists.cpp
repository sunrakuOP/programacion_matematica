#include <iostream>
#include <list>

/* Listas desde libreria <list>, metodo propio

Ya vimos como funcionan las listas enlazadas usando metodos propios (internamente)
Ahora vamos a verlo de forma mas "facil" usando metodos propios de la libreria

std::list<double> listaEnlazada;
std::list<int> listaValores = { 1,2,3,};

METODOS DE INSERTAR:
    Recordar que la lista crece en esta direccion - elemento1 - elemento2- elemento3 ------>.  al imprimir se hace de atras para adelante 
    1. ush_front(valor) => Agrega al frente (ultimo elemento, de atras para adelante)
    2. push_back(valor) => Agrega al final (primer elemento)
    3. insert(it, valor) => Inserta ANTES de la posicion del iterador 

METODOS PARA QUITAR:
    1. pop_front() => Borra el primer elemento
    2. pop_ back() => Borra el ultimo elemento
    3. erase(it) => Elimina valor de esa posicion
    4. remove(valor) => Busca y borra todas las apariciones de valor 
    5. clear() => Vacia toda la lista
 
METODOS DE LECTURA:
    1. front() => Muestra el primer elemento (ultimo agregado)
    2. back() => Muestra el ultimo elemento (primero agregado)

!! Tambien tiene metodos de tamano y de verificar si esta vacio 
    => .size() es el numero de elementos
    => .empty() entrega si true o false 

!! Se recorre con un for in range normaln y ya 
*/

/* Cuales son las ventajas de lista?????????
Respecto a vector, que es O(n) al insertar elementos, lista es O(1) siempre => ES MAS RAPIDO 


*/

bool buscar(const std::list<int>& lista, int valor) {
    for(const auto& e: lista) {
        if(e == valor) {
            return true;
        }
    }
    return false;
}

int numElementos(const std::list<int>& lista) {
    int contador = 0;
    for(const auto& e: lista) {
        contador++;
    }
    return contador;
}


int main() {
    std::list<int> listaEjercicio = { 58, 26, 9, 9, 23 };

    bool esta = buscar(listaEjercicio, 58);
    int num = numElementos(listaEjercicio);

    return 0;
}