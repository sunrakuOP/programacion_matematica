#include <iostream>

/*  Ya hicimos el agregar al final, atras y eliminar

Ahora vamos a hacer la agregar atras usando una COLA para que la complejidad Sea directa O(1)
*/

struct Nodo {
    int valor;
    Nodo* siguiente;
};

Nodo* cola = nullptr;

Nodo* agregarAtrasConCola(int valor, Nodo* cabeza) {
    // la lista esta vacia 
    if(cabeza == nullptr) {
        Nodo* nuevo = new Nodo{valor, nullptr};
        nuevo->siguiente = nuevo; // se apunta a si mismo
        cabeza = nuevo;
        cola = nuevo;
        return cabeza;
    }
    // si ya hay uno o mas elementos
    Nodo* nuevo = new Nodo{valor, cabeza}; // nace apuntando a cabeza 
    cola->siguiente = nuevo;
    cola = nuevo;
    return cabeza;
}


void imprimirCircular(Nodo* cabeza, int maxVueltas) {
    if (cabeza == nullptr) { std::cout << "(vacia)" << std::endl; return; }
    Nodo* aux = cabeza;
    int i = 0;
    do {
        std::cout << "Valor: " << aux->valor << std::endl;
        aux = aux->siguiente;
        i++;
    } while (aux != cabeza && i < maxVueltas);
}

int main() {
    Nodo* cabeza = nullptr;
    cabeza = agregarAtrasConCola(8, cabeza);
    cabeza = agregarAtrasConCola(3, cabeza);
    cabeza = agregarAtrasConCola(20, cabeza);

    std::cout << "--- deberia ser 8, 3, 20 ---" << std::endl;
    imprimirCircular(cabeza, 5);

    return 0;
}