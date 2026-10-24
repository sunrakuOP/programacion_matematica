#include "ElementoBarra.hpp"
#include <cmath>

ElementoBarra::ElementoBarra(double e, double a, Nodo n1, Nodo n2)
    : ElementoFinito(2), e(e), a(a), n1(n1), n2(n2) {}

double ElementoBarra::areaTransversal() const { return a; }
double ElementoBarra::area() { return areaTransversal(); }

double ElementoBarra::longNodo() const {
    double dx = n2.x - n1.x;
    double dy = n2.y - n1.y;
    double dz = n2.z - n1.z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

Matriz<double> ElementoBarra::matrizLocal() {
    double l = longNodo();
    RegistroCalculo registro{e, a, l, e*a/l};
    pilaRegistros.push(registro);

    Matriz<double> K(2, 2);

    K(0,0) = +(e*a)/l;
    K(0,1) = -(e*a)/l;
    K(1,0) = -(e*a)/l;
    K(1,1) = +(e*a)/l;

    return K;
}
