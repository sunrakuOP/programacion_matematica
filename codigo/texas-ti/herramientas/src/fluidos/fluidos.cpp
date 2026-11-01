#include "fluidos.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

const double PI = 3.14159265358979323846;

double G = 9.81;
double GC = 1.0;
double KMANNING = 1.0;

void fijarUnidades(bool ingles) {
    G = ingles ? 32.2 : 9.81;
    GC = ingles ? 32.2 : 1.0;
    KMANNING = ingles ? 1.486 : 1.0;
}

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

double dDarcy(double f, double L, double Q, double hf) {
    return std::pow(8 * f * L * Q * Q / (PI * PI * G * hf), 0.2);
}

double qDarcy(double f, double D, double L, double hf, double& v) {
    v = std::sqrt(2 * G * D * hf / (f * L));
    return v * PI * D * D / 4;
}

// Agrega la comparacion Haaland vs Colebrook a una Tuberia que ya tiene v, Re y f.
static void compararHaaland(Tuberia& t, double L, double D, double eps) {
    if (t.Re < 2300) {   // laminar: Haaland no aplica
        t.fH = t.errRel = t.hfH = std::nan("");
        return;
    }
    t.fH = haaland(t.Re, eps / D);
    t.errRel = std::fabs(t.fH - t.f) / t.f * 100;
    t.hfH = perdidaDarcy(t.fH, L, D, t.v);
}

Tuberia tuberiaHf(double Q, double D, double L, double eps, double nu) {
    Tuberia t;
    t.Q = Q;
    t.v = 4 * Q / (PI * D * D);
    t.Re = t.v * D / nu;
    t.f = factorFriccion(t.Re, eps / D, false).f;
    t.hf = perdidaDarcy(t.f, L, D, t.v);
    compararHaaland(t, L, D, eps);
    return t;
}

// Helpers de tabla: numero fijo con ancho w y p decimales; al final se vuelve al formato general.
static void num(double x, int w, int p) {
    std::cout << std::fixed << std::setw(w) << std::setprecision(p) << x;
}
static void finTabla() {
    std::cout.unsetf(std::ios::floatfield);
    std::cout << std::setprecision(8) << "\n";
}

// Metodo 3 de la clase (diap. 33-34): se supone f, de hL = f (L/D) V^2/2g sale V, luego Re,
// y la f corregida sale de Colebrook. Se repite hasta que f deje de cambiar.
bool tuberiaQ(double hf, double D, double L, double eps, double nu, Tuberia& out,
              bool traza, double f0, double tol) {
    double f = f0;
    if (traza)
        std::cout << " it  f supuesta        V         Re  f corregida\n";
    for (int i = 0; i < 200; ++i) {
        double v = std::sqrt(2 * G * D * hf / (f * L));
        double Re = v * D / nu;
        double fn = factorFriccion(Re, eps / D, false).f;
        if (traza) {
            std::cout << std::setw(3) << i + 1;
            num(f, 12, 5);
            num(v, 9, 3);
            num(Re, 11, 0);
            num(fn, 12, 5);
            finTabla();
        }
        out.v = v;
        out.Re = Re;
        out.f = fn;
        if (std::fabs(fn - f) < tol) {
            out.hf = hf;
            out.Q = v * PI * D * D / 4;
            compararHaaland(out, L, D, eps);
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

// Enfoque iterativo de la clase para el tipo 3 (diap. 23 y 25). En cada vuelta D queda fijo:
// con el se calculan V, Re, e/D y f (Haaland de arranque, Colebrook hasta converger). Con ese f y la
// hL pedida se despeja D de Darcy (hL = f (L/D) V^2/2g, V = 4Q/(pi D^2)  ->  hL = 8 f L Q^2/(pi^2 g D^5)):
//     D nuevo = [ 8 f L Q^2 / (pi^2 g hL) ]^(1/5) = D * (hL calculada / hL pedida)^(1/5)
// Se repite con el D nuevo hasta que D deje de cambiar.
bool tuberiaDiter(double Q, double hf, double L, double eps, double nu, double D0,
                  double& D, Tuberia& out, int& iter, bool traza) {
    D = D0;
    iter = 0;
    if (traza)
        std::cout << " it         D       Re   f Haal   f Cole     D nuevo\n";
    while (iter < 100) {
        Tuberia t = tuberiaHf(Q, D, L, eps, nu);
        ++iter;
        // D nuevo: Darcy despejada para D con la f de Colebrook y la hL pedida
        double Dn = D * std::pow(t.hf / hf, 0.2);
        if (traza) {
            std::cout << std::setw(3) << iter;
            num(D, 10, 6);
            num(t.Re, 9, 0);
            num(t.fH, 9, 5);
            num(t.f, 9, 5);
            num(Dn, 12, 6);
            finTabla();
        }
        if (!std::isfinite(Dn) || Dn <= 0) return false;
        bool listo = std::fabs(Dn - D) / D < 1e-6;
        D = Dn;
        if (listo) {
            out = tuberiaHf(Q, D, L, eps, nu);
            return true;
        }
    }
    return false;
}

// 1.07 Q^2 L / (g D^5) * { ln[ e/(3.7 D) + 4.62 (nu D / Q)^0.9 ] }^-2
double swameeHf(double Q, double D, double L, double eps, double nu) {
    double t = std::log(eps / (3.7 * D) + 4.62 * std::pow(nu * D / Q, 0.9));
    return 1.07 * Q * Q * L / (G * std::pow(D, 5)) / (t * t);
}

// -0.965 (g D^5 hf / L)^0.5 * ln[ e/(3.7 D) + (3.17 nu^2 L / (g D^3 hf))^0.5 ]
double swameeQ(double hf, double D, double L, double eps, double nu) {
    return -0.965 * std::sqrt(G * std::pow(D, 5) * hf / L) *
           std::log(eps / (3.7 * D) + std::sqrt(3.17 * nu * nu * L / (G * std::pow(D, 3) * hf)));
}

// 0.66 [ e^1.25 (L Q^2 / (g hf))^4.75 + nu Q^9.4 (L / (g hf))^5.2 ]^0.04
double swameeD(double Q, double hf, double L, double eps, double nu) {
    double a = std::pow(eps, 1.25) * std::pow(L * Q * Q / (G * hf), 4.75);
    double b = nu * std::pow(Q, 9.4) * std::pow(L / (G * hf), 5.2);
    return 0.66 * std::pow(a + b, 0.04);
}

// Q = (1/n) A R^(2/3) S^(1/2), con A = y (b + z y), P = b + 2 y sqrt(1 + z^2)
double caudalManning(double y, double n, double S, double b, double z) {
    double A = y * (b + z * y);
    double P = b + 2 * y * std::sqrt(1 + z * z);
    return KMANNING * A * std::pow(A / P, 2.0 / 3.0) * std::sqrt(S) / n;
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
