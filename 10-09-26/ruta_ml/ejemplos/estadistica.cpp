#include <iostream>
#include <vector>
#include <random>
#include <cmath>

int main() {
    std::mt19937 gen(42);                                   // semilla fija: reproducible
    std::normal_distribution<double> normal(10.0, 2.0);     // media 10, desvío 2
    const int n = 100000;
    std::vector<double> v(n);
    for (double& x : v) x = normal(gen);

    double suma = 0;
    for (double x : v) suma += x;
    double media = suma / n;

    double ss = 0;
    for (double x : v) ss += (x - media) * (x - media);
    double varianza = ss / (n - 1);                         // muestral: n-1

    int dentro = 0;
    for (double x : v) if (std::fabs(x - media) < std::sqrt(varianza)) ++dentro;

    std::cout << "media     = " << media << "   (teorica 10)\n";
    std::cout << "varianza  = " << varianza << "   (teorica 4)\n";
    std::cout << "dentro de 1 desvio = " << double(dentro) / n << "   (teorico 0.6827)\n";
}
