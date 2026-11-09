#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using M = std::vector<std::vector<double>>;

int main() {
    // 3 palabras, cada una un vector de 2 numeros (ya proyectado a Q, K, V)
    M Q = {{1, 0}, {0, 1}, {1, 1}};
    M K = {{1, 0}, {0, 1}, {1, 1}};
    M V = {{1, 2}, {3, 4}, {5, 6}};
    int n = 3, d = 2;

    M pesos(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        double suma = 0;
        for (int j = 0; j < n; ++j) {                       // puntaje = Q_i . K_j / sqrt(d)
            double s = 0;
            for (int t = 0; t < d; ++t) s += Q[i][t] * K[j][t];
            pesos[i][j] = std::exp(s / std::sqrt((double)d));
            suma += pesos[i][j];
        }
        for (int j = 0; j < n; ++j) pesos[i][j] /= suma;    // softmax por fila
    }
    std::cout << std::fixed << std::setprecision(3) << "pesos de atencion:\n";
    for (auto& f : pesos) { for (double w : f) std::cout << std::setw(7) << w; std::cout << "\n"; }
    std::cout << "salida = pesos * V:\n";
    for (int i = 0; i < n; ++i) {
        for (int t = 0; t < d; ++t) {
            double s = 0;
            for (int j = 0; j < n; ++j) s += pesos[i][j] * V[j][t];
            std::cout << std::setw(7) << s;
        }
        std::cout << "\n";
    }
}
