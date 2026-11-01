#ifndef __LISTA_H
#define __LISTA_H

#include <iostream>

using namespace std;


class Nodo{
public:
    int dato;
    Nodo* sig;
};

class Lista{
private:
    Nodo* head;
public:

    // OPERACIONES DEL LA ESTRUCTURA DE DATOS
    Lista();

    // OPERACIONES QUE MODIFICAN LA LISTA
    void appendLista(int elem); // inserta un elemento al final de la lista
    void insertLista(int elem, int pos); // inserta un elemento en una posición dada
    void insSortLista(int elem); // inserta un elemento de forma ordenada de menor a mayor
    void delLista(int pos); // elimina un elemento en una posicón dada

    // OPERACIONES DE CONSULTA A LA LISTA
    void printLista(); // muestra los elementos de la lista
    int lenLista(); // retorna un entero con el tamaño de la lista
    int searchPosLista(int pos); // busca un elemento en una posición dada y retorna el valor hallado
    bool isEmptyLista(); // indica si la lista está vacía o no
    int minLista(); // retorna el menor elemento de una lista

    // RETOS A RESOLVER CON LA ESTRUCTURA, APARTE DE LAS OPERACIONES
    //ToDo: inserta al final de la lista un nodo cuyo dato es la suma de todos los elementos de la lista
    void insSumLista();
    //ToDo: Eliminar todos los nodos de la lista cuyo dato sea un valor impar
    void delOddLista();
    //ToDo: Hallar el elemento mayor de la lista
    int maxLista();

};

#endif
