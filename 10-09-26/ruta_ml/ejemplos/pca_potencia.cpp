#include <iostream>
#include <vector>
#include <random>
#include <cmath>

int main() {
    std::mt19937 gen(8);
    std::normal_distribution<double> a(0, 3.0), b(0, 0.5);
    const int n = 1000;
    std::vector<double> X(n), Y(n);
    for (int i = 0; i < n; ++i) { double t = a(gen); X[i] = t + b(gen); Y[i] = 0.5 * t + b(gen); }   // datos alargados en una direccion

    double mx = 0, my = 0;
    for (int i = 0; i < n; ++i) { mx += X[i] / n; my += Y[i] / n; }
    double cxx = 0, cxy = 0, cyy = 0;                       // matriz de covarianza 2x2
    for (int i = 0; i < n; ++i) { cxx += (X[i] - mx) * (X[i] - mx); cxy += (X[i] - mx) * (Y[i] - my); cyy += (Y[i] - my) * (Y[i] - my); }
    cxx /= n - 1; cxy /= n - 1; cyy /= n - 1;

    double v[2] = {1, 0}, lambda = 0;                       // metodo de la potencia (el de Chapra, tema 3.4)
    for (int it = 0; it < 100; ++it) {
        double w0 = cxx * v[0] + cxy * v[1], w1 = cxy * v[0] + cyy * v[1];
        lambda = std::sqrt(w0 * w0 + w1 * w1);
        v[0] = w0 / lambda; v[1] = w1 / lambda;
    }
    double traza = cxx + cyy, lambda2 = traza - lambda;     // la traza es la suma de los autovalores
    std::cout << "covarianza: [" << cxx << " " << cxy << "; " << cxy << " " << cyy << "]\n";
    std::cout << "autovalor 1 = " << lambda << "  direccion = (" << v[0] << ", " << v[1] << ")\n";
    std::cout << "autovalor 2 = " << lambda2 << "\n";
    std::cout << "varianza explicada por la 1ra componente = " << lambda / traza << "\n";
}
