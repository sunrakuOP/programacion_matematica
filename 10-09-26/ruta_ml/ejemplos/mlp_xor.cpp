#include <iostream>
#include <vector>
#include <random>
#include <cmath>

const int H = 4;                                            // neuronas ocultas

int main() {
    std::mt19937 gen(1);
    std::normal_distribution<double> init(0, 0.8);
    double W1[H][2], b1[H], W2[H], b2 = 0;                  // capa 1: 2 -> H (tanh), capa 2: H -> 1 (sigmoide)
    for (int j = 0; j < H; ++j) { W1[j][0] = init(gen); W1[j][1] = init(gen); b1[j] = 0; W2[j] = init(gen); }

    double X[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    double T[4] = {0, 1, 1, 0};                             // XOR: ninguna recta lo separa
    auto sig = [](double z) { return 1.0 / (1.0 + std::exp(-z)); };
    double lr = 0.5;

    for (int epoca = 0; epoca <= 5000; ++epoca) {
        double perdida = 0, dW1[H][2] = {}, db1[H] = {}, dW2[H] = {}, db2 = 0;
        for (int n = 0; n < 4; ++n) {
            double h[H], z2 = b2;                           // ---- hacia adelante
            for (int j = 0; j < H; ++j) {
                h[j] = std::tanh(W1[j][0] * X[n][0] + W1[j][1] * X[n][1] + b1[j]);
                z2 += W2[j] * h[j];
            }
            double y = sig(z2);
            perdida += -(T[n] * std::log(y) + (1 - T[n]) * std::log(1 - y));
            double dz2 = y - T[n];                          // ---- hacia atras (regla de la cadena)
            db2 += dz2;
            for (int j = 0; j < H; ++j) {
                dW2[j] += dz2 * h[j];
                double dz1 = dz2 * W2[j] * (1 - h[j] * h[j]);      // d tanh = 1 - tanh^2
                dW1[j][0] += dz1 * X[n][0]; dW1[j][1] += dz1 * X[n][1]; db1[j] += dz1;
            }
        }
        for (int j = 0; j < H; ++j) { W2[j] -= lr * dW2[j] / 4; b1[j] -= lr * db1[j] / 4; W1[j][0] -= lr * dW1[j][0] / 4; W1[j][1] -= lr * dW1[j][1] / 4; }
        b2 -= lr * db2 / 4;
        if (epoca % 1000 == 0) std::cout << "epoca " << epoca << "   perdida = " << perdida / 4 << "\n";
    }
    for (int n = 0; n < 4; ++n) {
        double z2 = b2;
        for (int j = 0; j < H; ++j) z2 += W2[j] * std::tanh(W1[j][0] * X[n][0] + W1[j][1] * X[n][1] + b1[j]);
        std::cout << X[n][0] << " XOR " << X[n][1] << " -> " << sig(z2) << "   (esperado " << T[n] << ")\n";
    }
}
