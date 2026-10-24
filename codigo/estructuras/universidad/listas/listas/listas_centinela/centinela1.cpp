#include <iostream>

/*  LISTAS CON CENTINELA
Es un nodo que siempre existe asi la lista este vacia
Se usa para eliminar todas las restricciones que hay que chequear, si la lista esta vacia, si es primer elemento etc..

Centinela existe SOLO PARA ELIMINAR LOS CASOS ESPECIALES
Cual es la idea ??

En vez de que CABEZA / COLA sean nodos reales, son nodos ficticios, que apuntan al 1er y ulimo elemento

Igual es una rama de listas dobles, enlazan los nodos con su siguiente/anterior
*/

class NodoDoble {
public:
    int valor;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(int v, NodoDoble* s, NodoDoble* a): valor(v), siguiente(s), anterior(a) {}
};

class ListaCentinela {
private:
    NodoDoble* cabezaCentinela;
    NodoDoble* colaCentinela;
    
public:
    // inicializamos con valores de 0
    ListaCentinela():
        cabezaCentinela(new NodoDoble(0, nullptr, nullptr)), colaCentinela(new NodoDoble(0, nullptr, nullptr)) {
            cabezaCentinela->siguiente = colaCentinela;
            colaCentinela->anterior = cabezaCentinela;
        }
    
    ~ListaCentinela() {
        NodoDoble* auxiliar = cabezaCentinela;

        while(auxiliar != colaCentinela) {
            NodoDoble* siguienteNodo = auxiliar->siguiente;
            delete auxiliar;
            auxiliar = siguienteNodo;
        }
        delete colaCentinela;
    }

    void insertarAntes(NodoDoble* referencia, int valor) {
        NodoDoble* anteriorNodo = referencia->anterior;

        NodoDoble* nuevo = new NodoDoble(valor, referencia, anteriorNodo);
        referencia->anterior = nuevo;
        anteriorNodo->siguiente = nuevo;
    }

    void insertarDespues(NodoDoble* referencia, int valor){
        // conecetar el nodo nuevo DESPUES de cualquier nodo que le pase de referencia
        NodoDoble* siguienteNodo = referencia->siguiente;

        NodoDoble* nuevo = new NodoDoble(valor, siguienteNodo, referencia);
        siguienteNodo->anterior = nuevo;
        referencia->siguiente = nuevo;
    }

    void insertarInicio(int valor) {
        NodoDoble* siguienteNodo = cabezaCentinela->siguiente;

        NodoDoble* nuevo = new NodoDoble(valor, siguienteNodo, cabezaCentinela);
        siguienteNodo->anterior = nuevo;
        cabezaCentinela->siguiente = nuevo;
    }
};



int main() {

    return 0;
}