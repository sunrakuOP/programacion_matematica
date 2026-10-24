#include <iostream>

class Nodo {
public:
    int valor;
    Nodo* siguiente;

    Nodo(int v, Nodo* s): valor(v), siguiente(s) {} 
};

class Cola {
private:
    Nodo* cabeza;
    Nodo* cola;
public:
    Cola(): cabeza(nullptr), cola(nullptr) {}

    ~Cola() {
        Nodo* auxiliar = cabeza;
        while(auxiliar != nullptr) {
            Nodo* siguienteNodo = auxiliar->siguiente;
            delete auxiliar;
            auxiliar = siguienteNodo;
        }
    }

    bool estaVacia() {
        if(cabeza == nullptr) return true;
        return false;
    }

    void enqueue(int valor) {
        if(estaVacia()) {
            Nodo* nuevo = new Nodo(valor, nullptr);
            cabeza = nuevo;
            cola = nuevo;
            return;
        }
        Nodo* nuevo = new Nodo(valor, nullptr);
        cola->siguiente = nuevo;
        cola = nuevo;
    }

    int dequeue() {
        if(estaVacia()) {
            return -1;
        }
        Nodo* temporal = cabeza;
        int valor = temporal->valor;
        cabeza = temporal->siguiente;
        if(cabeza == nullptr) {
            cola = nullptr;
        }
        delete temporal;
        return valor;
    }

    int front() {
        if(estaVacia()) {
            return -1;
        }
        return cabeza->valor;
    }

};


int main() {


    return 0;
}