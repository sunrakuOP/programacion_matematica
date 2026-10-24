#pragma once
#include "ElementoFinito.hpp"

class ElementoCuadrilatero: public ElementoFinito {
private:
    int base, altura;
public:
    ElementoCuadrilatero(int b, int h);

    double area() override;
};
