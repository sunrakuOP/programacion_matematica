#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <utility>

/* FUNCION HASH
!!!! Convierte una clave en un indice donde agregar el valor (en el mapa)
*/


struct HashArista {
    size_t operator()(const std::pair<int,int>& e) const {
        // tu idea: combinar e.first y e.second en UN número
        return (size_t)e.first * 31 + e.second;
    }
};

using Arista = std::pair<int,int>;

// Siempre (menor, mayor): (3,2) y (2,3) son la MISMA arista
Arista normalizar(int a, int b) {
    return {std::min(a, b), std::max(a, b)};
}

int main() {
    std::unordered_map<Arista, int, HashArista> conteo;

    // Cada triángulo trae sus 3 nodos; sus aristas son los pares consecutivos (y el último con el primero)
    int triangulos[2][3] = { {1, 2, 3},     // A
                             {3, 2, 4} };   // B

    for (int t = 0; t < 2; ++t) {
        for (int k = 0; k < 3; ++k) {
            int a = triangulos[t][k];
            int b = triangulos[t][(k + 1) % 3];
            ++conteo[normalizar(a, b)];
        }
    }

    // El orden de recorrido del unordered_map NO es significativo
    for (auto it = conteo.begin(); it != conteo.end(); ++it) {
        std::cout << "(" << it->first.first << "," << it->first.second << ") -> " << it->second;
        std::cout << (it->second == 1 ? "  borde" : "  interior") << "\n";
    }
    return 0;
}