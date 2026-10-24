#include <iostream>
#include <cmath>


double biseccion(double (*f)(double), double x1, double x2, int maxIter, int n) {
    if(f(x1)*f(x2) >= 0) {
        // si ambas imagenes son del mismo signo, no cumplen la condicion del intervalo
        return -1.0;
    }
    // n es el numero de cifras significativas
    double es = 0.5*std::pow(10, 2-n);
    double ea = 100; // incializado en un valor grande
    int iter = 0;
    double medio = 0;
    double medioAnt = 0;
    double fm = 0;

    do {
        medioAnt = medio;
        medio = (x1 + x2) / 2;
        if(iter > 0) {
            ea = std::abs((medio - medioAnt) / medio) * 100;
        }
        fm = f(medio); // para no tener que llamarlo 2 veces

        if(fm == 0){
            return medio;
        } else if(fm*f(x1) < 0) {
            x2 = medio;
        } else {
            x1 = medio;
        }
        iter++;
    } while(ea > es && iter < maxIter);

    return medio;
}

// funciones de prueba
double funcion1(double x) {
    return x*x - 2;
}

double funcion2(double x) {
    return std::cos(x) - x;
}


int main() {
    double prueba1 = biseccion(funcion1, -1, 2, 50, 6);
    std::cout<< prueba1<<std::endl;

    double prueba2 = biseccion(funcion2, -1, 2, 50, 6);
    std::cout<< prueba2;

    double prueba3 = biseccion(funcion1, -1, 2, 50, 6);
    std::cout<< prueba3<<std::endl;

    return 0;
}