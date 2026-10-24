#pragma once
#include "ElementoFinito.hpp"

class ElementoTriangular: public ElementoFinito {
private:
    double base, altura;
public:
    ElementoTriangular(double b, double h);

    double getBase() const;
    double getAltura() const;

    double area() const override;
    Matriz<double> matrizLocal() const override;
};