#pragma once
#include <stack>
#include "ElementoFinito.hpp"
#include "Nodo.hpp"
#include "RegistroCalculo.hpp"
#include "Matriz.hpp"

class ElementoBarra: public ElementoFinito {
private:
    double e, a;
    Nodo n1, n2;
    std::stack<RegistroCalculo> pilaRegistros;
public:
    ElementoBarra(double e, double a, Nodo n1, Nodo n2);

    double areaTransversal() const;
    double area() override;

    double longNodo() const;
    Matriz<double> matrizLocal();
};
