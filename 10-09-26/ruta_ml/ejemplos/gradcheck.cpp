#include <iostream>
#include <cmath>
#include <functional>
#include <vector>

// f(x, y) = x^2 * y + sin(y)
double f(double x, double y) { return x * x * y + std::sin(y); }

int main() {
    double x = 1.5, y = 0.8;
    // gradiente analitico (a mano): df/dx = 2xy ; df/dy = x^2 + cos(y)
    double gx = 2 * x * y, gy = x * x + std::cos(y);

    // gradiente numerico: diferencia central
    for (double h : {1e-1, 1e-3, 1e-5, 1e-8}) {
        double nx = (f(x + h, y) - f(x - h, y)) / (2 * h);
        double ny = (f(x, y + h) - f(x, y - h)) / (2 * h);
        double err = std::sqrt((nx - gx) * (nx - gx) + (ny - gy) * (ny - gy)) /
                     std::sqrt(gx * gx + gy * gy);
        std::cout << "h = " << h << "   error relativo = " << err << "\n";
    }
    std::cout << "analitico: (" << gx << ", " << gy << ")\n";
}
