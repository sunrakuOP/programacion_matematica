#include <iostream>
#include <vector>
#include <random>

int main() {
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> ux(0, 10);
    std::normal_distribution<double> ruido(0, 0.5);
    const int n = 200;
    std::vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) { x[i] = ux(gen); y[i] = 3.0 * x[i] + 2.0 + ruido(gen); }

    // (a) forma cerrada para y = w*x + b
    double sx = 0, sy = 0, sxx = 0, sxy = 0;
    for (int i = 0; i < n; ++i) { sx += x[i]; sy += y[i]; sxx += x[i] * x[i]; sxy += x[i] * y[i]; }
    double w = (n * sxy - sx * sy) / (n * sxx - sx * sx);
    double b = (sy - w * sx) / n;
    std::cout << "forma cerrada:     w = " << w << "  b = " << b << "\n";

    // (b) descenso por gradiente sobre el error cuadratico medio
    double wg = 0, bg = 0, lr = 0.01;
    for (int it = 1; it <= 20000; ++it) {
        double dw = 0, db = 0;
        for (int i = 0; i < n; ++i) {
            double e = wg * x[i] + bg - y[i];               // error de la prediccion
            dw += e * x[i];
            db += e;
        }
        wg -= lr * dw / n;
        bg -= lr * db / n;
        if (it == 100 || it == 1000 || it == 20000)
            std::cout << "descenso, iter " << it << ":  w = " << wg << "  b = " << bg << "\n";
    }
}
