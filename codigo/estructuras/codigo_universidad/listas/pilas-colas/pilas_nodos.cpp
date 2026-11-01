#include <iostream>

/* PILAS


*/

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
        cabeza = nullptr; 
    }

    bool estaVacia() const {
        if(cabeza == nullptr) {
            return true;
        } 
        return false;
    }

    void push(int valor) {
        Nodo* nuevo = new Nodo(valor, cabeza);
        cabeza = nuevo;
    }

    int top() const {
        if(estaVacia()) {
            return -1;
        } 
        return cabeza->valor;
    }
 
    void pop() {
        if(estaVacia()) {
            return;
        } 
        Nodo* segundo = cabeza->siguiente;
        delete cabeza;
        cabeza = segundo;
    }

    void imprimir() const {
        if(estaVacia()) {
            return;
        }
        Nodo* auxiliar = cabeza;
        while(auxiliar != nullptr) {
            std::cout<< auxiliar->valor <<", ";
            auxiliar = auxiliar->siguiente;
        }
        std::cout<<std::endl;
    }
};

int main() {
    Pila pila1;
    pila1.push(10);
    pila1.push(11);
    pila1.push(12);
    pila1.push(13);
    pila1.push(14);
    pila1.push(15);
    pila1.push(16);

    pila1.imprimir();

    return 0;
}