#include <iostream>

class NodoSimple {
public:
    int valor;
    NodoSimple* siguiente;

    NodoSimple(int v, NodoSimple* s): valor(v), siguiente(s) {} 
};

/*
class NodoDoble {
public:
    int valor;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(int v, NodoDoble* s, NodoDoble* a): valor(v), siguiente(s), anterior(a) {}
};
*/



class ListaSimple {
private:   
    NodoSimple* cabeza;
    NodoSimple* cola;
public:
    ListaSimple(): cabeza(nullptr), cola(nullptr) {}

    ~ListaSimple() {
        NodoSimple* auxiliar = cabeza;
        while(auxiliar != nullptr) {
            NodoSimple* siguienteNodo = auxiliar->siguiente;
            delete auxiliar;
            auxiliar = siguienteNodo;
        }
    }

    void agregarInicio(int valor) {
        if(cabeza == nullptr) {
            NodoSimple* nuevo = new NodoSimple(valor, nullptr);
            cabeza = nuevo;
            cola = nuevo;
            return;
        }
        NodoSimple* nuevo = new NodoSimple(valor, cabeza);
        cabeza = nuevo;
    }

    void agregarFinal(int valor) {
        if(cabeza == nullptr) {
            NodoSimple* nuevo = new NodoSimple(valor, nullptr);
            cabeza = nuevo;
            cola = nuevo;
            return;
        }
        NodoSimple* nuevo = new NodoSimple(valor, nullptr);
        cola->siguiente = nuevo;
        cola = nuevo;
    }

    // retos simples, 1. devolver el indice del medio
    int valorDelMedio() {
        if(cabeza == nullptr) {
            return -1;
        }
        
        NodoSimple* recorrido = cabeza;
        NodoSimple* medio = cabeza;

        while(recorrido != nullptr && recorrido->siguiente != nullptr) {
            NodoSimple* dosEnDos = recorrido->siguiente;

            recorrido = dosEnDos->siguiente;
            medio = medio->siguiente;
        }
        return medio->valor;

    }

    // ejercicio 4, eliminar con indice desde el final
    void eliminarDesdeElFinal(int indice) {
        if(cabeza == nullptr || indice <= 0 ) {
            // lista vacia
            return;
        } 

        NodoSimple* adelantado = cabeza;
        NodoSimple* atrasado = cabeza;
        int cuenta = 0;

        while(adelantado != nullptr) {
            if(cuenta < indice + 1) {
                adelantado = adelantado->siguiente;
                cuenta++;
            } else {
                adelantado = adelantado->siguiente;
                atrasado = atrasado->siguiente;
            }
        }
        
        // cuenta dice en que caso estamos:
        if(cuenta < indice) {
            // el indice es mayor que el tamanio de la lista, no hay nada que eliminar
            return;
        }

        if(cuenta == indice) {
            // el nodo a eliminar es la cabeza (no hay nodo anterior)
            NodoSimple* objetivo = cabeza;
            cabeza = cabeza->siguiente;
            if(cabeza == nullptr) {
                cola = nullptr; // la lista quedo vacia
            }
            delete objetivo;
            return;
        }

        // caso normal: atrasado esta justo antes del nodo a eliminar
        NodoSimple* objetivo = atrasado->siguiente;
        atrasado->siguiente = objetivo->siguiente;
        if(objetivo == cola) {
            cola = atrasado; // se elimino el ultimo
        }
        delete objetivo;
    }

};


int main() {

    return 0;
}