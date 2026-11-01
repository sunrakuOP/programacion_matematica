#include <iostream>

/* LIFO: Ultimo en entrar, primero en salir 

El ultimo valor que entra es el primero que sale (como una pila de platos, se desocupan desde arriba)
    Nunca se pueden sacar valores de al fondo o medio (primero toca sacar todo lo de arriba)

OPERACIONES:
    push(x) => Agrega el elemento arriba de 
    pop() => Eliminar el primer elemento (el de arriba)

Se usa en el callstack.
    Lo usa mi programa cada vez que una funcion llama a otra por debajo

Ej: Funciones que llaman a otras funciones 

void funcionC() { std::cout << "entrando a C\n"; std::cout << "saliendo de C\n"; }
void funcionB() { std::cout << "entrando a B\n"; funcionC(); std::cout << "saliendo de B\n"; }
void funcionA() { std::cout << "entrando a A\n"; funcionB(); std::cout << "saliendo de A\n"; }
int main() { funcionA(); }

entrando a A
 entrando a B
  entrando a C
  saliendo de C
 saliendo de B
saliendo de A


CHEQUEAR QUE PILA NO ESTE VACIA ANTES DE HACER .pop()
Usar el .empty() antes de hacer .pop()

pila.top() => Muestra el primer elemento (el de arriba de la pila)
*/

struct NodoLista {
    int valor;
    NodoLista* siguiente;
};

struct Pila {
    NodoLista* tope = nullptr;

    void push(int valor) {
        // crear un nuevo NodoLista 
        NodoLista* nuevo = new NodoLista{valor, tope};
        tope = nuevo;
    }

    void pop() {
        if(tope == nullptr) {
            throw std::out_of_range("pop sobre fila vacia");
        }
        int valorSacado = tope->valor;
        NodoLista* siguienteGuardado = tope->siguiente;
        delete tope;
        tope = siguienteGuardado;
    }

    bool estaVacia() {
        if(tope == nullptr) {
            return true;
        } 
        return false;
    }

};

int main() {
    std::stack<int> pila;
    // si hago pila.pop() con el stack vacio hay error , usar .empty() para chequear
    pila.push(10);
    pila.push(20);
    pila.push(30);
    
    /* PILA NO SE PUEDE RECORRER CON FOR IN RANGE
    for(const auto& e: pila) {
        std::cout<< e <<std::endl;
        pila.pop();
    }
    */

    while(!pila.empty()){
        std::cout<<pila.top() <<std::endl;
        pila.pop();
    }

    // en la muestra de la terminal, el primer elemento sale, y sigue hasta abajo
    /*
    30
    20
    10
        Orden inverso 
    */

    return 0;
}