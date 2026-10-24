#include <iostream>


struct Nodo {
    int valor; 
    Nodo* siguiente;
};

// crear la interfaz (crear los metodos)


Nodo* insertarAlInicio(int valor, Nodo* cabeza) {
    Nodo* nuevo = new Nodo{valor, cabeza};
    cabeza = nuevo;
    return cabeza;
} 

Nodo* insertarAlFinal(int valor, Nodo* cabeza) {
    if(cabeza == nullptr) {
        Nodo* nuevo = new Nodo{valor, nullptr};
        cabeza = nuevo;
        return cabeza;
    } else {
        Nodo* auxiliar = cabeza;

        while(auxiliar->siguiente != nullptr) {
            auxiliar = auxiliar->siguiente;
        }
        Nodo* nuevo = new Nodo{valor, nullptr};
        auxiliar->siguiente = nuevo;
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

bool existeElElemento(Nodo* cabeza, int valorComparar) {
    if(cabeza == nullptr) {
        // la lista esta vacia
        return false;
    } else {
        Nodo* auxiliar = cabeza;
        while(auxiliar != nullptr) {
            if(auxiliar->valor == valorComparar) {
                return true;
            } else {
                auxiliar = auxiliar->siguiente;
            }
        }
        // salio de la funcion y no lo encontro
        return false;

    }
}

void imprimirLista(Nodo* cabeza) {
    if(cabeza == nullptr) {
        std::cout<<"La lista esta vacia, nada que mostrar"<<std::endl;
        return;
    } else {
        Nodo* auxiliar = cabeza;

        while(auxiliar != nullptr) {
            std::cout<< auxiliar->valor <<std::endl;
            auxiliar = auxiliar->siguiente;
        }
    }

}

Nodo* ejercicio1(Nodo* cabeza, int valor) {
    if(valor >= 500) {
        cabeza = insertarAlFinal(valor, cabeza);
        return cabeza;
        
    } else {
        cabeza = insertarAlInicio(valor, cabeza);
        return cabeza;
    }
}

Nodo* insertarLadoLado(int valor, Nodo* cabeza) {
    if(cabeza == nullptr) {
        Nodo* nuevo = new Nodo{valor, nullptr};
        cabeza = nuevo;
        return cabeza;
    } else {
        Nodo* auxiliar = cabeza;

        while(auxiliar != nullptr) {
            if(auxiliar->valor == valor) {
                Nodo* nuevo = new Nodo{valor, auxiliar->siguiente};
                auxiliar->siguiente = nuevo;
                return cabeza;
            } 
            auxiliar = auxiliar->siguiente;
        }
        // significa que no lo encontro 
        cabeza = insertarAlInicio(valor, cabeza);
        return cabeza;
    }
}

int main() {
    



    return 0;
}