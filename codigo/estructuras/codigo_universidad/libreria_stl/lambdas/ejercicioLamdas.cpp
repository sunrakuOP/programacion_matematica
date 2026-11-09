#include <iostream>
#include <algorithm>


template <typename F>

// entro la funcion y la ejecuto para x "n veces"
double aplicarFnumVeces(F f, double x, int n) {
    for(int i=0; i < n; ++i) {
        x = f(x);
    }
    return x;
}

// funcion crear potencia
auto crearPotenciaLambda = [](int x, int n){
    double acumulado = 1;
    for(int i = 0; i < n; ++i) {
        acumulado = x*acumulado;
    }
    return acumulado;
};

// crearlo usando lambda, solo recibe el valor de la potencia y devuelve la funcion
auto crearFuncionP(int p) {
    return [p](double x){
        double acumulado = 1.0;
        for(int i=0; i < p; ++i) {
            acumulado = x*acumulado;
        } 
        return acumulado;
    };
};


// ahora crear una funcion compuesta
template <typename F, typename G>
double funcionCompuesta(F f, G g, double x) {
    x = g(x);
    return f(x);
}

int main() {
    
    return 0;
}