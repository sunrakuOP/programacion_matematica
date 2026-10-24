#include <iostream>
#include <vector>

struct Nodo {
    double x,y,z; // coordenada del punto a analizar 
};

/* Buscar nodo por coordenadas
Cuando genero la malla defino los elementos uno por uno
2 elementos que estan pegados deben compartir el mismo nodo (NO PUEDE TENER CADA UNO UNA COPIA)

Se debe buscar si ya existe un nodo en la posicion (buscar nodo por coordenadas)

La idea es ver si es un Nodo restrigido para no usarlo (empotrado por ejemplo)
*/

Nodo* buscarNodoPorCoordenadas(const std::vector<Nodo*>& nodos, double x, double y, double z) {
    for(const auto& nodo: nodos) {
        if(nodo->x == x && nodo->y == y && nodo->z == z) {
            return nodo;
        } 
    }
    return nullptr;
}   

bool gdlRestringidos(const std::vector<Nodo*>& restringidos, double x, double y, double z) {
    if(buscarNodoPorCoordenadas(restringidos,x,y,z)) return true;
    else return false;
}




int main() {
    std::vector<Nodo*> nodos = {
        new Nodo{0.0, 0.0, 0.0},
        new Nodo{1.0, 0.0, 0.0},
        new Nodo{2.0, 0.0, 0.0},
        new Nodo{3.0, 0.0, 0.0},
        new Nodo{4.0, 0.0, 0.0}
    };
    std::vector<Nodo*> vacio;

    Nodo* r1 = buscarNodoPorCoordenadas(nodos, 2.0, 0.0, 0.0);   // medio
    Nodo* r2 = buscarNodoPorCoordenadas(nodos, 0.0, 0.0, 0.0);   // primero
    Nodo* r3 = buscarNodoPorCoordenadas(nodos, 4.0, 0.0, 0.0);   // ultimo
    Nodo* r4 = buscarNodoPorCoordenadas(nodos, 9.0, 9.0, 9.0);   // no existe
    Nodo* r5 = buscarNodoPorCoordenadas(vacio, 0.0, 0.0, 0.0);   // vacio

    std::cout << "coincide medio (2,0,0)    -> " << (r1 ? "encontrado" : "no encontrado") << " (esperado: encontrado)" << std::endl;
    std::cout << "coincide primero (0,0,0)  -> " << (r2 ? "encontrado" : "no encontrado") << " (esperado: encontrado)" << std::endl;
    std::cout << "coincide ultimo (4,0,0)   -> " << (r3 ? "encontrado" : "no encontrado") << " (esperado: encontrado)" << std::endl;
    std::cout << "no existe (9,9,9)         -> " << (r4 ? "encontrado" : "no encontrado") << " (esperado: no encontrado)" << std::endl;
    std::cout << "vector vacio              -> " << (r5 ? "encontrado" : "no encontrado") << " (esperado: no encontrado)" << std::endl;

    for (Nodo* n : nodos) delete n;

    return 0;
}