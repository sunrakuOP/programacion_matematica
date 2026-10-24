#include <iostream>

struct NodoLista {
    int valor; 
    NodoLista* anterior;
};

// 1er elemento creado (ultimo de atras para adelante) es nullptr para tener como un caso final
NodoLista* cabeza = nullptr;

// 1ero solo Insertar al frente, nunca toco nada nuevo, solo agrego al final
void agregarAlFrente(int valor) {
    NodoLista* nuevo = new NodoLista{valor, cabeza};  
    cabeza = nuevo;
}

// ahora creo otro que de a nullptr para simular una cola, es decir el primero creado
NodoLista* cola = nullptr;

void agregarAtras(int valor) {
    NodoLista* nuevo = new NodoLista{valor, nullptr}; // lo instancio a nullptr para que sea la nueva cola (nuevo primer elemento)
    if(cabeza == nullptr) {
        cabeza = nuevo; // ahora nuevo es el primer elemento es a la vez cabeza y cola
        cola = nuevo;
    } else {
        cola->anterior = nuevo; // modifica el existente
        cola = nuevo;
    }
}

// como se hace el borrar la memoria
void liberar() {
    NodoLista* actual = cabeza; // empezamos en el ultimo elemento creado 
    while(actual != nullptr) {
        NodoLista* anteriorGuardado = actual->anterior;
        delete actual;
        actual = anteriorGuardado;
    }
    cabeza = nullptr;
    cola = nullptr;
}




int main() {

    return 0;
}