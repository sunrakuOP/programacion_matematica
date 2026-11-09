#include <iostream>
#include <vector>
#include <random>
#include <cmath>

struct Punto { double x, y; int clase; };

int main() {
    std::mt19937 gen(5);
    std::normal_distribution<double> r(0, 1.0);
    auto datos = [&](int n) {
        std::vector<Punto> v;
        for (int i = 0; i < n; ++i) { int c = i % 2; double mu = c ? 1.2 : -1.2; v.push_back({mu + r(gen), mu + r(gen), c}); }
        return v;
    };
    auto train = datos(400), test = datos(400);

    double w1 = 0, w2 = 0, b = 0, lr = 0.1;
    auto sigmoide = [](double z) { return 1.0 / (1.0 + std::exp(-z)); };
    for (int it = 0; it < 2000; ++it) {
        double g1 = 0, g2 = 0, gb = 0;
        for (const auto& p : train) {
            double e = sigmoide(w1 * p.x + w2 * p.y + b) - p.clase;   // (prediccion - real)
            g1 += e * p.x; g2 += e * p.y; gb += e;
        }
        int n = train.size();
        w1 -= lr * g1 / n; w2 -= lr * g2 / n; b -= lr * gb / n;
    }

    int tp = 0, fp = 0, fn = 0, tn = 0;
    for (const auto& p : test) {
        int pred = sigmoide(w1 * p.x + w2 * p.y + b) > 0.5;
        if (pred && p.clase) ++tp; else if (pred && !p.clase) ++fp; else if (!pred && p.clase) ++fn; else ++tn;
    }
    double prec = double(tp) / (tp + fp), rec = double(tp) / (tp + fn);
    std::cout << "w = (" << w1 << ", " << w2 << ")  b = " << b << "\n";
    std::cout << "matriz de confusion (test):  TP=" << tp << " FP=" << fp << " FN=" << fn << " TN=" << tn << "\n";
    std::cout << "exactitud = " << double(tp + tn) / test.size() << "  precision = " << prec << "  recall = " << rec
              << "  F1 = " << 2 * prec * rec / (prec + rec) << "\n";
}
