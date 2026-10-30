#pragma once

// Sistema de unidades activo. SI: m, m3/s, m2/s, g = 9.81. Ingles (como en la clase): ft, ft3/s, ft2/s,
// g = 32.2 ft/s2 y gc = 32.2 lbm.ft/(lbf.s2) para pasar a lbf. Todo el modulo trabaja con estos valores.
extern double G;          // gravedad
extern double GC;         // gc: dP = rho g hL / gc  (1 en SI)
extern double KMANNING;   // 1 en SI, 1.486 en ingles (Manning)
void fijarUnidades(bool ingles);

double haaland(double Re, double eD);

struct Friccion { double f; double f0; int iter; bool ok; };
// Re < 2300: laminar, f = 64/Re. Si no: semilla de Haaland y Colebrook por punto fijo.
Friccion factorFriccion(double Re, double eD, bool traza, double tol = 1e-10);

double perdidaDarcy(double f, double L, double D, double v);   // hf = f L/D v^2/2g

// f = Colebrook (valor "exacto" de referencia). fH = Haaland en el mismo Re y e/D.
// errRel = |fH - f| / f * 100 (%). hfH = perdida calculada con fH. Si es laminar (Re < 2300)
// Haaland no aplica: fH, errRel y hfH quedan en NaN.
struct Tuberia { double hf, Q, v, Re, f, fH, errRel, hfH; };
Tuberia tuberiaHf(double Q, double D, double L, double eps, double nu);       // dado el caudal
// dado hf: iteracion de la clase (diap. 33-34); con traza imprime la tabla f supuesta -> f corregida
bool    tuberiaQ(double hf, double D, double L, double eps, double nu, Tuberia& out,
                 bool traza = false, double f0 = 0.02, double tol = 1e-10);
// dado Q y hf, iterando D a partir de D0 (la de Swamee-Jain, por ejemplo). iter = vueltas dadas.
bool    tuberiaDiter(double Q, double hf, double L, double eps, double nu, double D0,
                     double& D, Tuberia& out, int& iter, bool traza);
bool    tuberiaD(double Q, double hf, double L, double eps, double nu, double& D, Tuberia& out);

// Ecuaciones explicitas de Swamee-Jain (sin iterar), una por cada tipo de problema de tuberia.
// Validas para 1e-6 < e/D < 1e-2 y Re entre ~3000 y 3e8 (hf), > 2000 (Q), 5000..3e8 (D).
double swameeHf(double Q, double D, double L, double eps, double nu);
double swameeQ(double hf, double D, double L, double eps, double nu);
double swameeD(double Q, double hf, double L, double eps, double nu);

// Canal trapezoidal (z = 0 es rectangular, b = 0 es triangular): profundidad normal por Manning.
struct Canal { double y, A, v, Fr; bool ok; };
double caudalManning(double y, double n, double S, double b, double z);
Canal  manning(double Q, double n, double S, double b, double z);
