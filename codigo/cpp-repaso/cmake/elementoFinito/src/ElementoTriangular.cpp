#include "ElementoTriangular.hpp"

ElementoTriangular::ElementoTriangular(double b, double h)
    : ElementoFinito(3), base(b), altura(h) {}

double ElementoTriangular::getBase() const {
    return base;
}

double ElementoTriangular::getAltura() const {
    return altura;
}

double ElementoTriangular::area() const {
    return (base * altura) / 2.0;
}

Matriz<double> ElementoTriangular::matrizLocal() const {
    Matriz<double> m(2, 2);
    m(0,0) = base;
    m(0,1) = altura;
    m(1,0) = altura;
    m(1,1) = base * altura;
    return m;
}