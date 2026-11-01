#include "ListaDoble.hpp"
#include <iostream>

ListaDoble::ListaDoble(): cabeza(nullptr), cola(nullptr) {}

ListaDoble::~ListaDoble() {
    NodoDoble* auxiliar = cabeza;

    while(auxiliar != nullptr) {
        NodoDoble* siguiente = auxiliar->siguiente;
        delete auxiliar;

        auxiliar = siguiente;
    }
}

void ListaDoble::agregarInicio(int valor) {
    if(cabeza == nullptr) {
        NodoDoble* nuevo = new NodoDoble(valor, cabeza, cola);
        cabeza = nuevo;
        cola = nuevo;
        return;
    }

    NodoDoble* nuevo = new NodoDoble(valor, cabeza, nullptr);
    cabeza->anterior = nuevo; // ya no es null
    cabeza = nuevo;
}

void ListaDoble::agregarFinal(int valor) {
    if(cabeza == nullptr) {
        NodoDoble* nuevo = new NodoDoble(valor, cabeza, cola);
        cabeza = nuevo;
        cola = nuevo;
        return;
    }

    NodoDoble* nuevo = new NodoDoble(valor, nullptr, cola);
    cola->siguiente = nuevo;
    cola = nuevo;
}

void ListaDoble::agregarMedioIndice(int indice, int valor) {
    if(indice == 0 && cabeza == nullptr) {
        // agregar un primer elemento
        NodoDoble* nuevo = new NodoDoble(valor, cabeza, cola);
        cabeza = nuevo;
        cola = nuevo;
        return;
    }
    if(indice == 0 && cabeza != nullptr) {
        // reasignar cabeza
        NodoDoble* nuevo = new NodoDoble(valor, cabeza, nullptr);
        cabeza->anterior = nuevo;
        cabeza = nuevo;
        return;
    }

    NodoDoble* auxiliar = cabeza;
    int cuenta = 0;

    while(cuenta < indice - 1) {
        if(auxiliar == cola) {
            // llego al final y aun no llega al indice del nodo
            return;
        }
        auxiliar = auxiliar->siguiente;
        cuenta++;
    }

    if(auxiliar == cola) {
        NodoDoble* nuevo = new NodoDoble(valor, nullptr, cola);
        cola->siguiente = nuevo;
        cola = nuevo;
        return;
    }
    NodoDoble* siguienteNodo = auxiliar->siguiente;
    NodoDoble* nuevo = new NodoDoble(valor, siguienteNodo, auxiliar);
    auxiliar->siguiente = nuevo;
    siguienteNodo->anterior = nuevo;
}


// ahora insertar en el medio pero por valor
void ListaDoble::insertarMedioValor(int valor, int valorBuscar) {
    if(cabeza == nullptr) {
        return; // no hay elementos para comparar
    }

    NodoDoble* auxiliar = cabeza;

    while(auxiliar != nullptr) {
        if(auxiliar->valor == valorBuscar) {
            if(cabeza == cola) {
                // significa que solo hay un elemento
                NodoDoble* nuevo = new NodoDoble(valor, nullptr, cabeza);
                cabeza->siguiente = nuevo;
                cola = nuevo;
                return;
            } else if(auxiliar == cabeza) {
                NodoDoble* segundo = cabeza->siguiente;
                NodoDoble* nuevo = new NodoDoble(valor, segundo, cabeza);
                segundo->anterior = nuevo;
                cabeza->siguiente = nuevo;
                return;
            } else if(auxiliar == cola) {
                NodoDoble* nuevo = new NodoDoble(valor, nullptr, cola);
                cola->siguiente = nuevo;
                cola = nuevo;
                return;
            } else {
                NodoDoble* siguienteNodo = auxiliar->siguiente;
                NodoDoble* nuevo = new NodoDoble(valor, siguienteNodo, auxiliar);
                auxiliar->siguiente = nuevo;
                siguienteNodo->anterior = nuevo;
                return;
            }

        } else {
            auxiliar = auxiliar->siguiente;
        }
    }
    // si llego aca es que termino la lista y no encontro el valor buscado
    return;
}


void ListaDoble::eliminarPorValor(int valorEliminar) {
    if(cabeza == nullptr) {
        return;
    }

    NodoDoble* auxiliar = cabeza;

    while(auxiliar != nullptr) {
        NodoDoble* siguienteNodo = auxiliar->siguiente;
        if(auxiliar->valor == valorEliminar) {
            if(cabeza == cola) {
                // solo hay un elemento
                cabeza = nullptr;
                cola = nullptr;
            } else if(auxiliar == cabeza) {
                siguienteNodo->anterior = nullptr;
                cabeza = siguienteNodo;
            } else if(auxiliar == cola) {
                NodoDoble* anterior = auxiliar->anterior;
                anterior->siguiente = nullptr;
                cola = anterior;
            } else {
                NodoDoble* anterior = auxiliar->anterior;
                anterior->siguiente = siguienteNodo;
                siguienteNodo->anterior = anterior;
            }
            delete auxiliar;
        }
        auxiliar = siguienteNodo;
    }
    // si salio y no encontro el elemento a eliminar
    return;
}

// metodos de impresion (Adelante y Atras)
void ListaDoble::imprimirAdelante() {
    NodoDoble* auxiliar = cabeza;

    while(auxiliar != nullptr) {
        std::cout<< auxiliar->valor <<", ";
        auxiliar = auxiliar->siguiente;
    }
    std::cout<<std::endl;
}

void ListaDoble::imprimirAtras() {
    NodoDoble* auxiliar = cola;

    while(auxiliar != nullptr) {
        std::cout<< auxiliar->valor <<", ";
        auxiliar = auxiliar->anterior;
    }
    std::cout<<std::endl;
}

void ListaDoble::invertir() {
    if(cabeza == cola || cabeza == nullptr) {
        return;
    }

    NodoDoble* auxiliar = cabeza;

    while(auxiliar != nullptr) {
        NodoDoble* siguienteNodo = auxiliar->siguiente;
        NodoDoble* anteriorNodo = auxiliar->anterior;

        auxiliar->anterior = siguienteNodo;
        auxiliar->siguiente = anteriorNodo;

        auxiliar = siguienteNodo;
    }
    NodoDoble* cabezaFinal = cabeza;
    NodoDoble* colaFinal = cola;

    cabeza = colaFinal;
    cola = cabezaFinal;
}

// fusionar dos listas y ordenarlas, que queden en orden 

void ListaDoble::fusionarOrdenadamente(ListaDoble& lista) {
    if(cabeza == nullptr && lista.cabeza != nullptr) {
        // una sola lista
        cabeza = lista.cabeza;
        cola = lista.cola;

        lista.cabeza = nullptr;
        lista.cola = nullptr;
        return;
    } else if(cabeza != nullptr && lista.cabeza == nullptr) {
        // No hay nada que agregar
        return;
    }

    // las listas ya estan ordenadas de forma ascendente

    NodoDoble* auxiliar1 = lista.cabeza;
    NodoDoble* auxiliar2 = cabeza;

    while(auxiliar1 != nullptr) {
        NodoDoble* siguienteComparar = auxiliar1->siguiente;

        while(auxiliar2 != nullptr) {
            if(auxiliar1->valor >= auxiliar2->valor) {
                auxiliar2 = auxiliar2->siguiente;
            } else {
                NodoDoble* anterior2 = auxiliar2->anterior;
                if(auxiliar2 == cabeza) {   
                    auxiliar1->anterior = nullptr;
                    auxiliar1->siguiente = cabeza;
                    cabeza->anterior = auxiliar1;
                    cabeza = auxiliar1;
                    break;
                } else {
                    auxiliar1->anterior = anterior2;
                    auxiliar1->siguiente = auxiliar2;
                    anterior2->siguiente = auxiliar1;
                    auxiliar2->anterior= auxiliar1;
                    break;
                }
            }
        }
        if(auxiliar2 == nullptr) {
            // Si sepaso ese pasa a ser la nueva cola
            auxiliar1->siguiente = nullptr;
            auxiliar1->anterior = cola;
            cola->siguiente = auxiliar1;
            cola = auxiliar1;
        } 
        auxiliar1 = siguienteComparar;
    }
    lista.cabeza = nullptr;
    lista.cola = nullptr;
}