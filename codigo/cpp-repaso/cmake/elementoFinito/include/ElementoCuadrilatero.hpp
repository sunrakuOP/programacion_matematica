#pragma once
#include "ElementoFinito.hpp"

class ElementoCuadrilatero: public ElementoFinito {
private:
    double ancho, alto;
public:
    ElementoCuadrilatero(double a, double b);

    double getBase() const;
    double getAltura() const;

    double area() const override;
    Matriz<double> matrizLocal() const override;
};