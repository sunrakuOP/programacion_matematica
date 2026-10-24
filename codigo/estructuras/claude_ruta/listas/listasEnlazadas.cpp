#include <iostream>

/* LISTAS ENLAZADAS

En vez de un array plano se usan diferentes listas separadas, que sabe donde esta cada una 
Se hace mediante un puntero a un primer elemento

Por que necesita puntero?????
    Para manejar direcciones de memoria y conocer donde se encuentra el siguiente elemento

Para que sirve??
    No se usa mucho realmente, vector se usa mucho mas 
    HAY 2 CASOS PUNTUALES DONDE SI O SI GANA A TODO LO DEMAS:
    
    1. Insertar/borrar en el medio o al frente en una coleccion grande
        En un vector, insertar al frente corre todos los elementos una posicion.... O(n)
        En una lista enlazada, si ya tengo el puntero, insertar es solo reconectar 2 punteros.... O(1)

    2. Cuando un vector se queda sin capacidad y tiene que crecer, mueve todos sus elementos a un bloque de memoria nuevo
        Cualquier puntero queda apuntando a memoria vieja. 
        
        Una lista enlazada nunca mueve un nodo ya creado
*/

// nodo plano
struct NodoPlano {
    double x, y, z; // objeto que relaciona 3 datos 
};

struct NodoLista {
    int valor;
    NodoLista* siguiente; 
};

NodoLista* cabeza = nullptr; // arranca vacia
NodoLista* cola = nullptr; 

void insertarAlFrente(int valor) {
    NodoLista* nuevo = new NodoLista{valor, cabeza};
    cabeza = nuevo;
}

void insertarAlFinal(int valor) {
    NodoLista* nuevo = new NodoLista{valor, nullptr}; // es como insertar al primer elemento pero como va al reves pues se invierte
    if(cabeza == nullptr) { // es decir que la lista esta vacia, porque cabeza es el ultimo elemento creado
        cabeza = nuevo; 
    } else { // significa que la lista si contiene elementos 
        cola = nuevo;
    }
}

void imprimir(NodoLista* cabeza) { // imprimir el valor del elemento 
    NodoLista* actual = cabeza;
    while(actual != nullptr) {
        std::cout<<"Actual: "<< actual->valor <<std::endl;
        actual = actual->siguiente;
    }
}

int main() {
    NodoPlano a;
    NodoPlano* ptr; // es la direccion a memoria del Nodo, no el valor como tal 
    // ventaja: Puntero siempre pesa lo mismo, sin importar lo que contenga




    return 0;
}