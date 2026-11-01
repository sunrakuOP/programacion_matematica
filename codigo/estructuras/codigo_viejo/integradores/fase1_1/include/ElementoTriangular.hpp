#pragma once
#include "ElementoFinito.hpp"

class ElementoTriangular: public ElementoFinito {
private:
    int base, altura;
public:
    ElementoTriangular(int b, int h);

    double area() override;
};
