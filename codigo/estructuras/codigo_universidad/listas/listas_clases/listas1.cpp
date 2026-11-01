#include <iostream>

/*
Legalmente el profesor maneja el tema usando .hpp y .cpp 
Por ahora solo dejemoslo de esta manera, todo dentro del cpp
*/
class Nodo {
public:
    int valor;
    Nodo* siguiente;
};

class Lista {
private:
    Nodo* cabeza; // la cabeza ya esta dentro de la clase, ya no debo mandarla por parametro

public:
    Lista() {}

    // operaciones que modifican la lista
    void appendLista(int elemento); // inserta elemento al final 
    void insertarLista(int elemento, int pos); // inserta elemento en la posicion dada
    void delLista(int pos); // borrar elemento de esa posicion

    // operaciones que hacen uso de la lista
    void imprimirLista(); // imprime la lista
    int longLista(); // devuelve la logitud de la lista
    int buscarPorPosicion(int pos); // devuelve el valor en esa posicion
    bool estaVacia(); // devuelve si esta vacia o no
    int minLista(); // devuelve el menor elemento de la lista

    

};