#include <iostream>
#include <vector>

/* Busqueda Lineal: O(n)
Revisar uno por uno cada elemento, comprueba por cada elemento a ver si lo encuentra

Busqueda binaria: O(log n)
SOLO SIRVE PARA DATOS ORDENADOS
*/

int buscarLineal(const std::vector<int>& vector, int valor) {
    if(vector.size() == 0) {
        std::cout<<"Vector vacio"<<std::endl;
        return -1;
    }
    for(size_t i=0; i< vector.size(); ++i) {
        if(vector[i]== valor) {
            return (int)i;
        }
    }
    return -1;
}

// SOLO PARA DATOS ORDENADOS 
int busquedaBinaria(const std::vector<int>& vector, int valor) {
    if(vector.size() == 0) {
        std::cout<<"Vector vacio"<<std::endl;
        return -1;
    }
    int izq = 0; int der = vector.size() -1; // rango inicial [0, n-1]
    while(izq <= der) {
        int medio = izq + (der - izq) / 2;
        if(vector[medio] == valor) return medio;
        else if(vector[medio] < valor) izq = medio + 1; // si es mayor que medio esta en la mitad superior, entonces izq se mueve
        else der = medio -1; // si es menor que medio esta en la mitad inferior entonces der se mueve 
    }
    // si no lo encuentra, retorna -1
    return -1;
}

int main() {
    std::vector<int> v = {1, 3, 5, 7, 9, 11, 13, 15};
    std::vector<int> vacio;
    std::vector<int> unElemento = {42};
    std::vector<int> dosElementos = {10, 20};

    std::cout << "buscar 7 (medio)     -> " << buscarLineal(v, 7) << " (esperado: 3)" << std::endl;
    std::cout << "buscar 1 (primero)   -> " << buscarLineal(v, 1) << " (esperado: 0)" << std::endl;
    std::cout << "buscar 15 (ultimo)   -> " << buscarLineal(v, 15) << " (esperado: 7)" << std::endl;
    std::cout << "buscar 4 (no existe) -> " << buscarLineal(v, 4) << " (esperado: -1)" << std::endl;
    std::cout << "buscar 5 (vacio)     -> " << buscarLineal(vacio, 5) << " (esperado: -1)" << std::endl;

    std::cout << "\n--- busquedaBinaria ---" << std::endl;
    std::cout << "binaria 7 (medio)          -> " << busquedaBinaria(v, 7) << " (esperado: 3)" << std::endl;
    std::cout << "binaria 1 (primero)        -> " << busquedaBinaria(v, 1) << " (esperado: 0)" << std::endl;
    std::cout << "binaria 15 (ultimo)        -> " << busquedaBinaria(v, 15) << " (esperado: 7)" << std::endl;
    std::cout << "binaria 4 (no existe)      -> " << busquedaBinaria(v, 4) << " (esperado: -1)" << std::endl;
    std::cout << "binaria 5 (vacio)          -> " << busquedaBinaria(vacio, 5) << " (esperado: -1)" << std::endl;
    std::cout << "binaria 42 (1 elemento)    -> " << busquedaBinaria(unElemento, 42) << " (esperado: 0)" << std::endl;
    std::cout << "binaria 20 (2 elementos)   -> " << busquedaBinaria(dosElementos, 20) << " (esperado: 1)" << std::endl;

    return 0;
}