#include <iostream>
#include <cmath>

// Problema 2.10, aproximacion de la raiz cuadrada de un numero
double raizAprox(int a, int maxIter) {
    if(a < 0) {
        return -1;
    } else if(a == 0) {
        return 0;
    } else if(maxIter <= 0) {
        return -1;
    }

    int cifrasSignificativas = 6; // cuántas cifras correctas queremos garantizar
    double tolerancia = 0.5 * std::pow(10, 2 - cifrasSignificativas); // formula de Chapra, Cap. 3: Es = 0.5 * 10^(2-n) %
    double x_nuevo = 0;
    double errorAprox = 0;
    int iteraciones = 0;

    double x = a; // arrancar en el valor a
    do {
        x_nuevo = (x + (a/x)) / 2;
        errorAprox = std::abs(((x_nuevo - x) / x_nuevo)) * 100;
        x = x_nuevo;
        iteraciones++;
    } while(errorAprox > tolerancia && iteraciones < maxIter);

    return x;
}


// problema 2.8, la aproximacion del coseno
int factorial(int valor) {
    if(valor < 0){
        return -1;
    } else if(valor == 0) {
        return 0;
    } else if(valor == 1) {
        return 1;
    }
    int resultado = 1;
    while(valor > 0) {
        resultado *= valor;
        valor--;
    }

    return resultado;
}


double cosenoFactorial(double x ,int n) {
    if(n < 0) {
        return -1;
    } else if(n == 0) {
        return 1;
    }  

    double resultado = 1;
    double valorReal = std::cos(x);
    double error = 0;
    // se itera n veces desde 1
    for(int i=1; i<=n; ++i) {
        if(i % 2 == 0) {
            resultado += std::pow(x, (2*i)) / factorial(2*i);
        } else {
            resultado -= std::pow(x, (2*i)) / factorial(2*i);
        }
        error = ((valorReal - resultado) / valorReal) * 100;
        std::cout<<"Error actual (iteracion "<< i <<"): "<<error <<std::endl;
    }   
    return resultado;
}

int main() {
    double r = cosenoFactorial(1.25, 5);
    std::cout<<r<<std::endl;
    
    return 0;
}