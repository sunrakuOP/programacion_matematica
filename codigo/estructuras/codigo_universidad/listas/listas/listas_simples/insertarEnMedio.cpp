#include <iostream> 

struct Nodo {
    int valor;
    Nodo* siguiente;
};

/* Como hago para insertar en el medio si no se de indices??? 

Hay 2 formas tipicas:
    1. Con indice: Y cuenta mientras recorre, empezando en 0
    2. Por valor de referencia:
        Ejemplo, insertar el nodo creado despues de el valor 100 (por ejemplo)

    Hagamos ambas versiones
*/

Nodo* cabeza = 0;

Nodo* insertarMedioIndice(int valor, Nodo* cabeza, int indice) {
    if(cabeza == nullptr || indice == 0) {
        Nodo* nuevo = new Nodo{valor, cabeza};
        cabeza = nuevo;
        return cabeza;
    } 

    Nodo* auxiliar = cabeza;

    int cuenta = 0;
    while(cuenta < indice-1) {
        if(auxiliar->siguiente == nullptr) {
            return cabeza; // se sale de rango y aun esta dentro del loop, indice es mayor que total de elementos
        }
        auxiliar = auxiliar->siguiente;
        cuenta++;
    } 
    Nodo* nuevo = new Nodo{valor, auxiliar->siguiente};
    auxiliar->siguiente = nuevo;
    return cabeza;
}

/* Insertar en el medio por Valor

Buscar un valor en la lista, recorriendo uno a uno y mirando si es ese valor.
Si lo encuentra, lo agrega, si no pues retorna a cabeza.
*/

Nodo* insertarMedioPorValor(int valor, Nodo* cabeza, int valorComparar) {
    if(cabeza == nullptr) {
        // no hay elementos entonces pues no se puede agregar de esta forma
        return cabeza;
    }

    Nodo* auxiliar = cabeza;

    while(auxiliar != nullptr) { // recorrer hasta que se llegue al ultimo elemento (se para en el ultimo, no llega a lo que apunta)

        if(auxiliar->valor == valorComparar) {
            Nodo* nuevo = new Nodo{valor, auxiliar->siguiente};
            auxiliar->siguiente = nuevo;
            return cabeza;
        }
        auxiliar = auxiliar->siguiente; // avanzamos si no es el elemento
    }
    // se llego al final y no se encontro el elemento
    return cabeza;
}

// volver a repetir el patron de eliminar valor
Nodo* eliminarPorValor(Nodo* cabeza, int valorEliminar) {
    if(cabeza == nullptr) {
        // no hay nada que eliminar, retorna null/cabeza
        return cabeza;
    }
    // caso en que quiera borrar la cabeza

    Nodo* auxiliar = cabeza; // hacer de pivote
    Nodo* anterior = nullptr;

    while(auxiliar != nullptr) {
        Nodo* siguienteReal = auxiliar->siguiente; // para poder eliminar aux sin borrar nada
        if(auxiliar->valor == valorEliminar) {
            if(anterior == nullptr) {
                // si se esta borrando la cabeza hay que reasignarla
                cabeza = siguienteReal;
                delete auxiliar; // siempre el que se toca es el auxiliar, nunca los datos necesarios 
            } else {
                anterior->siguiente = siguienteReal;
                delete auxiliar;
            }    
        } else {
            anterior = auxiliar;
        }
        auxiliar = siguienteReal;
    }
    // si termina la lista y no retorna nada, o sale de borrar todos
    return cabeza;
}



void imprimir(Nodo* cabeza) {
    for (Nodo* aux = cabeza; aux != nullptr; aux = aux->siguiente) {
        std::cout << "Valor: " << aux->valor << std::endl;
    }
}

int main() {
    // lista de prueba: 12, 3, 8 (3 elementos, indices validos 0,1,2, y 3 para agregar al final)
    cabeza = new Nodo{12, new Nodo{3, new Nodo{8, nullptr}}};

    std::cout << "--- insertar en indice 1 (caso normal) ---" << std::endl;
    cabeza = insertarMedioIndice(99, cabeza, 1);
    imprimir(cabeza);

    std::cout << "--- insertar en indice 4 (agregar al final, valido con 4 elementos) ---" << std::endl;
    cabeza = insertarMedioIndice(100, cabeza, 4);
    imprimir(cabeza);

    std::cout << "--- insertar en indice 0 sobre una lista vacia ---" << std::endl;
    Nodo* pruebaVacia = nullptr;
    pruebaVacia = insertarMedioIndice(500, pruebaVacia, 0);
    imprimir(pruebaVacia);
    std::cout << "(si no se imprimio nada arriba, no se inserto nada)" << std::endl;

    std::cout << "--- insertar en indice 0 sobre lista NO vacia (deberia quedar primero) ---" << std::endl;
    cabeza = insertarMedioIndice(999, cabeza, 0);
    imprimir(cabeza);

    std::cout << "--- insertar en indice 7 (lista tiene 6 elementos, 1 mas del maximo valido = 6) ---" << std::endl;
    cabeza = insertarMedioIndice(200, cabeza, 7);
    imprimir(cabeza);

    std::cout << "--- prueba insertarMedioPorValor: lista limpia 12,3,8 ---" << std::endl;
    Nodo* cabeza2 = new Nodo{12, new Nodo{3, new Nodo{8, nullptr}}};

    std::cout << "insertar 99 despues del 3 (valor del medio)" << std::endl;
    cabeza2 = insertarMedioPorValor(99, cabeza2, 3);
    imprimir(cabeza2);

    std::cout << "insertar 100 despues del 8 (valor del ULTIMO nodo)" << std::endl;
    cabeza2 = insertarMedioPorValor(100, cabeza2, 8);
    imprimir(cabeza2);

    std::cout << "--- prueba eliminarPorValor: lista limpia 12,3,8 ---" << std::endl;
    Nodo* cabeza3 = new Nodo{12, new Nodo{3, new Nodo{8, nullptr}}};

    std::cout << "eliminar el 8 (valor del ULTIMO nodo)" << std::endl;
    cabeza3 = eliminarPorValor(cabeza3, 8);
    imprimir(cabeza3);

    std::cout << "eliminar el 12 (valor de la CABEZA)" << std::endl;
    cabeza3 = eliminarPorValor(cabeza3, 12);
    imprimir(cabeza3);

    return 0;
}