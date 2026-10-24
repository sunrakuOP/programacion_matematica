/*
#include <iostream>

struct Nodo {
    int valor;
    Nodo* siguiente;
};

 INVERTIR LA LISTA SIMPLE
si la lista es 5->9->2->null <=> 2->9->5->null

Nodo* cabeza = nullptr;
Nodo* invertir(Nodo* cabeza) {
    if(cabeza == nullptr) {
        return cabeza; //lista vacia
    }

    // usar el auxiliar para recorrer 
    Nodo* auxiliar = cabeza;
    Nodo* anterior = nullptr;

    // aca recorro hasta el primer elemento creado (el que apunta a null)
    while(auxiliar != nullptr) {
        Nodo* siguienteReal = auxiliar->siguiente; 
        
        auxiliar->siguiente = anterior;
        anterior = auxiliar;
        auxiliar = siguienteReal;
    }
    cabeza = anterior;

    return cabeza;
}

INSERTAR EN EL MEDIO POR INDICE EN CIRCULAR 



Nodo* insertarMedioCircularPorIndice(Nodo* cabeza, int valor, int indice) {
    if(cabeza == nullptr && indice != 0) {
        // cabeza vacia
        return cabeza;
    }

    Nodo* auxiliar = cabeza;

    if(cabeza == nullptr && indice == 0) {
        // agregar primer elemento de una lista vacia, crear a null y reconectarlo haciendose apuntar a si mismo
        Nodo* nuevo = new Nodo{valor, nullptr}; // lo creo apuntando a nada
        nuevo->siguiente = nuevo; // se apunta a si mismo
        cabeza = nuevo; // cabeza apunta a nuevo
        return cabeza;

    }  

    if(cabeza != nullptr && indice == 0) {
        Nodo* nuevo = new Nodo{valor, cabeza}; // como va a reemplazar al primero, apunta a cabeza
        // encontrar el elemento que cierra el circulo
        Nodo* cierre = cabeza;

        while(cierre->siguiente != cabeza) {
            // para encontrar el ultimo nodo, no lo voy a actualiza ni nada, me quedo parado en el 
            cierre = cierre->siguiente;
        }
        cierre->siguiente = nuevo;
        cabeza = nuevo;
        return cabeza;
    }
    
    int cuenta = 0;
    do {    
        if(cuenta > indice) {
            // indice es mayor al numero de elementos
            return cabeza;
        }
        if(cuenta == indice) {
            if(cabeza->siguiente == auxiliar) {
                // si el indice es a donde apunta cabeza
                Nodo* nuevo = new Nodo{valor, auxiliar};
                cabeza->siguiente = nuevo;
                return cabeza;
            } else {
                Nodo* nuevo = new Nodo{valor, auxiliar->siguiente};
                auxiliar->siguiente = nuevo;
                return cabeza;
            }
        }
        cuenta++;
        auxiliar = auxiliar->siguiente;
    } while(auxiliar != cabeza);

    return cabeza;
}


Nodo* insertarCircularPorIndiceV2(int valor, Nodo* cabeza, int indice) {
    if(cabeza == nullptr && indice == 0) {
        Nodo* nuevo = new Nodo{valor, nullptr};
        nuevo->siguiente = nuevo;
        cabeza = nuevo;
        return cabeza;
    }
    if(cabeza == nullptr && indice != 0) {
        // no agrega nada porque no hay suficientes elementos
        return cabeza;
    }
    
    Nodo* auxiliar = cabeza;
    Nodo* anterior = nullptr;
    
    if(cabeza != nullptr && indice !=0) {
        // reasignar la cabeza 
        while(auxiliar->siguiente != cabeza) {
            auxiliar = auxiliar->siguiente;
        }
        Nodo* nuevo = new Nodo{valor, cabeza->siguiente};
        auxiliar->siguiente = nuevo;
        cabeza = nuevo;
        return cabeza;
    }

    int cuenta = 0;
    do {    
        if(cuenta < indice) {
            auxiliar = auxiliar->siguiente;
            cuenta++;
            continue;
        } else if(cuenta == indice) {
            Nodo* siguienteReal = auxiliar->siguiente;
            
            Nodo* nuevo = new Nodo{valor, };
            auxiliar->siguiente = nuevo;
            nuevo
        }


    } while(auxiliar != cabeza);
}
int main() {

    return 0;
}
*/