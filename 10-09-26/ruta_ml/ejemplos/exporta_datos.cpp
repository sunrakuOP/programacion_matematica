#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

struct Punto { double x, y; int clase; };

void guardar(const std::string& ruta, const std::vector<Punto>& v) {
    std::ofstream f(ruta);
    f << "x1,x2,clase\n";
    for (const auto& p : v) f << p.x << "," << p.y << "," << p.clase << "\n";
}

int main() {
    std::mt19937 gen(5);                                    // los mismos datos que logistica.cpp
    std::normal_distribution<double> r(0, 1.0);
    auto datos = [&](int n) {
        std::vector<Punto> v;
        for (int i = 0; i < n; ++i) { int c = i % 2; double mu = c ? 1.2 : -1.2; v.push_back({mu + r(gen), mu + r(gen), c}); }
        return v;
    };
    auto train = datos(400), test = datos(400);
    guardar("train.csv", train);
    guardar("test.csv", test);

    double w1 = 0, w2 = 0, b = 0, lr = 0.1;
    auto sig = [](double z) { return 1.0 / (1.0 + std::exp(-z)); };
    for (int it = 0; it < 2000; ++it) {
        double g1 = 0, g2 = 0, gb = 0;
        for (const auto& p : train) { double e = sig(w1 * p.x + w2 * p.y + b) - p.clase; g1 += e * p.x; g2 += e * p.y; gb += e; }
        w1 -= lr * g1 / train.size(); w2 -= lr * g2 / train.size(); b -= lr * gb / train.size();
    }
    int ok = 0;
    for (const auto& p : test) ok += (sig(w1 * p.x + w2 * p.y + b) > 0.5) == p.clase;
    std::cout << "C++ (mi codigo):  w = (" << w1 << ", " << w2 << ")  b = " << b << "  exactitud test = " << double(ok) / test.size() << "\n";
}
