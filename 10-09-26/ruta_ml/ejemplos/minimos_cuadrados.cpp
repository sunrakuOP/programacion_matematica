#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <utility>

using Matriz = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

// Gauss con pivoteo parcial (el de Chapra, ahora con el intercambio de filas)
Vector resolver(Matriz A, Vector b) {
    int n = A.size();
    for (int c = 0; c < n; ++c) {
        int p = c;
        for (int f = c + 1; f < n; ++f) if (std::fabs(A[f][c]) > std::fabs(A[p][c])) p = f;
        std::swap(A[c], A[p]); std::swap(b[c], b[p]);
        for (int f = c + 1; f < n; ++f) {
            double m = A[f][c] / A[c][c];
            for (int k = c; k < n; ++k) A[f][k] -= m * A[c][k];
            b[f] -= m * b[c];
        }
    }
    Vector x(n);
    for (int i = n - 1; i >= 0; --i) {
        double s = b[i];
        for (int j = i + 1; j < n; ++j) s -= A[i][j] * x[j];
        x[i] = s / A[i][i];
    }
    return x;
}

int main() {
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> ux(0, 10);
    std::normal_distribution<double> ruido(0, 0.5);

    int n = 200;
    Matriz X(n, Vector(2));                                 // matriz de diseno: columna de 1 y columna de x
    Vector y(n);
    for (int i = 0; i < n; ++i) { double x = ux(gen); X[i] = {1.0, x}; y[i] = 3.0 * x + 2.0 + ruido(gen); }

    // ecuaciones normales:  (X^T X) w = X^T y
    Matriz XtX(2, Vector(2, 0.0));
    Vector Xty(2, 0.0);
    for (int i = 0; i < n; ++i)
        for (int a = 0; a < 2; ++a) {
            Xty[a] += X[i][a] * y[i];
            for (int b = 0; b < 2; ++b) XtX[a][b] += X[i][a] * X[i][b];
        }
    Vector w = resolver(XtX, Xty);
    std::cout << "ordenada = " << w[0] << "  (real 2)    pendiente = " << w[1] << "  (real 3)\n";
}
