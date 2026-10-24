#include "ElementoCuadrilatero.hpp"

ElementoCuadrilatero::ElementoCuadrilatero(int b, int h): ElementoFinito(4), base(b), altura(h) {}

double ElementoCuadrilatero::area() {
    return base * altura;
}
