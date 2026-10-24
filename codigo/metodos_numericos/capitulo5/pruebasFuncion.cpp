#include <iostream>
#include <cmath>

double funcion1(double x) {
    return x*x - 2;
}

double funcion2(double x) {
    return std::cos(x) - x;
}

// ahora escribir funcion tabular, "g es el nombre de la funcion", se usa g(x)
void tabular(double (*g)(double), double desde, double hasta, double pasos) {
    double ancho = (hasta - desde) / pasos;

    double x = 0;
    for(int i=0; i<pasos; ++i) {
        x = (desde + i *(hasta - desde)) / pasos;
        std::cout<< x <<", "<<g(x) <<std::endl;
    }
}


int main() {

    return 0;
}