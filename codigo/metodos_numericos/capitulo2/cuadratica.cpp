#include <iostream>
#include <cmath>
#include <utility>

struct RaicesCuadraticas {
    double r1, r2 = 0;
    double i1=0, i2=0; // parte imaginaria con default 0
};

RaicesCuadraticas cuadratica(double a, double b, double c) {
    if(a == 0 && b != 0) {
        double r1 = -c / b;
        return RaicesCuadraticas{r1};
    } 
    if(a == 0 && b == 0) {
        return RaicesCuadraticas{0,0,0,0};
    }

    double denominador = 2*a;
    double discriminante = b*b - 4*a*c;

    if(discriminante >= 0) {
        double r1 = (-b + std::sqrt(discriminante)) / denominador;
        double r2 = (-b - std::sqrt(discriminante)) / denominador;

        RaicesCuadraticas valores{r1, r2};
        return valores;
    } else {
        double r1 = -b / denominador;
        double r2 = r1;
        double i1 = (std::sqrt(std::abs(discriminante))) / denominador ;
        double i2 = -i1;

        return RaicesCuadraticas{r1,r2,i1,i2};
    }
}

int main() {

    return 0;
}