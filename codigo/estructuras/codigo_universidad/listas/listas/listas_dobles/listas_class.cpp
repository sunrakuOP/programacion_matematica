#include <iostream>

/* REPASO DE LISTAS SIMPLES

Hagamos ejercicio para mostrarlo
*/

class Nodo {
public:
    int valor;
    Nodo* siguiente;

    // usando el constructor dentro de la clase 
    Nodo(int valor, Nodo* siguiente = nullptr): valor(valor), siguiente(siguiente) {}
};


class ListaSimple {
private:
    Nodo* cabeza; // el nodo es privado y va compuesto
    Nodo* cola;
public:
    ListaSimple(): cabeza(nullptr), cola(nullptr) {} // se incializa apuntando a null 

    // aca digito los metodos que voy a implementar

    bool estaVacia() const {
        if(cabeza == nullptr) {
            return true;
        }
        return false;
    }

    Nodo* agregarInicio(int valor) {
        Nodo* nuevo = new Nodo(valor, cabeza); // nuevo nace apuntando a cabeza
        cabeza = nuevo; 
        // por si la lista estaba vacia
        if(cola == nullptr) {
            cola = nuevo;
        }
        return cabeza;
    }

    Nodo* agregarFinal(int valor) {
        if(cabeza == nullptr) { // lista vacia, agrega comun y corriente
            Nodo* nuevo = new Nodo(valor, cabeza);
            cabeza = nuevo;
            cola = nuevo;
            return cabeza;
        }

        Nodo* auxiliar = cabeza;
        while(auxiliar->siguiente != nullptr) {
            auxiliar = auxiliar->siguiente;
        }
        
        Nodo* nuevo = new Nodo(valor, auxiliar->siguiente); // o tambien se podria hacer con nullptr creo yo
        auxiliar->siguiente = nuevo;
        cola = nuevo;
        return cabeza;
    }

    // tambien se puede agregar directamente atras, si hacemos una cola que apunte a null
    Nodo* agregarFinalDirecto(int valor) {
        if(cabeza == nullptr) {
            Nodo* nuevo = new Nodo(valor, cabeza);
            // cabeza y cola al mismo tiempo
            cabeza = nuevo;
            cola = nuevo;
            return cabeza;
        }

        Nodo* nuevo = new Nodo(valor, nullptr);
        cola->siguiente = nuevo;
        cola = nuevo;
        return cabeza;
    }

    Nodo* insertarMedioIndice(int valor, int indice) {
        if(indice < 0) {
            return cabeza;
        }

        if(indice == 0 && cabeza == nullptr) {
            // es decir que es el primer elemento en una lista vacia 
            Nodo* nuevo = new Nodo(valor,cabeza);
            cabeza = nuevo;
            cola = nuevo;
            return cabeza;
        }
        if(indice == 0 && cabeza != nullptr) {
            // cambiar cabeza, en una lista con datos
            Nodo* nuevo = new Nodo(valor, cabeza);
            cabeza = nuevo;
            return cabeza;
        }

        Nodo* auxiliar = cabeza;
        int cuenta = 0;

        while(cuenta < indice - 1) {
            auxiliar = auxiliar->siguiente;
            cuenta++;
            if(auxiliar == nullptr) {
                return cabeza;
            }
        }
        Nodo* nuevo = new Nodo(valor, auxiliar->siguiente);
        auxiliar->siguiente = nuevo;
        if(auxiliar == cola) {
            cola = nuevo;
        }
        return cabeza;
    }


    /*
    Nodo* eliminarPorValor(int valorEliminar) {
        if(cabeza == nullptr) {
            return cabeza;
        }

        Nodo* auxiliar = cabeza;
        Nodo* anterior = nullptr;

        while(auxiliar->valor != valorEliminar) {
            anterior = auxiliar;
            auxiliar = auxiliar->siguiente;
            if(auxiliar == nullptr) {
                // llego al final y no lo encontro
                return cabeza;
            }
        }

        Nodo* siguiente = auxiliar->siguiente;
        if(auxiliar == cola) {
            anterior->siguiente = nullptr;
            delete auxiliar;
            cola = anterior;
            return cabeza;
        } else if(auxiliar == cabeza) {
            cabeza = auxiliar->siguiente;
            delete auxiliar;
            return cabeza;
        } else {
            anterior->siguiente = siguiente;
            delete auxiliar;
            return cabeza;
        }
    }
    */

    // version 2 haciendolo como lo he hecho ya
    Nodo* eliminarPorValor2(int valorEliminar) {
        if(cabeza == nullptr) {
            return cabeza;
        }

        Nodo* auxiliar = cabeza;
        Nodo* anterior = nullptr;

        while(auxiliar != nullptr) {
            if(auxiliar->valor == valorEliminar) {
                if(auxiliar == cabeza && auxiliar == cola) {
                    // un solo elemento
                    cabeza = nullptr;
                    cola = nullptr;
                    delete auxiliar;
                    return cabeza;
                } else if(auxiliar == cola) {
                    anterior->siguiente = nullptr;
                    delete auxiliar;
                    cola = anterior;
                    return cabeza;
                } else if(auxiliar == cabeza) {
                    cabeza = auxiliar->siguiente;
                    delete auxiliar;
                    return cabeza;
                } else {
                    anterior->siguiente = auxiliar->siguiente;
                    delete auxiliar;
                    return cabeza;
                }
            } else {
                anterior = auxiliar;
                auxiliar = auxiliar->siguiente;
            }
        }
        // salio del ciclo y no lo encontro
        return cabeza;
    }

};



int main() {

    return 0;
}