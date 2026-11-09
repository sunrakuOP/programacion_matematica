#include <iostream>
#include <algorithm>
#include <vector>

/* ALGORITMOS CON CONDICIONES (lambdad)

Le paso los elementos y el lamnda decide si si o no, dependiendo del tipo de algoritmo que sea 

1. SORT => (solo condiciones de < o > ), no igualdad, genera errores
2. FIND_IF => devuelve iterador a la primera posicion que cumpla
3. COUNT_IF => lleva la cuenta de cuantos cumplen
4. ANY_OF / ALL_OF => Si alguno cumple (any) o si todos cumplen (all), devuelve TRUE / FALSE
*/


int cuentaMayorA(const std::vector<int>& v, int m) {
    return std::count_if(v.begin(), v.end(),
        [m](int x){ return x > m; });
} 

int primeroMayorQue(const std::vector<int>& v, int m) {
    auto it = std::find_if(v.begin(), v.end(), 
        [m](int x){ return x > m; });
    if(it == v.end()) {
        return -1;
    }
    // si si exite debo retornar el indice 
    return it - v.begin(); // creo que se haria asi 
}

bool algunNegativo(const std::vector<int>& v) {
    return (std::any_of(v.begin(), v.end(),
        [](int x){ return x < 0; }));
}




int main() {

    return 0;
}