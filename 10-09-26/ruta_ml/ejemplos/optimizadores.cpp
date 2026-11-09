#include <iostream>
#include <cmath>
#include <string>

// f(x, y) = x^2 + 10 y^2   (un "valle" alargado: lo que mas cuesta a un gradiente simple)
void gradiente(double x, double y, double& gx, double& gy) { gx = 2 * x; gy = 20 * y; }
double f(double x, double y) { return x * x + 10 * y * y; }

int main() {
    const int MAX = 5000;
    for (std::string nombre : {"SGD", "momentum", "Adam"}) {
        double x = 5, y = 5, vx = 0, vy = 0, mx = 0, my = 0, sx = 0, sy = 0;
        int paso = 0;
        for (; paso < MAX && f(x, y) > 1e-8; ++paso) {
            double gx, gy;
            gradiente(x, y, gx, gy);
            if (nombre == "SGD") { x -= 0.09 * gx; y -= 0.09 * gy; }
            else if (nombre == "momentum") { vx = 0.9 * vx + gx; vy = 0.9 * vy + gy; x -= 0.01 * vx; y -= 0.01 * vy; }
            else {                                          // Adam
                double b1 = 0.9, b2 = 0.999, e = 1e-8, lr = 0.3, t = paso + 1;
                mx = b1 * mx + (1 - b1) * gx; my = b1 * my + (1 - b1) * gy;
                sx = b2 * sx + (1 - b2) * gx * gx; sy = b2 * sy + (1 - b2) * gy * gy;
                x -= lr * (mx / (1 - std::pow(b1, t))) / (std::sqrt(sx / (1 - std::pow(b2, t))) + e);
                y -= lr * (my / (1 - std::pow(b1, t))) / (std::sqrt(sy / (1 - std::pow(b2, t))) + e);
            }
        }
        std::cout << nombre << ":  " << paso << " pasos,  f final = " << f(x, y) << "\n";
    }
}
