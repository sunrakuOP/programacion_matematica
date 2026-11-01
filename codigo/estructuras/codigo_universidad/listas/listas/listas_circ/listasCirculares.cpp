#include <iostream>

struct Nodo {
    int valor;
    Nodo* siguiente;
};

Nodo* agregarListaCircular(int valor, Nodo* cabeza) {
    if(cabeza == nullptr) {
        Nodo* nuevo = new Nodo{valor, nullptr}; // se apunta a si mismo
        nuevo->siguiente = nuevo; 
        cabeza = nuevo; // cabeza ahora apunta a nodo
        return cabeza;
    }

    Nodo* auxiliar = cabeza;

    do {
        if(auxiliar->siguiente == cabeza) { // ultimo actual
            Nodo* nuevo = new Nodo{valor, cabeza};
            cabeza = nuevo; // cabeza ahora apunta al ultimo elemento
            // hacer que el nodo no se apunte a si mismo
            auxiliar->siguiente = nuevo;
            return cabeza;
        }   
        else {
            auxiliar = auxiliar->siguiente; // para que avance si no es lo que buscamos
        }
    } while(auxiliar != cabeza);

}

// insertar al final de una lista circular, es decir antes del primer elemento
Nodo* agregarFinalListaCircular(int valor, Nodo* cabeza) {
    if(cabeza == nullptr) {
        // significa que la lista esta vacia 
        Nodo* nuevo = new Nodo{valor, nullptr};
        nuevo->siguiente = nuevo;
        cabeza = nuevo;
        return cabeza;
    }

    Nodo* auxiliar = cabeza; // pivote

    do {
        if(auxiliar->siguiente == cabeza) {
            Nodo* nuevo = new Nodo{valor, cabeza};
            auxiliar->siguiente = nuevo;
            return cabeza;
        } else {
            auxiliar = auxiliar->siguiente;
        }

    } while(auxiliar != cabeza);
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

// ahora, eliminar por valor 

Nodo* eliminarPorValo(Nodo* cabeza, int valorEliminar) {
    if(cabeza == nullptr) {
        // pues la lista esta vacia, no hay nada que borrar
        return cabeza;
    }

    // si solo hay un valor, se esta borrando la cabeza
    if((cabeza->valor == valorEliminar) && (cabeza->siguiente == cabeza)) {
        // significa que cabeza se apunta a si misma
        delete cabeza;
        cabeza = nullptr;
        return cabeza; // para cerrar
    }

    // si la cabeza es la que se borra pero hay mas de un nodo
    if(cabeza->valor == valorEliminar) {
        Nodo* ultimo = cabeza;
        while(ultimo->siguiente != cabeza) { // buscar quien cierra el circulo
            ultimo = ultimo->siguiente;
        }
        Nodo* viejo = cabeza;       // guardamos la direccion antes de perderla
        cabeza = cabeza->siguiente; // cabeza avanza al nuevo primero
        ultimo->siguiente = cabeza; // el que cierra se reconecta al nuevo cabeza
        delete viejo;
        return cabeza;
    }

    Nodo* auxiliar = cabeza;
    Nodo* anterior = nullptr;

    do {
        Nodo* siguienteReal = auxiliar->siguiente;
        if(auxiliar->valor == valorEliminar) {
            if(auxiliar->siguiente == cabeza) {
                anterior->siguiente = cabeza;
                delete auxiliar;
                return cabeza;
            } else {
                anterior->siguiente = auxiliar->siguiente;
                delete auxiliar;
                return cabeza;
            }
        } else {
            anterior = auxiliar;
            auxiliar = siguienteReal;
        }
    } while(auxiliar != cabeza);

    // si no encuentra el elemento al terminar de recorrer
    return cabeza;
}


int main() {
    Nodo* cabeza = nullptr;
    cabeza = agregarListaCircular(8, cabeza);
    std::cout << "--- lista con 1 elemento (8) ---" << std::endl;
    imprimirCircular(cabeza, 5);

    cabeza = agregarListaCircular(3, cabeza);
    std::cout << "--- despues de insertar 3 al inicio (deberia ser 3, 8) ---" << std::endl;
    imprimirCircular(cabeza, 5);

    cabeza = agregarFinalListaCircular(20, cabeza);
    std::cout << "--- despues de insertar 20 al final (deberia ser 3, 8, 20) ---" << std::endl;
    imprimirCircular(cabeza, 5);

    std::cout << "--- eliminar el 8 (valor del medio) ---" << std::endl;
    cabeza = eliminarPorValo(cabeza, 8);
    imprimirCircular(cabeza, 5);

    std::cout << "--- eliminar el 3 (valor de la CABEZA, con 2 nodos restantes) ---" << std::endl;
    cabeza = eliminarPorValo(cabeza, 3);
    imprimirCircular(cabeza, 5);

    return 0;
}