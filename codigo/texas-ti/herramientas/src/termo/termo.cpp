#include "termo.hpp"
#include <cmath>

double interpLineal(double x1, double y1, double x2, double y2, double x) {
    if (x1 == x2) return std::nan("");
    return y1 + (y2 - y1) * (x - x1) / (x2 - x1);
}

double propMezcla(double f, double g, double x) {
    return f + x * (g - f);
}

double calidad(double prop, double f, double g) {
    if (f == g) return std::nan("");
    return (prop - f) / (g - f);
}

double bilineal(double x1, double x2, double y1, double y2,
                double q11, double q21, double q12, double q22,
                double x, double y) {
    // primero en x sobre cada fila y, despues en y entre los dos resultados
    double a = interpLineal(x1, q11, x2, q21, x);
    double b = interpLineal(x1, q12, x2, q22, x);
    return interpLineal(y1, a, y2, b, y);
}
