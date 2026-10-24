#include <iostream>
#include "Malla.hpp"
#include "Vector2D.hpp"
#include "Vector3D.hpp"

int main() {
    std::cout << "=== Malla (Fase 1) ===" << std::endl;
    Malla malla;

    malla.agregarNodo(0.0, 0.0, 0.0, 100);
    malla.agregarNodo(2.0, 1.0, 0.0, 205);
    malla.agregarNodo(4.0, 1.0, 1.5, 310);
    malla.agregarNodo(6.0, 0.0, 1.5, 415);

    malla.agregarBarra(200e9, 0.001,  100, 205);
    malla.agregarBarra(200e9, 0.0015, 205, 310);
    malla.agregarBarra(200e9, 0.0008, 310, 415);

    malla.procesarCola();

    std::cout << "\n=== Vectores (Estatica) ===" << std::endl;
    Punto2D p1{0.0, 0.0};
    Punto2D p2{3.0, 4.0};
    Vector2D direccion = p2 - p1;   // punto - punto = vector

    std::cout << "direccion entre " << p1 << " y " << p2 << " = " << direccion << std::endl;
    std::cout << "magnitud = " << direccion.magnitud() << std::endl;

    Punto2D p3 = p1 + direccion;    // punto + vector = punto
    std::cout << "p1 desplazado por 'direccion' = " << p3 << " (debe volver a dar " << p2 << ")" << std::endl;

    return 0;
}
