#pragma once
#include "Matriz.hpp"
// como ElementoFinito no es template, si hay que hacerle .hpp y .cpp

class ElementoFinito {
private:
    int numNodos;
public:
    ElementoFinito(int n);
    virtual ~ElementoFinito();

    int getNumNodos() const;
    
    virtual double area() const = 0;
    virtual Matriz<double> matrizLocal() const = 0;
};