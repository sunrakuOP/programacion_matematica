#pragma once
#include <vector>
#include <random>
#include <cmath>
struct Punto { double x, y; int clase; };
// clase 0: disco de radio ~1.5 en el centro; clase 1: anillo de radio 2.5 a 4
inline std::vector<Punto> anillo(int n, unsigned semilla) {
    std::mt19937 g(semilla);
    std::uniform_real_distribution<double> ang(0, 2 * M_PI), r0(0, 1.5), r1(2.5, 4.0);
    std::vector<Punto> v;
    for (int i = 0; i < n; ++i) {
        double a = ang(g);
        int c = i % 2;
        double r = c == 0 ? r0(g) : r1(g);
        v.push_back({r * std::cos(a), r * std::sin(a), c});
    }
    return v;
}
