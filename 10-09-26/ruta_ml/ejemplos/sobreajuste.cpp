#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <utility>

using Matriz = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

Vector resolver(Matriz A, Vector b) {                       // Gauss con pivoteo parcial
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

// ajusta un polinomio de grado d con penalizacion ridge lambda:  (X^T X + lambda I) w = X^T y
Vector ajustar(const Vector& x, const Vector& y, int d, double lambda) {
    int m = d + 1, n = x.size();
    Matriz A(m, Vector(m, 0.0));
    Vector r(m, 0.0);
    for (int i = 0; i < n; ++i)
        for (int a = 0; a < m; ++a) {
            r[a] += std::pow(x[i], a) * y[i];
            for (int b = 0; b < m; ++b) A[a][b] += std::pow(x[i], a + b);
        }
    for (int a = 0; a < m; ++a) A[a][a] += lambda;
    return resolver(A, r);
}

double rmse(const Vector& w, const Vector& x, const Vector& y) {
    double s = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        double p = 0;
        for (size_t a = 0; a < w.size(); ++a) p += w[a] * std::pow(x[i], a);
        s += (p - y[i]) * (p - y[i]);
    }
    return std::sqrt(s / x.size());
}

int main() {
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> ux(0, 1);
    std::normal_distribution<double> ruido(0, 0.2);
    auto verdad = [](double x) { return std::sin(2 * M_PI * x); };

    Vector xt(12), yt(12), xs(300), ys(300);
    for (int i = 0; i < 12; ++i) { xt[i] = ux(gen); yt[i] = verdad(xt[i]) + ruido(gen); }
    for (int i = 0; i < 300; ++i) { xs[i] = ux(gen); ys[i] = verdad(xs[i]) + ruido(gen); }

    std::cout << "grado   error train   error test\n";
    for (int d : {1, 3, 9}) {
        Vector w = ajustar(xt, yt, d, 0.0);
        std::cout << "  " << d << "       " << rmse(w, xt, yt) << "         " << rmse(w, xs, ys) << "\n";
    }
    std::cout << "\ngrado 9 con ridge:\nlambda    error train   error test\n";
    for (double lam : {0.0, 1e-6, 1e-3, 1e-1}) {
        Vector w = ajustar(xt, yt, 9, lam);
        std::cout << lam << "      " << rmse(w, xt, yt) << "         " << rmse(w, xs, ys) << "\n";
    }
}
