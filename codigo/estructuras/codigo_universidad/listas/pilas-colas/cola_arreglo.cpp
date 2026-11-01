#include <iostream>

/*
En un arreglo eliminar un valor solo mueve un espacio el bloque

Volverlo circular para que el espacio que se libere al frente se aproveche al final
*/

class Cola {
private:
    int* datos;
    int capacidad;
    int posicion = -1;
    int cantidad = 0; // cada vez que agregue un elemento aumento
    int inicio = 0;
public:
    Cola(int n): capacidad(n), datos(new int[n]) {}

    ~Cola() {
        delete[] datos;
    }

    bool estaVacia() const {
        if(cantidad == 0) {
            return true;
        }
        return false;
    }

    bool estaLlena() const {
        if(capacidad == cantidad) {
            return true;
        }
        return false;
    }

    void enqueue(int valor) {
        if(estaLlena()) {
            return;
        }
        posicion = (posicion+1) % capacidad;
        datos[posicion] = valor;
        cantidad++;
    }

    int dequeue() {
        if(estaVacia()) {
            return -1;
        }
        int valor = datos[inicio];
        inicio = (inicio+1) % capacidad;
        cantidad--;
        return valor;
    }

    int front() const {
        if(estaVacia()) {
            return -1;
        }
        return datos[inicio];
    }
};




int main() {

    return 0;
}