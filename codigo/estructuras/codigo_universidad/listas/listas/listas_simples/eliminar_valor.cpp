#include <iostream>

struct Nodo {
    int valor; 
    Nodo* siguiente; 
};

Nodo* cabeza = nullptr;

Nodo* agregarAlFrente(int valor, Nodo* cabeza) {
    Nodo* nuevo = new Nodo{valor, cabeza}; // nuevo nodo va a apuntar a cabeza (anterior elemento creado)
    cabeza = nuevo; // ahora cabeza apunta a nuevo, se reasigna
    return cabeza;
}

// agregar atras O(n): TOCA RECORRER TODA LA LISTA
Nodo* agregarAtrasLineal(int valor, Nodo* cabeza) {
    if(cabeza == nullptr) {
        return cabeza;
    }
    // necesito usar un auxiliar para no mover cabeza
    Nodo* auxiliar = cabeza;
    while(auxiliar->siguiente != nullptr) { // para no llegar hasta el final
        auxiliar = auxiliar->siguiente;
    }
    Nodo* nuevo = new Nodo{valor, nullptr};
    auxiliar->siguiente = nuevo; // el anterior ultimo valor ahora apunta al nuevo ultimo, y ese apunta a null
    return cabeza;
}

// agregar atras pero O(1): FORMA MAS DIRECTA Y EFICIENTE
Nodo* cola = nullptr;

Nodo* agregarAtrasDirecto(int valor, Nodo* cabeza) {
    // si la lista esta vacia, nuevo es cabeza y cola al tiempo
    Nodo* nuevo = new Nodo{valor, nullptr}; // se crea apuntando a null
    if(cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo; 
        return cabeza; 
    } else { 
        // si la lista no esta vacia (contiene elementos)
        cola->siguiente = nuevo; // el anterior apunta ahora a nuevo (para no perder su direccion)
        cola = nuevo; // ahora cola apunta a nuevo    
        return cabeza;  
    }
}


Nodo* eliminarPorValor(int valorComparar, Nodo* cabeza) {
    if(cabeza == nullptr) {
       return cabeza;
    }

    Nodo* anterior = nullptr; // antes de cabeza no hay nada
    Nodo* auxiliar = cabeza;
    
    while(auxiliar != nullptr) {
        Nodo* siguienteReal = auxiliar->siguiente; // creo el nodo que apunta al siguiente valor

        if(auxiliar->valor == valorComparar) {
            if(anterior == nullptr) {
                // estoy borrando la cabeza 
                cabeza = cabeza->siguiente; // no se si podria hacerlo con siguiente real, ya que auxiliar vendria siendo cabeza en este caso 
                delete auxiliar;
            } else {
                anterior->siguiente = auxiliar->siguiente;
                delete auxiliar;
            }
        } else {
            anterior = auxiliar; // hace avanzar a auxiliar si no borra
        }
        auxiliar = siguienteReal; // siempre avanzo con el valor guardado, no con -> 
    }
    return cabeza;
}


int main() {
    // insertando 8,20,8,3,8 al frente queda: 8,3,8,20,8
    cabeza = agregarAlFrente(8, cabeza);
    cabeza = agregarAlFrente(20, cabeza);
    cabeza = agregarAlFrente(8, cabeza);
    cabeza = agregarAlFrente(3, cabeza);
    cabeza = agregarAlFrente(8, cabeza);

    std::cout << "--- antes de eliminar ---" << std::endl;
    for (Nodo* aux = cabeza; aux != nullptr; aux = aux->siguiente) {
        std::cout << "Valor: " << aux->valor << std::endl;
    }

    cabeza = eliminarPorValor(8, cabeza);

    std::cout << "--- despues de eliminar 8 ---" << std::endl;
    for (Nodo* aux = cabeza; aux != nullptr; aux = aux->siguiente) {
        std::cout << "Valor: " << aux->valor << std::endl;
    }

    return 0;
}