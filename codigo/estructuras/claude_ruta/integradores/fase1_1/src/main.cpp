#include "Malla.hpp"

int main() {
    Malla malla;

    malla.agregarNodo(0.0, 0.0, 0.0, 100);
    malla.agregarNodo(2.0, 1.0, 0.0, 205);
    malla.agregarNodo(4.0, 1.0, 1.5, 310);
    malla.agregarNodo(6.0, 0.0, 1.5, 415);

    malla.agregarBarra(200e9, 0.001,  100, 205);
    malla.agregarBarra(200e9, 0.0015, 205, 310);
    malla.agregarBarra(200e9, 0.0008, 310, 415);

    malla.procesarCola();

    return 0;
}
