#include "fluidos.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

const double PI = 3.14159265358979323846;

// 1/sqrt(f) = -1.8 log10[ (e/D / 3.7)^1.11 + 6.9/Re ]
double haaland(double Re, double eD) {
    double x = -1.8 * std::log10(std::pow(eD / 3.7, 1.11) + 6.9 / Re);
    return 1.0 / (x * x);
}

Friccion factorFriccion(double Re, double eD, bool traza, double tol) {
    Friccion r{0, 0, 0, false};
    if (Re < 2300) {   // laminar: Colebrook no aplica
        r.f = r.f0 = 64.0 / Re;
        r.ok = true;
        return r;
    }
    double f = haaland(Re, eD);
    r.f0 = f;
    double err = 1;
    if (traza)
        std::cout << std::setw(4) << "it" << std::setw(15) << "f" << std::setw(15) << "error" << "\n";
    // 1/sqrt(f) = -2 log10( (e/D)/3.7 + 2.51/(Re sqrt(f)) )
    while (err > tol && r.iter < 100) {
        double inv = -2.0 * std::log10(eD / 3.7 + 2.51 / (Re * std::sqrt(f)));
        double fn = 1.0 / (inv * inv);
        err = std::fabs(fn - f);
        f = fn;
        ++r.iter;
        if (traza)
            std::cout << std::setw(4) << r.iter << std::setw(15) << f << std::setw(15) << err << "\n";
    }
    r.f = f;
    r.ok = err <= tol;
    return r;
}

double perdidaDarcy(double f, double L, double D, double v) {
    return f * (L / D) * v * v / (2 * G);
}

Tuberia tuberiaHf(double Q, double D, double L, double eps, double nu) {
    Tuberia t;
    t.Q = Q;
    t.v = 4 * Q / (PI * D * D);
    t.Re = t.v * D / nu;
    t.f = factorFriccion(t.Re, eps / D, false).f;
    t.hf = perdidaDarcy(t.f, L, D, t.v);
    return t;
}

// f depende de v y v depende de f: se itera hasta que f deje de cambiar.
bool tuberiaQ(double hf, double D, double L, double eps, double nu, Tuberia& out) {
    double f = 0.02;
    for (int i = 0; i < 200; ++i) {
        double v = std::sqrt(2 * G * D * hf / (f * L));
        double Re = v * D / nu;
        double fn = factorFriccion(Re, eps / D, false).f;
        out.v = v;
        out.Re = Re;
        out.f = fn;
        if (std::fabs(fn - f) < 1e-10) {
            out.hf = hf;
            out.Q = v * PI * D * D / 4;
            return true;
        }
        f = fn;
    }
    return false;
}

// hf baja al crecer D, asi que hay una sola raiz: biseccion sobre D.
bool tuberiaD(double Q, double hf, double L, double eps, double nu, double& D, Tuberia& out) {
    double lo = 1e-4, hi = 10;
    if (tuberiaHf(Q, lo, L, eps, nu).hf < hf) return false;   // ni el tubo mas fino pierde tanto
    if (tuberiaHf(Q, hi, L, eps, nu).hf > hf) return false;   // ni 10 m alcanza
    for (int i = 0; i < 200; ++i) {
        double mid = (lo + hi) / 2;
        if (tuberiaHf(Q, mid, L, eps, nu).hf > hf) lo = mid;
        else hi = mid;
    }
    D = (lo + hi) / 2;
    out = tuberiaHf(Q, D, L, eps, nu);
    return true;
}

// Q = (1/n) A R^(2/3) S^(1/2), con A = y (b + z y), P = b + 2 y sqrt(1 + z^2)
double caudalManning(double y, double n, double S, double b, double z) {
    double A = y * (b + z * y);
    double P = b + 2 * y * std::sqrt(1 + z * z);
    return A * std::pow(A / P, 2.0 / 3.0) * std::sqrt(S) / n;
}

Canal manning(double Q, double n, double S, double b, double z) {
    Canal c{0, 0, 0, 0, false};
    double lo = 0, hi = 1;
    while (caudalManning(hi, n, S, b, z) < Q) {   // Q crece con y: buscamos un tope
        hi *= 2;
        if (hi > 1e5) return c;
    }
    for (int i = 0; i < 200; ++i) {
        double mid = (lo + hi) / 2;
        if (caudalManning(mid, n, S, b, z) < Q) lo = mid;
        else hi = mid;
    }
    c.y = (lo + hi) / 2;
    c.A = c.y * (b + z * c.y);
    c.v = Q / c.A;
    double T = b + 2 * z * c.y;   // ancho superficial
    c.Fr = c.v / std::sqrt(G * c.A / T);
    c.ok = true;
    return c;
}
