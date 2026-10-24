#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

/* PRECISION CON LA QUE TRABAJA "DOUBLE"

Para poder ver cual es el paso optimo "h" de la maquina. 
*/

double epsilonDeLaMaquina() {
    double eps = 1.0;
    
    do {
        eps = eps / 2;
    } while(1.0 + eps /2  != 1.0);
    
    return eps;
}

// casos de prueba nada mas
double f(double x) {
    // devolver la funcion del ejemplo, evaluarla
    return -(0.1* std::pow(x, 4)) - (0.15*std::pow(x,3)) - (0.5* std::pow(x, 2)) -(0.25*x) + 1.2;
}

double dfExacta(double x) {
    return -0.4*std::pow(x,3) -0.45*std::pow(x,2) - x - 0.25;
}

// usar los metodos de diferencias finitas
double difAdelante(double x, double h) {
    // retornar la derivada truncada en orden 1 
    return (f(x+h) - f(x)) / h;
}

double difAtras(double x, double h) {
    return (f(x) - f(x-h)) / h;
}

double difCentrada(double x, double h) {
    return (f(x+h) - f(x-h)) / (2*h);
}

int factorial(int n) {
    // se trunca despues de 12 (por limite de bits de int)
    if(n < 0 || n > 12) {
        return -1;
    } else if(n == 0 || n == 1) {
        return 1;
    } else {
        int resultado = 1;
        while(n > 0) {
            resultado = n*resultado;
            n -= 1;
        }
        return resultado;
    }
}


int main() {
    double epsilon = epsilonDeLaMaquina();
    std::cout<<"Limite por ciclo propio: "<<epsilon<<std::endl;

    // ahora usando limites 
    std::cout<<"Epsilon de la maquina real: "<<std::numeric_limits<double>::epsilon()<<std::endl;

    std::cout<<"Prueba de resultados: "<<f(0.5)<<", "<<dfExacta(0.5)<<std::endl;

    double h = 1.0;
    double exacta = dfExacta(0.5);

    // formato de la tabla: notacion cientifica, 4 decimales (se fija una sola vez)
    std::cout << std::scientific << std::setprecision(4);
    std::cout << std::setw(12) << "h"
              << std::setw(14) << "derivada"
              << std::setw(14) << "error %" << std::endl;

    do {
        double aprox = difCentrada(0.5, h);
        double error = std::abs((exacta - aprox) / exacta) * 100;
        std::cout << std::setw(12) << h
                  << std::setw(14) << aprox
                  << std::setw(14) << error << std::endl;
        h = h / 10;
    } while(h > 1.0e-16); // desigualdad: comparar double con != nunca llega a coincidir

    return 0;
}