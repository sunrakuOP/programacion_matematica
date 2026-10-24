#include "ElementoCuadrilatero.hpp"

ElementoCuadrilatero::ElementoCuadrilatero(double a, double b)
    : ElementoFinito(4), ancho(a), alto(b) {}

double ElementoCuadrilatero::getBase() const {
    return ancho;
}

double ElementoCuadrilatero::getAltura() const {
    return alto;
}

double ElementoCuadrilatero::area() const {
    return ancho * alto;
}

Matriz<double> ElementoCuadrilatero::matrizLocal() const {
    Matriz<double> m(2, 2);
    m(0,0) = ancho;
    m(0,1) = alto;
    m(1,0) = alto;
    m(1,1) = ancho * alto;
    return m;
}


