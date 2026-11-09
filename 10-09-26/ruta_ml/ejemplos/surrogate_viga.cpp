#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <utility>

using Matriz = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

Vector resolver(Matriz A, Vector b) {
    int n = A.size();
    for (int c = 0; c < n; ++c) {
        int p = c;
        for (int f = c + 1; f < n; ++f) if (std::fabs(A[f][c]) > std::fabs(A[p][c])) p = f;
        std::swap(A[c], A[p]); std::swap(b[c], b[p]);
        for (int f = c + 1; f < n; ++f) { double m = A[f][c] / A[c][c]; for (int k = c; k < n; ++k) A[f][k] -= m * A[c][k]; b[f] -= m * b[c]; }
    }
    Vector x(n);
    for (int i = n - 1; i >= 0; --i) { double s = b[i]; for (int j = i + 1; j < n; ++j) s -= A[i][j] * x[j]; x[i] = s / A[i][i]; }
    return x;
}

int main() {
    // viga en voladizo: flecha en el extremo  delta = P L^3 / (3 E I)
    const double E = 210e9, base = 0.05, alto = 0.10, I = base * alto * alto * alto / 12;
    auto flecha = [&](double L, double P) { return P * L * L * L / (3 * E * I); };

    std::mt19937 gen(21);
    std::uniform_real_distribution<double> uL(0.5, 3.0), uP(100, 2000);
    std::normal_distribution<double> ruido(0, 0.02);        // 2% de error de medicion
    const int n = 300;
    Matriz X(n, Vector(3));
    Vector y(n);
    for (int i = 0; i < n; ++i) {
        double L = uL(gen), P = uP(gen);
        double medida = flecha(L, P) * (1 + ruido(gen));
        X[i] = {1.0, std::log(L), std::log(P)};             // modelo lineal en LOGARITMOS
        y[i] = std::log(medida);
    }
    Matriz A(3, Vector(3, 0.0));                            // ecuaciones normales
    Vector r(3, 0.0);
    for (int i = 0; i < n; ++i) for (int a = 0; a < 3; ++a) { r[a] += X[i][a] * y[i]; for (int b = 0; b < 3; ++b) A[a][b] += X[i][a] * X[i][b]; }
    Vector w = resolver(A, r);

    std::cout << "exponente de L  : " << w[1] << "   (teoria: 3)\n";
    std::cout << "exponente de P  : " << w[2] << "   (teoria: 1)\n";
    std::cout << "ordenada        : " << w[0] << "   (teoria: " << -std::log(3 * E * I) << ")\n";
    double L = 2.0, P = 1000.0;
    double pred = std::exp(w[0] + w[1] * std::log(L) + w[2] * std::log(P));
    std::cout << "flecha para L = 2 m, P = 1000 N:  modelo = " << pred * 1000 << " mm   exacta = " << flecha(L, P) * 1000 << " mm\n";
}
