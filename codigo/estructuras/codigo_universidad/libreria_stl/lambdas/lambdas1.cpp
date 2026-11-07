#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

/* Ademas de las utilidades que ya vimos en lambdas, tambien sirve para mas cosas

!!!! PASAR UNA FUNCION COMO PARAMETRO
Es decir, en vez de pasarle a una funcion un valor, se le pasa otra funcion. 

ESO SE HACE CON LAMDA. Como ????????
Para escribir un solo algoritmo que sirva para varios tipos de datos y valores
*/

// forma de escribirla usando template (la mas comun en C++). 
// MOLDE PARA REUSAR CON TIPOS DE VALORES 
template <typename T>
T mayor(T a, T b) {
    if(a > b) {
        return a;
    } else { 
        return b;
    }
}


// usar lambdas para guardar funciones
// cada una tiene un tipo propio y sin nombre
auto cuadrado = [](double x){ return x* x; };
auto suma1 = [](double x){ return x + 1; };


// RECIBIR LA LAMBDA
template <typename F>
double aplicar(F f, double x) { // recibe la funcion como parametro
    return f(x); // devuelve la funcion evauada
}



// ejemplo que puede servir para metodos numericos
template <typename F>
double sumatoria(F f, int i, int n) { // sumatoria desde i hasta n
    double suma = 0;
    for(int j=i; j <= n; ++j) {
        suma += f(i);
    }
    return suma;
}


// pasar funcion por referencia, (F& f), solo util cuando la funcion tiene estado propio, ej: Contador, de resto por valor esta bien

/* Usar un generador de plantillas por ejemplo

!!!! FUNCION QUE DEVULVE OTRA YA CONFIGURADA
ej: Crear funciones lineales en base a lo que se pase como parametro
*/

auto crearFuncionLineal(int m, int b) {
    return [m, b](double x){ return m*x + b; };
}

auto f = crearFuncionLineal(2, 4);


/* VECTOR DE FUNCIONES

No puede ser tipo template T =>. PORQUE CADA LAMBA TIENE TIPO PROPIO, y vector<T> todos deben tener el mismo

std::function<double(double)>
*/


std::vector<std::pair<std::string, std::function<double(double)>>> tablaFunciones = {
    { "doblar", [](double x){ return 2*x; }},
    { "cuadrado", [](double x){ return x*x; }},
    { "seno", [](double x){ return std::cos(x); }} 
};

/* COMO SE USA ??????????
Como es un pair => .first y .second

1. .first => es el nombre de la funcion
2. .second => 
3. .second(valor) =>
*/


int main() {

    // Que pasaria si lo guardo en un unordered_map ???????

    std::unordered_map<std::string, std::function<double(double)>> funcion;

    funcion["cuadrado"] = [](double x){ return x*x ;}; 

    // VENTAJA: SOLO CON EL NOMBRE ACCEDO A LA FUNCION DE UNA

    funcion.at("cuadrado")(2);

    return 0;
}