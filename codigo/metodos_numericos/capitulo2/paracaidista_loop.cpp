#include <iostream>
#include <cmath>

double velocidad(double cd, double m, double dt, double ti, double tf, double vi) {
    double g = 9.8;
    double numIter = (tf - ti) / dt;

    for(int i=0; i<numIter; ++i) {
        double dvdt = g - (cd/m)*vi;
        vi = vi + dvdt*dt;
    }
    return vi;
}



int main() {

    return 0;
}