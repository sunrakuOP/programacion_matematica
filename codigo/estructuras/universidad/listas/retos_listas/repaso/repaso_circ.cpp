#include <iostream>

/* Retos que propone claude para mejorar en listar circulares

Como hace rato no la usamos aca repasamos 
*/

class NodoSimple {
public:
    int valor;
    NodoSimple* siguiente;

    NodoSimple(int v, NodoSimple* s): valor(v), siguiente(s) {} 
};


class ListaCircular {
private:
    NodoSimple* cabeza;
public:
    ListaCircular(): cabeza(nullptr) {}

    ~ListaCircular() {
        NodoSimple* auxiliar = cabeza;

        do {
            if(auxiliar == nullptr) {
                return;
            }
            NodoSimple* siguienteReal = auxiliar->siguiente;
            delete auxiliar;
            auxiliar = siguienteReal;
        } while(auxiliar != cabeza);
    }

    void agregarInicio(int valor) {
        if(cabeza == nullptr) {
            NodoSimple* nuevo = new NodoSimple(valor, nullptr);
            cabeza = nuevo;
            nuevo->siguiente = cabeza;
            return;
        }

        NodoSimple* auxiliar = cabeza;

        do {
            if(auxiliar->siguiente == cabeza) {
                NodoSimple* nuevo = new NodoSimple(valor, cabeza);
                auxiliar->siguiente = nuevo;
                cabeza = nuevo;
                return;
            } else {
                auxiliar = auxiliar->siguiente;
            }
        } while(auxiliar != cabeza);
        
    }

    void agregarFinal(int valor) {
        // si es primer elemento en una lista vacia 
        if(cabeza == nullptr) {
            NodoSimple* nuevo = new NodoSimple(valor, nullptr);
            cabeza = nuevo;
            nuevo->siguiente = cabeza;
            return;
        }

        // si ya hay elementos, recorrer hasta llegar a cabeza otra vez 
        NodoSimple* auxiliar = cabeza;
        
        do {
            if(auxiliar->siguiente == cabeza) {
                NodoSimple* nuevo = new NodoSimple(valor, cabeza);
                auxiliar->siguiente = nuevo;
                return;
            } else {
                auxiliar = auxiliar->siguiente;
            }
        } while(auxiliar != cabeza);
    }

    void agregarMedioIndice(int valor, int indice) {
        if(indice < 0) return;
        if(indice == 0 && cabeza == nullptr) {
            // agregar primer elemento
            NodoSimple* nuevo = new NodoSimple(valor, nullptr);
            cabeza = nuevo;
            nuevo->siguiente = cabeza;
            return;
        } else if(cabeza == nullptr && indice != 0)  {
            // is vacia y diferente de 0, no valido
            return;
        } else if(indice == 0 && cabeza != nullptr) {
            // reasignar la cabeza (AGREGAR AL INICIO)
            NodoSimple* auxiliar = cabeza;
            do {
                if(auxiliar->siguiente == cabeza) {
                    NodoSimple* nuevo = new NodoSimple(valor, cabeza);
                    auxiliar->siguiente = nuevo;
                    cabeza = nuevo;
                    return;
                } else {
                    auxiliar = auxiliar->siguiente;
                } 
            } while(auxiliar != cabeza);
            
        } else {
            NodoSimple* auxiliar = cabeza;
            int cuenta = 0;
            do {
                if(cuenta == indice - 1) {
                    if(auxiliar->siguiente == cabeza) {
                        // reasignar la cola
                        NodoSimple* nuevo = new NodoSimple(valor, cabeza);
                        auxiliar->siguiente = nuevo;
                        return;
                    } else {
                        // caso cualquiera (en medio)
                        NodoSimple* siguienteNodo = auxiliar->siguiente;
                        NodoSimple* nuevo = new NodoSimple(valor, siguienteNodo);
                        auxiliar->siguiente = nuevo;
                        return;
                    }
                } else {
                    auxiliar = auxiliar->siguiente;
                    cuenta++;
                }
            } while(auxiliar != cabeza);
            // si sale y nunca encontro el indice, se paso 
            return;
        }
    }


    // agregar lista circular ordenada 
    void agregarOrdenada(int valor) {
        if(cabeza == nullptr) {
            NodoSimple* nuevo = new NodoSimple(valor, nullptr);
            cabeza = nuevo;
            nuevo->siguiente = cabeza;
            return;
        } 

        if(valor < cabeza->valor) {
            // es menor que todos: pasa a ser la nueva cabeza
            agregarInicio(valor);
            return;
        }

        NodoSimple* auxiliar = cabeza;

        do {
            NodoSimple* siguienteNodo = auxiliar->siguiente;
            if(siguienteNodo->valor > valor) {
                NodoSimple* nuevo = new NodoSimple(valor, siguienteNodo);
                auxiliar->siguiente = nuevo;
                return;
            } else {
                auxiliar = siguienteNodo;
            }

        } while(auxiliar != cabeza);

        // el ciclo dio toda la vuelta sin encontrar un lugar: es mayor o igual que todos
        agregarFinal(valor);
        
    }


    void imprimir() {
        NodoSimple* auxiliar = cabeza;

        do {
            if(cabeza == nullptr) {
                return;
            }
            std::cout<< auxiliar->valor <<", ";
            auxiliar = auxiliar->siguiente;
        } while(auxiliar != cabeza);
    }


};


int main() {

    return 0;
}