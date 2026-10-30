#include <iostream>

class Nodo {
public:
    int valor;
    Nodo* siguiente;

    Nodo(int v, Nodo* s): valor(v), siguiente(s) {}
};

class Pila {
private:
    Nodo* cabeza;
public:
    Pila(): cabeza(nullptr) {}
    ~Pila() {
        Nodo* auxiliar = cabeza;

        while(auxiliar != nullptr) {
            Nodo* siguienteNodo = auxiliar->siguiente;
            delete auxiliar;
            auxiliar = siguienteNodo;
        }
    }

    bool estaVacia() {
        if(cabeza == nullptr) {
            return true;
        }
        return false;

    }
    void push(int valor) {
        // solo puede agregarse por la cabeza
        Nodo* nuevo = new Nodo(valor, cabeza);
        cabeza = nuevo;
    }

    void pop() {
        if(cabeza == nullptr) {
            return;
        }
        Nodo* nuevaCabeza = cabeza->siguiente;
        delete cabeza;
        cabeza = nuevaCabeza;
    }

    int top() {
        if(cabeza == nullptr) {
            return -1;
        }
        return cabeza->valor;
    }

};


// ================== EJERCICIO PRE PARCIAL ========================

class NodoMax {
public:
    int valor;
    int maxAnterior;
    NodoMax* siguiente;

    NodoMax(int v, int mx, NodoMax* s): valor(v), maxAnterior(mx), siguiente(s) {}
};

class PilaMax {
private:
    NodoMax* cabeza;
public: 
    PilaMax(): cabeza(nullptr) {}

    void push(int valor) {
        int max = 0;
        if(cabeza == nullptr || valor > cabeza->maxAnterior) {
            max = valor;
        }  else {
            max = cabeza->maxAnterior;
        }
        NodoMax* nuevo = new NodoMax(valor, max, cabeza);
        cabeza = nuevo;
    } 

};


int main() {

    return 0;
}