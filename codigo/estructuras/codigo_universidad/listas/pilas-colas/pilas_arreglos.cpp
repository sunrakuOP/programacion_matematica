#include <iostream>

/* PILAS COMO EN STL

Ya que en la version de la libreria las pilas se usan con bloques (por velocidad)
Pues aprendamoslo a usar tambien de esta forma.

Ya no se hace por nodos sino que se hace por indices.

Tope es la posicion del ultimo elemento (arranca en -1)
*/

class Pila {
private:
    int capacidad;
    int tope; // se incializa en -1
    int* arreglo; // puntero al primer elemento
public:
    Pila(int n): capacidad(n), tope(-1), arreglo(new int[n]) {}

    ~Pila() {
        delete[] arreglo;
    }

    bool estaVacia() const {
        if(tope == -1) {
            return true;
        } 
        return false;
    }

    bool estaLlena() const {
        if(tope == capacidad - 1){
            return true;
        }
        return false;
    }

    void push(int valor) {
        if(estaLlena()) {
            return;
        }
        tope++;
        arreglo[tope] = valor;
    }

    int top() const {
        if(estaVacia()) {
            return -1;
        }
        return arreglo[tope];
    }

    int pop() {
        if(estaVacia()) {
            return -1;
        }
        int valor = arreglo[tope];
        tope--;
        return valor;
    }

};





int main() {

    return 0;
}