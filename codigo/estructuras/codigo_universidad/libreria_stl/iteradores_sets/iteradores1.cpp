#include <iostream>
#include <vector>
#include <string>

/* ITERADORES

Un vector guarda los datos contiguos, una lista los guarda en nodos sueltos, un map en un arbol
!!!! Cada uno se recorre diferente, pero si los quiero recorrer igual => ITERADOR

Que hace???
Apuntar a una posicion de la estructura, y avanzar a la siguiente

Para un vector es basicamente un puntero. 

v.begin() => Apunta al primer elemento
v.end() => Apunta una posicion despues del ultimo (como un vacio)

*it => Elemento al que apunta (desreferenciando)
*/




int main() {
    std::vector<int> v = { 1,2,3,4,5,6,7,8,9 };

    // debo eliminar todos los pares
    for(auto it = v.begin(); it != v.end();) {
        if(*it % 2 == 0) {
            it = v.erase(it);
        } else {
            ++it;
        }
    }
    
    return 0;
}