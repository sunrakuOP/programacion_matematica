#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <cmath>

int main() {
    std::mt19937 gen(7);
    std::normal_distribution<double> alturas(170, 10), pesos(70, 15);
    const int n = 1000;
    std::vector<std::vector<double>> X(n, std::vector<double>(2));
    for (auto& fila : X) { fila[0] = alturas(gen); fila[1] = pesos(gen); }

    // 1) mezclar los indices y separar 80% / 20%  (ANTES de calcular estadisticas)
    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::shuffle(idx.begin(), idx.end(), gen);
    int nTrain = n * 8 / 10;

    // 2) media y desvio SOLO con el train
    double media[2] = {0, 0}, desvio[2] = {0, 0};
    for (int k = 0; k < nTrain; ++k) for (int j = 0; j < 2; ++j) media[j] += X[idx[k]][j] / nTrain;
    for (int k = 0; k < nTrain; ++k) for (int j = 0; j < 2; ++j) desvio[j] += std::pow(X[idx[k]][j] - media[j], 2) / nTrain;
    for (int j = 0; j < 2; ++j) desvio[j] = std::sqrt(desvio[j]);

    // 3) estandarizar todo con ESAS estadisticas
    for (auto& fila : X) for (int j = 0; j < 2; ++j) fila[j] = (fila[j] - media[j]) / desvio[j];

    double mTrain = 0, mTest = 0;
    for (int k = 0; k < nTrain; ++k) mTrain += X[idx[k]][0] / nTrain;
    for (int k = nTrain; k < n; ++k) mTest += X[idx[k]][0] / (n - nTrain);
    std::cout << "train = " << nTrain << "  test = " << n - nTrain << "\n";
    std::cout << "media de la altura estandarizada: train = " << mTrain << "  test = " << mTest << "\n";
}
