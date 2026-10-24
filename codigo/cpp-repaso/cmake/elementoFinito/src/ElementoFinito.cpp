#include "ElementoFinito.hpp"

ElementoFinito::ElementoFinito(int n): numNodos(n) {}

ElementoFinito::~ElementoFinito() {}

int ElementoFinito::getNumNodos() const {
    return numNodos;
}

// no escribo los metodos virtuales puros, LOS OVERRIDES SE ESCRIBEN EN EL .cpp PURO

