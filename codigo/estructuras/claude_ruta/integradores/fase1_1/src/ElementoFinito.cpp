#include "ElementoFinito.hpp"

ElementoFinito::ElementoFinito(int n): numNodos(n) {}
ElementoFinito::~ElementoFinito() {}

int ElementoFinito::getNumNodos() const { return numNodos; }
