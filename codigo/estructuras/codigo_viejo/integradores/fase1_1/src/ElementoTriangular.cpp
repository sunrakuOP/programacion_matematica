#include "ElementoTriangular.hpp"

ElementoTriangular::ElementoTriangular(int b, int h): ElementoFinito(3), base(b), altura(h) {}

double ElementoTriangular::area() {
    return (base * altura) / 2.0;
}
