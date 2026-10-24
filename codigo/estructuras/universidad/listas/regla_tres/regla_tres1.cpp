#include <iostream>

/* HASTA AHORA VENIMOS COPIANDO NODOS 

Pila a;
Pila b = a;

Ahi lo unico que hago es copiar a.cabeza en b, solo copio las direcciones de memoria. 

Solucion: COPIAR TODOS LOS NODOS
Copiar en B todos los valores y direcciones de cada nodo, SUS PROPIOS NODOS

Se hace con el constructor de copia

Pila(const Pila& otra)
!!!!!!  Recorre cada elemento de lista y lo agrega a la nueva

*/

class NodoSimple {
public: 
    int valor;
    NodoSimple* siguiente;

    NodoSimple(int v, NodoSimple* s): valor(v), siguiente(s) {}
};

class Pila {
private:
    NodoSimple* cabeza;
public:
    Pila(): cabeza(nullptr) {}

    ~Pila() {
        NodoSimple* auxiliar = cabeza;

        while(auxiliar != nullptr) {
            NodoSimple* siguienteNodo = auxiliar->siguiente;
            delete auxiliar;
            auxiliar = siguienteNodo;
        }
    }

    Pila& operator=(const Pila& otra) {
        if(cabeza == nullptr && otra.cabeza == nullptr) {
            return *this;
        } else if(otra.cabeza == cabeza) {
            return *this;
        } else {
            eliminarTodo();

            NodoSimple* auxiliar = otra.cabeza;
            NodoSimple* pivote = cabeza;

            while(auxiliar != nullptr) {
                NodoSimple* nuevo = new NodoSimple(auxiliar->valor, nullptr);
                if(cabeza == nullptr) {
                    // no hay cabeza para enganchar
                    cabeza = nuevo;
                    pivote = nuevo;
                    
                    auxiliar = auxiliar->siguiente;
                } else {
                    pivote->siguiente = nuevo;
                    pivote = nuevo;

                    auxiliar = auxiliar->siguiente;
                }
            }
            return *this;

        }
    
    }

    void agregarInicio(int valor) {
        NodoSimple* nuevo = new NodoSimple(valor, cabeza);
        cabeza = nuevo;
    }

    Pila(const Pila& otra): cabeza(nullptr) {
        if(otra.cabeza == nullptr) {
            return;
        } 

        NodoSimple* auxiliar = otra.cabeza;
        NodoSimple* pivote = cabeza;

        while(auxiliar != nullptr) {
            NodoSimple* nuevo = new NodoSimple(auxiliar->valor, nullptr);
            if(cabeza == nullptr) {
                // no hay cabeza para enganchar
                cabeza = nuevo;
                pivote = nuevo;
                
                auxiliar = auxiliar->siguiente;
            } else {
                pivote->siguiente = nuevo;
                pivote = nuevo;

                auxiliar = auxiliar->siguiente;
            }
        }

    }

    void imprimir() {
        NodoSimple* auxiliar = cabeza;

        while(auxiliar != nullptr) {
            std::cout<< auxiliar->valor<<",";
            auxiliar = auxiliar->siguiente;
        }
        std::cout<<std::endl;
    }

    void eliminarTodo() {
        NodoSimple* auxiliar = cabeza;
        
        while(auxiliar != nullptr) {
            NodoSimple* siguienteNodo = auxiliar->siguiente;
            delete auxiliar;

            auxiliar = siguienteNodo;
        }
        cabeza = nullptr;
    }
}; 

int main() {
    
    return 0;
}