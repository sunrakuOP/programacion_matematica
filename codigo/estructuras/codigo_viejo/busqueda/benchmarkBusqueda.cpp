#include <iostream>
#include <vector>
#include <chrono>
#include <random>

int buscarLineal(const std::vector<int>& v, int valor) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == valor) return (int)i;
    }
    return -1;
}

int busquedaBinaria(const std::vector<int>& v, int objetivo) {
    if (v.size() == 0) return -1;
    int izq = 0;
    int der = static_cast<int>(v.size()) - 1;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        if (v[medio] == objetivo) return medio;
        else if (v[medio] < objetivo) izq = medio + 1;
        else der = medio - 1;
    }
    return -1;
}

int main() {
    const int N = 1'000'000;   // tamano del vector ordenado
    const int M = 10'000;      // cuantas busquedas repetimos

    std::vector<int> v(N);
    for (int i = 0; i < N; ++i) v[i] = i;   // ya ordenado por construccion

    std::mt19937 rng(42);   // semilla fija -> mismos resultados cada corrida
    std::uniform_int_distribution<int> dist(0, N - 1);

    std::vector<int> objetivos(M);
    for (int i = 0; i < M; ++i) objetivos[i] = dist(rng);

    // los checksum acumulan el resultado de cada busqueda -> el optimizador
    // no puede borrar el loop, porque el resultado SI se termina usando (se imprime).
    long long checksumLineal = 0;
    long long checksumBinaria = 0;

    auto inicioLineal = std::chrono::high_resolution_clock::now();
    for (int obj : objetivos) checksumLineal += buscarLineal(v, obj);
    auto finLineal = std::chrono::high_resolution_clock::now();

    auto inicioBinaria = std::chrono::high_resolution_clock::now();
    for (int obj : objetivos) checksumBinaria += busquedaBinaria(v, obj);
    auto finBinaria = std::chrono::high_resolution_clock::now();

    auto msLineal = std::chrono::duration_cast<std::chrono::milliseconds>(finLineal - inicioLineal).count();
    auto msBinaria = std::chrono::duration_cast<std::chrono::milliseconds>(finBinaria - inicioBinaria).count();

    std::cout << N << " elementos, " << M << " busquedas repetidas\n";
    std::cout << "Lineal:  " << msLineal  << " ms (checksum " << checksumLineal  << ")\n";
    std::cout << "Binaria: " << msBinaria << " ms (checksum " << checksumBinaria << ")\n";

    return 0;
}
