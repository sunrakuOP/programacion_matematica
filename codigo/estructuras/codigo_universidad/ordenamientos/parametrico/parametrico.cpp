#include <iostream>
#include <vector>
#include <string>
#include <utility>

void ordenamiento(std::vector<int>& v, int a, int b) {
    // Rango de valores es [a,b]
    int rango = (b - a) + 1;
    std::vector<int> cuenta(rango);
    
    for(int i=0; i < (int)v.size(); ++i) {
        int x = v[i];
        cuenta[x - a]++;
    }
    int i = 0;
    for(int j=0; j < (int)cuenta.size(); ++j) {
        int y = cuenta[j];
        for(int k=0; k < y; ++k) {
            v[i] = a+j;
            ++i;
        }
    }
}

// Versión estable y genérica: sirve para cualquier tipo T del que se pueda sacar
// una clave entera en [a,b] mediante la función `clave`.
template <typename T, typename Clave>
void ordenamientoEstable(std::vector<T>& v, int a, int b, Clave clave) {
    int rango = (b - a) + 1;
    std::vector<int> inicio(rango, 0);

    for (const T& e : v) {
        ++inicio[clave(e) - a];            // 1) contar
    }
    int acumulado = 0;                      // 2) cuenta -> inicio de cada grupo
    for (int j = 0; j < rango; ++j) {
        int cuentaJ = inicio[j];
        inicio[j] = acumulado;
        acumulado += cuentaJ;
    }
    std::vector<T> salida(v.size());        // 3) colocar de izquierda a derecha (estable)
    for (const T& e : v) {
        salida[inicio[clave(e) - a]++] = e;
    }
    v = std::move(salida);                  // 4) devolver
}

struct Estudiante {
    std::string nombre;
    int semestre;
};

int main() {
    std::vector<Estudiante> es = {{"Ana", 5}, {"Luis", 2}, {"Eva", 5}, {"Tomas", 2}};
    ordenamientoEstable(es, 2, 5, [](const Estudiante& e) { return e.semestre; });
    for (const Estudiante& e : es) std::cout << e.nombre << "(" << e.semestre << ") ";
    std::cout << "\n";

    // Otro tipo, otra clave: palabras ordenadas por largo (1..10)
    std::vector<std::string> ps = {"casa", "sol", "mar", "luna", "pez", "arbol"};
    ordenamientoEstable(ps, 1, 10, [](const std::string& s) { return (int)s.size(); });
    for (const std::string& s : ps) std::cout << s << " ";
    std::cout << "\n";
    return 0;
}