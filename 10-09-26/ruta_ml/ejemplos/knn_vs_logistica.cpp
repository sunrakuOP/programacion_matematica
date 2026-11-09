#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "datos2d.hpp"

int main() {
    auto train = anillo(400, 1), test = anillo(400, 2);

    // --- regresion logistica (frontera RECTA)
    double w1 = 0, w2 = 0, b = 0;
    auto sig = [](double z) { return 1.0 / (1.0 + std::exp(-z)); };
    for (int it = 0; it < 3000; ++it) {
        double g1 = 0, g2 = 0, gb = 0;
        for (auto& p : train) { double e = sig(w1 * p.x + w2 * p.y + b) - p.clase; g1 += e * p.x; g2 += e * p.y; gb += e; }
        w1 -= 0.1 * g1 / train.size(); w2 -= 0.1 * g2 / train.size(); b -= 0.1 * gb / train.size();
    }
    int okLog = 0;
    for (auto& p : test) okLog += (sig(w1 * p.x + w2 * p.y + b) > 0.5) == p.clase;

    // --- k-NN por fuerza bruta: O(n) por consulta
    auto knn = [&](const Punto& q, int k) {
        std::vector<std::pair<double, int>> d;
        for (auto& p : train) d.push_back({(p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y), p.clase});
        std::partial_sort(d.begin(), d.begin() + k, d.end());
        int votos = 0;
        for (int i = 0; i < k; ++i) votos += d[i].second;
        return votos * 2 > k ? 1 : 0;
    };
    std::cout << "regresion logistica: exactitud = " << double(okLog) / test.size() << "\n";
    for (int k : {1, 5, 15, 51}) {
        int ok = 0;
        for (auto& p : test) ok += knn(p, k) == p.clase;
        std::cout << "k-NN con k = " << k << ":  exactitud = " << double(ok) / test.size() << "\n";
    }
}
