#pragma once

// Todo en SI: m, m3/s, m2/s (viscosidad cinematica), m/s.
const double G = 9.81;

double haaland(double Re, double eD);

struct Friccion { double f; double f0; int iter; bool ok; };
// Re < 2300: laminar, f = 64/Re. Si no: semilla de Haaland y Colebrook por punto fijo.
Friccion factorFriccion(double Re, double eD, bool traza, double tol = 1e-10);

double perdidaDarcy(double f, double L, double D, double v);   // hf = f L/D v^2/2g

struct Tuberia { double hf, Q, v, Re, f; };
Tuberia tuberiaHf(double Q, double D, double L, double eps, double nu);       // dado el caudal
bool    tuberiaQ(double hf, double D, double L, double eps, double nu, Tuberia& out);   // dado hf
bool    tuberiaD(double Q, double hf, double L, double eps, double nu, double& D, Tuberia& out);

// Canal trapezoidal (z = 0 es rectangular, b = 0 es triangular): profundidad normal por Manning.
struct Canal { double y, A, v, Fr; bool ok; };
double caudalManning(double y, double n, double S, double b, double z);
Canal  manning(double Q, double n, double S, double b, double z);
