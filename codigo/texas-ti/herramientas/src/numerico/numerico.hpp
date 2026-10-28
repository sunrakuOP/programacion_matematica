#pragma once
#include "expr.hpp"

// Tamanos fijos: en la calculadora no hay memoria para sobrar y evitamos std::vector.
const int MAXN   = 10;   // incognitas maximas en sistemas lineales
const int MAXPTS = 20;   // puntos maximos de una tabla de datos

// ---- Raices de f(x) = 0 ----
struct Raiz { double x; int iter; bool ok; };
Raiz biseccion(const Expr& f, double a, double b, double tol, int maxIter, bool traza);
Raiz newton(const Expr& f, double x0, double tol, int maxIter, bool traza);   // derivada numerica
Raiz secante(const Expr& f, double x0, double x1, double tol, int maxIter, bool traza);

// ---- Sistemas lineales A x = b ----
bool gauss(int n, const double A[MAXN][MAXN], const double b[MAXN], double x[MAXN]);   // pivoteo parcial
struct Seidel { int iter; bool ok; };
Seidel gaussSeidel(int n, const double A[MAXN][MAXN], const double b[MAXN], double x[MAXN],
                   double tol, int maxIter);   // x entra como estimado inicial y sale como resultado

// ---- Interpolacion y ajuste de datos ----
double lagrange(int n, const double* xs, const double* ys, double x);
double newtonInterp(int n, const double* xs, const double* ys, double x);   // diferencias divididas
// Ajusta un polinomio de grado `grado`: coef[0] + coef[1] x + ... ; r2 = coeficiente de determinacion.
bool minimosCuadrados(int n, const double* xs, const double* ys, int grado, double* coef, double& r2);

// ---- Integracion ----
double trapecio(const Expr& f, double a, double b, int n);
double simpson(const Expr& f, double a, double b, int n);   // n se sube a par si es impar

// ---- EDO y' = f(x, y), Runge-Kutta de 4to orden ----
double rk4(const Expr& f, double x0, double y0, double xf, int pasos, bool traza);
