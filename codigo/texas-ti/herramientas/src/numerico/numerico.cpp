#include "numerico.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

using std::cout;

static void cabecera(const char* a, const char* b, const char* c) {
    cout << std::setw(4) << a << std::setw(15) << b << std::setw(15) << c << "\n";
}
static void fila(int i, double a, double b) {
    cout << std::setw(4) << i << std::setw(15) << a << std::setw(15) << b << "\n";
}

// ================= Raices =================

Raiz biseccion(const Expr& f, double a, double b, double tol, int maxIter, bool traza) {
    Raiz r{0, 0, false};
    double fa = f.eval(a), fb = f.eval(b);
    // Sin cambio de signo no hay garantia de raiz en [a, b]
    if (!std::isfinite(fa) || !std::isfinite(fb) || fa * fb > 0) return r;
    if (traza) cabecera("it", "c", "error");
    for (int i = 1; i <= maxIter; ++i) {
        double c = (a + b) / 2;
        double fc = f.eval(c);
        double err = (b - a) / 2;
        if (traza) fila(i, c, err);
        r.x = c;
        r.iter = i;
        if (!std::isfinite(fc)) return r;
        if (fc == 0 || err < tol) { r.ok = true; return r; }
        if (fa * fc < 0) { b = c; fb = fc; }
        else             { a = c; fa = fc; }
    }
    return r;
}

Raiz newton(const Expr& f, double x, double tol, int maxIter, bool traza) {
    Raiz r{x, 0, false};
    if (traza) cabecera("it", "x", "error");
    for (int i = 1; i <= maxIter; ++i) {
        double fx = f.eval(x);
        double h = 1e-6 * std::fmax(1.0, std::fabs(x));
        double d = (f.eval(x + h) - f.eval(x - h)) / (2 * h);   // diferencia central
        if (!std::isfinite(fx) || !std::isfinite(d) || d == 0) return r;
        double xn = x - fx / d;
        double err = std::fabs(xn - x);
        if (traza) fila(i, xn, err);
        x = xn;
        r.x = x;
        r.iter = i;
        if (!std::isfinite(x)) return r;
        if (err < tol) { r.ok = true; return r; }
    }
    return r;
}

Raiz secante(const Expr& f, double x0, double x1, double tol, int maxIter, bool traza) {
    Raiz r{x1, 0, false};
    double f0 = f.eval(x0), f1 = f.eval(x1);
    if (traza) cabecera("it", "x", "error");
    for (int i = 1; i <= maxIter; ++i) {
        if (!std::isfinite(f0) || !std::isfinite(f1) || f1 == f0) return r;
        double x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        double err = std::fabs(x2 - x1);
        if (traza) fila(i, x2, err);
        x0 = x1; f0 = f1;
        x1 = x2; f1 = f.eval(x1);
        r.x = x1;
        r.iter = i;
        if (!std::isfinite(x1)) return r;
        if (err < tol) { r.ok = true; return r; }
    }
    return r;
}

// ================= Sistemas lineales =================

bool gauss(int n, const double A[MAXN][MAXN], const double b[MAXN], double x[MAXN]) {
    double M[MAXN][MAXN + 1];
    double escala = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            M[i][j] = A[i][j];
            if (std::fabs(A[i][j]) > escala) escala = std::fabs(A[i][j]);
        }
        M[i][n] = b[i];
    }
    for (int k = 0; k < n; ++k) {
        int p = k;   // pivote: la fila con mayor |M[i][k]|
        for (int i = k + 1; i < n; ++i)
            if (std::fabs(M[i][k]) > std::fabs(M[p][k])) p = i;
        if (std::fabs(M[p][k]) < 1e-12 * escala) return false;   // matriz singular
        if (p != k)
            for (int j = k; j <= n; ++j) { double t = M[k][j]; M[k][j] = M[p][j]; M[p][j] = t; }
        for (int i = k + 1; i < n; ++i) {
            double m = M[i][k] / M[k][k];
            for (int j = k; j <= n; ++j) M[i][j] -= m * M[k][j];
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        double s = M[i][n];
        for (int j = i + 1; j < n; ++j) s -= M[i][j] * x[j];
        x[i] = s / M[i][i];
    }
    return true;
}

Seidel gaussSeidel(int n, const double A[MAXN][MAXN], const double b[MAXN], double x[MAXN],
                   double tol, int maxIter) {
    Seidel r{0, false};
    for (int it = 1; it <= maxIter; ++it) {
        double err = 0;
        for (int i = 0; i < n; ++i) {
            if (std::fabs(A[i][i]) < 1e-12) return r;
            double s = b[i];
            for (int j = 0; j < n; ++j)
                if (j != i) s -= A[i][j] * x[j];
            double nuevo = s / A[i][i];
            if (!std::isfinite(nuevo)) return r;   // diverge
            err = std::fmax(err, std::fabs(nuevo - x[i]));
            x[i] = nuevo;
        }
        r.iter = it;
        if (err < tol) { r.ok = true; return r; }
    }
    return r;
}

// ================= Interpolacion y ajuste =================

double lagrange(int n, const double* xs, const double* ys, double x) {
    double suma = 0;
    for (int i = 0; i < n; ++i) {
        double L = 1;
        for (int j = 0; j < n; ++j)
            if (j != i) L *= (x - xs[j]) / (xs[i] - xs[j]);
        suma += ys[i] * L;
    }
    return suma;
}

double newtonInterp(int n, const double* xs, const double* ys, double x) {
    double c[MAXPTS];
    for (int i = 0; i < n; ++i) c[i] = ys[i];
    // c[k] queda como f[x0..xk], la diferencia dividida de orden k
    for (int k = 1; k < n; ++k)
        for (int i = n - 1; i >= k; --i)
            c[i] = (c[i] - c[i - 1]) / (xs[i] - xs[i - k]);
    double v = c[n - 1];   // Horner anidado
    for (int i = n - 2; i >= 0; --i) v = v * (x - xs[i]) + c[i];
    return v;
}

bool minimosCuadrados(int n, const double* xs, const double* ys, int grado, double* coef, double& r2) {
    int m = grado + 1;
    if (grado < 1 || m > MAXN || n < m) return false;
    // Ecuaciones normales: sum_j (sum x^(i+j)) c_j = sum y x^i
    double S[2 * MAXN], T[MAXN];
    for (int k = 0; k < 2 * m; ++k) S[k] = 0;
    for (int k = 0; k < m; ++k) T[k] = 0;
    for (int p = 0; p < n; ++p) {
        double pot = 1;
        for (int k = 0; k < 2 * m - 1; ++k) {
            S[k] += pot;
            if (k < m) T[k] += ys[p] * pot;
            pot *= xs[p];
        }
    }
    double A[MAXN][MAXN];
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j) A[i][j] = S[i + j];
    if (!gauss(m, A, T, coef)) return false;

    double media = 0;
    for (int p = 0; p < n; ++p) media += ys[p];
    media /= n;
    double sr = 0, st = 0;
    for (int p = 0; p < n; ++p) {
        double est = 0;
        for (int k = m - 1; k >= 0; --k) est = est * xs[p] + coef[k];
        sr += (ys[p] - est) * (ys[p] - est);
        st += (ys[p] - media) * (ys[p] - media);
    }
    r2 = (st == 0) ? 1.0 : 1.0 - sr / st;
    return true;
}

// ================= Integracion =================

double trapecio(const Expr& f, double a, double b, int n) {
    double h = (b - a) / n;
    double s = (f.eval(a) + f.eval(b)) / 2;
    for (int i = 1; i < n; ++i) s += f.eval(a + i * h);
    return s * h;
}

double simpson(const Expr& f, double a, double b, int n) {
    if (n % 2) ++n;
    double h = (b - a) / n;
    double s = f.eval(a) + f.eval(b);
    for (int i = 1; i < n; ++i) s += (i % 2 ? 4 : 2) * f.eval(a + i * h);
    return s * h / 3;
}

// ================= EDO =================

double rk4(const Expr& f, double x0, double y0, double xf, int pasos, bool traza) {
    double h = (xf - x0) / pasos;
    double x = x0, y = y0;
    int cada = pasos > 10 ? pasos / 10 : 1;   // la pantalla es chica: ~10 filas
    if (traza) {
        cabecera("pas", "x", "y");
        fila(0, x, y);
    }
    for (int i = 1; i <= pasos; ++i) {
        double k1 = f.eval(x, y);
        double k2 = f.eval(x + h / 2, y + h * k1 / 2);
        double k3 = f.eval(x + h / 2, y + h * k2 / 2);
        double k4 = f.eval(x + h, y + h * k3);
        y += h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        x = x0 + i * h;
        if (traza && (i % cada == 0 || i == pasos)) fila(i, x, y);
    }
    return y;
}
