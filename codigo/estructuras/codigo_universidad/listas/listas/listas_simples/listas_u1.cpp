#include <iostream>

/* LISTAS ENLAZADAS 

Array es bloque conntiguo de memoria, es decir se reserva previamente el tamano
    Array agrega elementos al FINAL, va creciendo -------> 

1. Pero insertar o borrar (en el medio) requiere recorrer todo el arreglo comparando O(n)
2. Si el arreglo se queda sin espacio, no hay forma de estirarlo en el mismo lugar de memoria

LISTA ENLAZADA
RENUNCIA AL ACCESO POR INDICE (NO SABE CUANTOS ELEMENTOS HAY)
    Solo tiene el valor (del puntero) del elemento siguiente 

    Hace que insertar (si tengo el puntero al lugar) sea O(1)

*/

struct Nodo {
    int valor;
    Nodo* siguiente;
};

Nodo* cabeza = nullptr;

Nodo* insertarAlInicio(Nodo* cabeza, int valor) {
    Nodo* nuevo = new Nodo{valor,cabeza}; // nuevo apunta a lo que hoy es la cabeza
    cabeza = nuevo;
    return cabeza;
}

void imprimir(Nodo* cabeza) {
    Nodo* auxiliar = cabeza; // cabeza apunta al primer nodo lógico de la lista
    while(auxiliar != nullptr) {
        std::cout<<"Valor: "<<auxiliar->valor<<std::endl; // muestra el valor actual
        auxiliar = auxiliar->siguiente; // ahora pasa al siguiente para ir moviendose
    }
}

/* INSERTAR AL FINAL (HAY 2 VERSIONES)

El nodo nuevo se va a volver el ultimo de la lista (el que apunta a null)
Lo que cambia entre versiones es como encuentro al ultimo nodo

VERSION 1: IMPLEMENTAR SIN COLA
    Reuso el patron de imprimir, usando el while hasta llegar al nullptr
    Auxiliar que arranca en cabeza y recorre hasta el final, cuando llega alla cambio, el ultimo actual apunta al nuevo y el nuevo a null
*/

Nodo* agregarAtrasLineal(Nodo* cabeza, int valor) {
    if(cabeza == nullptr) {
        return nullptr; // la lista esta vacia
    }
    Nodo* auxiliar = cabeza; // nodo que arranca en el primer elemento (ultimo actual)
    while(auxiliar->siguiente != nullptr) {
        auxiliar = auxiliar->siguiente;
    }
    Nodo* nuevo = new Nodo{valor, nullptr};
    auxiliar->siguiente = nuevo;  // reasignamos a que apunta el anterior null
    return cabeza; // la cabeza no cambia al insertar al final (excepto lista vacia)
}

// agregar atras de forma O(1), sin usar el while para recorrer

Nodo* cola = nullptr;

Nodo* agregarAtrasDirecta(Nodo* cabeza, int valor) {
    Nodo* nuevo = new Nodo{valor, nullptr}; // nuevo es el nuevo ultimo: siempre apunta a null
    if (cabeza == nullptr) {
        cabeza = nuevo; // con un solo elemento, es cabeza Y cola a la vez
        cola = nuevo;
    } else {
        cola->siguiente = nuevo; // el viejo ultimo se conecta al nuevo
        cola = nuevo;             // cola avanza al nuevo ultimo
    }
    return cabeza;
}

int main() {
    // al crear valores solo reasigno cabeza (es el que se mueve)
    cabeza = insertarAlInicio(cabeza, 8);
    cabeza = insertarAlInicio(cabeza, 3);
    cabeza = insertarAlInicio(cabeza, 12);

    imprimir(cabeza);

    std::cout << "--- despues de agregarAtras(20) ---" << std::endl;
    cabeza = agregarAtrasLineal(cabeza, 20);
    imprimir(cabeza);

    std::cout << "--- prueba agregarAtrasDirecta en lista vacia ---" << std::endl;
    Nodo* pruebaCabeza = nullptr;
    pruebaCabeza = agregarAtrasDirecta(pruebaCabeza, 99);
    pruebaCabeza = agregarAtrasDirecta(pruebaCabeza, 100);
    imprimir(pruebaCabeza);

    return 0;
}





