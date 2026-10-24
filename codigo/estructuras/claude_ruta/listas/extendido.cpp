#include <iostream>

struct NodoLista {
    int valor;
    NodoLista* anterior; // guardo la direccion de memoria del nodo anterior 
};

NodoLista* cabeza = nullptr; // primer elemento va a guardar el valor de null (1ro que se genere)
// hagamos el insertar atras por entender no mas 
NodoLista* cola = nullptr;

void agregarAlFrente(int valor) {    
    NodoLista* nuevo = new NodoLista{valor, cabeza}; // guarda la direccion del ultimo elemento
    if(cabeza == nullptr) { // compronar que no esta vacia 
        cola = nuevo;
    }
    cabeza = nuevo;
}

void agregarAtras(int valor) {
    NodoLista* nuevo = new NodoLista{valor, nullptr}; // debe apuntar a null porque va a reemplazar al primero
    if(cabeza == nullptr) {
        // significa que la lista esta vacia 
        cabeza = nuevo;
        cola = nuevo;
        // ambos, cabeza y cola al tiempo
    } else { // si si hay elementos
        cola->anterior = nuevo; // valor del ultimo apunta ahora a nuevo (null)
        cola = nuevo;  
    }
}

void imprimir(NodoLista* cabeza) { // cabeza es en general el ultimo elemento creado
    NodoLista* actual = cabeza; 
    // toca ir corriendo para atras elemento por elemento
    while(actual != nullptr) {
        std::cout<<"Valor: "<< actual->valor <<std::endl;
        actual = actual->anterior; // devuelvo la direccion de memoria al elemento anterior
    }
} 

void liberar() {
    NodoLista* actual = cabeza;
    while(actual != nullptr) {
        NodoLista* anteriorGuardado = actual->anterior;
        delete actual;
        actual = anteriorGuardado; // reasigno
    }
    // al final dejo cola y cabeza como null. Limpieza completa
    cabeza = nullptr;
    cola = nullptr;
}

int main() {
    agregarAlFrente(9);
    agregarAlFrente(9);
    agregarAlFrente(26);
    agregarAlFrente(58);

    agregarAtras(23);
    imprimir(cabeza);

    liberar();

    return 0;
}