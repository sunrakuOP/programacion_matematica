#include <iostream>

/* LISTAS DOBLEMENTE ENLZADAS

Ya vimos listas simples y circulares, solo se puede avanzar en una direccion (cada nodo solo conoce a su anterior)
Antes para eliminar un nodo necesitaba el puntero anterior.

SIMPLES:
Se necesitaba guardar el puntero "anterior" para borrar un nodo. Ademas de recorrer la lista asi tenga el puntero a la mano.

DOBLES:
Tiene nodo de referencia ANTERIOR y SIGUIENTE
Costo: Memoria extra. (1 puntero mas de referencia)



*/

class NodoDoble {
public: 
    int valor;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    // 3 parametros de constructor
    NodoDoble(int v, NodoDoble* s = nullptr, NodoDoble* a = nullptr): valor(v), siguiente(s), anterior(a) {}
};

class ListasDobles {
private:
    NodoDoble* cabeza;
    NodoDoble* cola;
public:
    ListasDobles(): cabeza(nullptr), cola(nullptr) {}

    void agregarInicio(int valor) {
        if(cabeza == nullptr) {
            NodoDoble* nuevo = new NodoDoble(valor, cabeza, cola);
            cabeza = nuevo;
            cola = nuevo;
            return;
        }

        NodoDoble* nuevo = new NodoDoble(valor, cabeza, nullptr);
        cabeza->anterior = nuevo; // ya no es null
        cabeza = nuevo;
    }

    void agregarFinal(int valor) {
        if(cabeza == nullptr) {
            NodoDoble* nuevo = new NodoDoble(valor, cabeza, cola);
            cabeza = nuevo;
            cola = nuevo;
            return;
        }

        NodoDoble* nuevo = new NodoDoble(valor, nullptr, cola);
        cola->siguiente = nuevo;
        cola = nuevo;
    }

    void agregarMedioIndice(int indice, int valor) {
        if(indice == 0 && cabeza == nullptr) {
            // agregar un primer elemento
            NodoDoble* nuevo = new NodoDoble(valor, cabeza, cola);
            cabeza = nuevo;
            cola = nuevo;
            return;
        }
        if(indice == 0 && cabeza != nullptr) {
            // reasignar cabeza
            NodoDoble* nuevo = new NodoDoble(valor, cabeza, nullptr);
            cabeza->anterior = nuevo;
            cabeza = nuevo;
            return;
        }

        NodoDoble* auxiliar = cabeza;
        int cuenta = 0;

        while(cuenta < indice - 1) {
            if(auxiliar == cola) {
                // llego al final y aun no llega al indice del nodo
                return;
            }
            auxiliar = auxiliar->siguiente;
            cuenta++;
        }

        if(auxiliar == cola) {
            NodoDoble* nuevo = new NodoDoble(valor, nullptr, cola);
            cola->siguiente = nuevo;
            cola = nuevo;
            return;
        }
        NodoDoble* siguienteNodo = auxiliar->siguiente;
        NodoDoble* nuevo = new NodoDoble(valor, siguienteNodo, auxiliar);
        auxiliar->siguiente = nuevo;
        siguienteNodo->anterior = nuevo;
    }


    // ahora insertar en el medio pero por valor
    void insertarMedioValor(int valor, int valorBuscar) {
        if(cabeza == nullptr) {
            return; // no hay elementos para comparar 
        }

        NodoDoble* auxiliar = cabeza;

        while(auxiliar != nullptr) {
            if(auxiliar->valor == valorBuscar) {
                if(cabeza == cola) {
                    // significa que solo hay un elemento
                    NodoDoble* nuevo = new NodoDoble(valor, nullptr, cabeza);
                    cabeza->siguiente = nuevo;
                    cola = nuevo;
                    return;
                } else if(auxiliar == cabeza) {
                    NodoDoble* segundo = cabeza->siguiente;
                    NodoDoble* nuevo = new NodoDoble(valor, segundo, cabeza);
                    segundo->anterior = nuevo;
                    cabeza->siguiente = nuevo;
                    return;
                } else if(auxiliar == cola) {
                    NodoDoble* nuevo = new NodoDoble(valor, nullptr, cola);
                    cola->siguiente = nuevo;
                    cola = nuevo;
                    return;
                } else {
                    NodoDoble* siguienteNodo = auxiliar->siguiente;
                    NodoDoble* nuevo = new NodoDoble(valor, siguienteNodo, auxiliar);
                    auxiliar->siguiente = nuevo;
                    siguienteNodo->anterior = nuevo;
                    return;
                }

            } else {
                auxiliar = auxiliar->siguiente;
            }
        }
        // si llego aca es que termino la lista y no encontro el valor buscado
        return;
    }


    void eliminarPorValor(int valorEliminar) {
        if(cabeza == nullptr) {
            return;
        }

        NodoDoble* auxiliar = cabeza;

        while(auxiliar != nullptr) {
            NodoDoble* siguienteNodo = auxiliar->siguiente;
            if(auxiliar->valor == valorEliminar) {
                if(cabeza == cola) {
                    // solo hay un elemento
                    cabeza = nullptr;
                    cola = nullptr;
                } else if(auxiliar == cabeza) {
                    siguienteNodo->anterior = nullptr;
                    cabeza = siguienteNodo;
                } else if(auxiliar == cola) {
                    NodoDoble* anterior = auxiliar->anterior;
                    anterior->siguiente = nullptr;
                    cola = anterior;
                } else {
                    NodoDoble* anterior = auxiliar->anterior;
                    anterior->siguiente = siguienteNodo;
                    siguienteNodo->anterior = anterior;
                }
                delete auxiliar;
            } 
            auxiliar = siguienteNodo;
        }
        // si salio y no encontro el elemento a eliminar 
        return;
    }
};



int main() {

    return 0;
}