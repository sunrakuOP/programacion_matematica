#include <iostream>
#include "io.hpp"
#include "numerico.hpp"

using std::cout;

static void ayudaFuncion() {
    cout << "Escribe sin espacios. Ej: x^3-x-2\n"
         << "sin cos tan exp ln log sqrt abs pi e\n";
}

static void mostrarRaiz(const Raiz& r) {
    cout << (r.ok ? "raiz = " : "NO convergio, ultimo x = ") << r.x << "\n";
    cout << "iteraciones: " << r.iter << "\n";
}

static void opRaices(int metodo) {
    ayudaFuncion();
    Expr f = leerFuncion("f(x)= ");
    bool traza = leerEntero("Ver iteraciones? (1=si 0=no): ", 0, 1) == 1;
    double tol = leerNum("Tolerancia (ej 1e-8): ");
    if (tol <= 0) { cout << "Tolerancia debe ser > 0\n"; return; }
    if (metodo == 1) {
        double a = leerNum("a: "), b = leerNum("b: ");
        Raiz r = biseccion(f, a, b, tol, 200, traza);
        if (!r.ok && r.iter == 0) { cout << "f(a) y f(b) deben tener signo distinto\n"; return; }
        mostrarRaiz(r);
    } else if (metodo == 2) {
        double x0 = leerNum("x0: ");
        mostrarRaiz(newton(f, x0, tol, 100, traza));
    } else {
        double x0 = leerNum("x0: "), x1 = leerNum("x1: ");
        mostrarRaiz(secante(f, x0, x1, tol, 100, traza));
    }
}

static int leerSistema(double A[MAXN][MAXN], double b[MAXN]) {
    int n = leerEntero("Numero de incognitas (2 a 10): ", 2, MAXN);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "A(" << i + 1 << "," << j + 1 << ")";
            A[i][j] = leerNum(" = ");
        }
        cout << "b(" << i + 1 << ")";
        b[i] = leerNum(" = ");
    }
    return n;
}

static void imprimirSolucion(int n, const double* x) {
    for (int i = 0; i < n; ++i) cout << "x" << i + 1 << " = " << x[i] << "\n";
}

static void opGauss() {
    double A[MAXN][MAXN], b[MAXN], x[MAXN];
    int n = leerSistema(A, b);
    if (!gauss(n, A, b, x)) { cout << "Matriz singular: sin solucion unica\n"; return; }
    imprimirSolucion(n, x);
}

static void opSeidel() {
    double A[MAXN][MAXN], b[MAXN], x[MAXN];
    int n = leerSistema(A, b);
    double tol = leerNum("Tolerancia (ej 1e-8): ");
    for (int i = 0; i < n; ++i) x[i] = 0;   // estimado inicial: ceros
    Seidel r = gaussSeidel(n, A, b, x, tol, 1000);
    if (!r.ok) { cout << "No convergio (revisa dominancia diagonal)\n"; return; }
    cout << "iteraciones: " << r.iter << "\n";
    imprimirSolucion(n, x);
}

static int leerTabla(double* xs, double* ys) {
    int n = leerEntero("Numero de puntos (2 a 20): ", 2, MAXPTS);
    for (int i = 0; i < n; ++i) {
        cout << "x" << i + 1;
        xs[i] = leerNum(" = ");
        cout << "y" << i + 1;
        ys[i] = leerNum(" = ");
    }
    return n;
}

static void opInterpolacion() {
    double xs[MAXPTS], ys[MAXPTS];
    int n = leerTabla(xs, ys);
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (xs[i] == xs[j]) { cout << "Hay x repetidos\n"; return; }
    double x = leerNum("x a interpolar: ");
    cout << "Lagrange: " << lagrange(n, xs, ys, x) << "\n";
    cout << "Newton:   " << newtonInterp(n, xs, ys, x) << "\n";
}

static void opMinimosCuadrados() {
    double xs[MAXPTS], ys[MAXPTS], coef[MAXN], r2;
    int n = leerTabla(xs, ys);
    int grado = leerEntero("Grado del polinomio (1 a 5): ", 1, 5);
    if (!minimosCuadrados(n, xs, ys, grado, coef, r2)) {
        cout << "Faltan puntos (n > grado) o el sistema es singular\n";
        return;
    }
    for (int k = 0; k <= grado; ++k) cout << "c" << k << " = " << coef[k] << "\n";
    cout << "R2 = " << r2 << "\n(y = c0 + c1 x + c2 x^2 + ...)\n";
}

static void opIntegral() {
    ayudaFuncion();
    Expr f = leerFuncion("f(x)= ");
    double a = leerNum("a: "), b = leerNum("b: ");
    int n = leerEntero("Subintervalos n: ", 1, 100000);
    cout << "Trapecio: " << trapecio(f, a, b, n) << "\n";
    cout << "Simpson 1/3: " << simpson(f, a, b, n) << (n % 2 ? "  (n -> n+1)\n" : "\n");
}

static void opRK4() {
    cout << "Resuelve y' = f(x,y)\n";
    ayudaFuncion();
    Expr f = leerFuncion("f(x,y)= ");
    double x0 = leerNum("x0: "), y0 = leerNum("y0: "), xf = leerNum("x final: ");
    int pasos = leerEntero("Numero de pasos: ", 1, 100000);
    double y = rk4(f, x0, y0, xf, pasos, true);
    cout << "y(" << xf << ") = " << y << "\n";
}

void menuNumerico() {
    int op;
    do {
        cout << "\n--- METODOS NUMERICOS ---\n"
             << "1. Biseccion\n"
             << "2. Newton-Raphson\n"
             << "3. Secante\n"
             << "4. Gauss (pivoteo)\n"
             << "5. Gauss-Seidel\n"
             << "6. Interpolacion (Lagrange/Newton)\n"
             << "7. Minimos cuadrados\n"
             << "8. Integral (trapecio/Simpson)\n"
             << "9. EDO Runge-Kutta 4\n"
             << "0. Salir\n";
        op = leerEntero("Opcion: ", 0, 9);
        switch (op) {
            case 1: opRaices(1); break;
            case 2: opRaices(2); break;
            case 3: opRaices(3); break;
            case 4: opGauss(); break;
            case 5: opSeidel(); break;
            case 6: opInterpolacion(); break;
            case 7: opMinimosCuadrados(); break;
            case 8: opIntegral(); break;
            case 9: opRK4(); break;
            default: break;
        }
    } while (op != 0);
}
