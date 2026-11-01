#include <cmath>
#include <iostream>
#include <string>
#include "fluidos.hpp"
#include "io.hpp"

using std::cout;
using std::string;

static const double PI = 3.14159265358979323846;

// ---------------------------------------------------------------- sistema de unidades
struct Unid {
    const char *L, *Q, *nu, *mu, *rho, *nombre;
};
static const Unid SI = {"m", "m3/s", "m2/s", "Pa.s", "kg/m3", "Internacional (SI)"};
static const Unid ING = {"ft", "ft3/s", "ft2/s", "lbm/ft.s", "lbm/ft3", "Ingles"};
static const Unid* U = &SI;
static bool ingles = false;

static string vel() { return string(U->L) + "/s"; }

// "nombre (unidad): "
static double pedir(const char* nombre, const string& unidad) {
    return leerNum((string(nombre) + " (" + unidad + "): ").c_str());
}

static void elegirUnidades() {
    cout << "\nSistema de unidades:\n1. Internacional (m, kg)\n2. Ingles (ft, lbm)\n";
    ingles = leerEntero("Opcion: ", 1, 2) == 2;
    U = ingles ? &ING : &SI;
    fijarUnidades(ingles);
    cout << "Unidades: " << U->nombre << "  (g = " << G << ")\n";
}

// Pide nu directo o, con 0, mu y rho (nu = mu/rho, equivalente a Re = rho V D / mu de la clase).
// Devuelve rho, o 0 si no se dio. nu queda <= 0 si los datos son invalidos.
static double leerFluido(double& nu) {
    nu = pedir("nu, o 0 para dar mu y rho", U->nu);
    if (nu != 0) return 0;
    double mu = pedir("mu", U->mu), rho = pedir("rho", U->rho);
    if (mu <= 0 || rho <= 0) { nu = -1; return 0; }
    nu = mu / rho;
    cout << "nu = " << nu << " " << U->nu << "\n";
    return rho;
}

// Las ecuaciones de Swamee-Jain declaran: 1e-6 < e/D < 1e-2 y un Re minimo segun el problema.
static void avisoExplicita(double eps, double D, double Re, double reMin) {
    double eD = eps / D;
    if ((eps > 0 && (eD < 1e-6 || eD > 1e-2)) || Re < reMin || Re > 3e8)
        cout << "Aviso: fuera del rango de Swamee-Jain\n";
}

// Regimen segun la clase (diap. 3): Re <= 2300 laminar, hasta 4000 transicion, mas turbulento.
static void mostrarRegimen(double Re) {
    cout << "Re = " << Re << (Re <= 2300 ? "  (laminar)\n" : Re < 4000 ? "  (transicion)\n" : "  (turbulento)\n");
}

// e/D, f de Haaland, f de Colebrook (con numero de iteraciones) y el error entre ambas.
// traza = true muestra tambien cada iteracion de Colebrook.
static void mostrarFriccion(double Re, double eD, bool traza = false) {
    cout << "e/D = " << eD << "\n";
    if (Re < 2300) {   // laminar: f = 64/Re (diap. 7 y 10), Haaland y Colebrook no aplican
        cout << "Laminar: f = 64/Re = " << 64.0 / Re << "\n";
        return;
    }
    Friccion r = factorFriccion(Re, eD, traza, 1e-8);
    cout << "f Haaland   = " << r.f0 << "\n"
         << "f Colebrook = " << r.f << "  (" << r.iter << " iteraciones)\n"
         << "Error H vs C = " << std::fabs(r.f0 - r.f) / r.f * 100 << " %  (|dif| = "
         << std::fabs(r.f0 - r.f) << ")\n";
}

// dP = rho g hL / gc  y  potencia = Q dP  (diap. 19), solo si se dio rho.
static void mostrarPresion(double rho, double hL, double Q) {
    if (rho <= 0) return;
    double dP = rho * G * hL / GC;
    if (!ingles) {
        cout << "dP = " << dP << " Pa\nPotencia Q*dP = " << Q * dP << " W\n";
    } else {   // lbf/ft2 -> psi (/144); lbf.ft/s -> W (x 1.355818)
        cout << "dP = " << dP << " lbf/ft2 = " << dP / 144 << " psi\n"
             << "Potencia Q*dP = " << Q * dP * 1.355818 << " W\n";
    }
}

// ---------------------------------------------------------------- opcion 1
// Pide lo necesario para llegar a Re (segun el dato que traiga el problema) y de ahi saca e/D,
// f Haaland, f Colebrook y el error. V = Q/(pi D^2/4), Re = V D / nu = rho V D / mu.
static void opFriccion() {
    cout << "\nFACTOR DE FRICCION f\nQue datos tienes?\n"
         << "1. Q y D\n2. V y D\n3. Re y D\n";
    int v = leerEntero("Opcion: ", 1, 3);
    double Q = 0, V = 0, Re = 0, nu = 1, rho = 0;
    double D;
    if (v == 1) {
        Q = pedir("Q", U->Q);
        D = pedir("D", U->L);
    } else if (v == 2) {
        V = pedir("V", vel());
        D = pedir("D", U->L);
    } else {
        Re = leerNum("Re: ");
        D = pedir("D", U->L);
    }
    double eps = pedir("Rugosidad e (0 si liso)", U->L);
    if (v != 3) rho = leerFluido(nu);   // para Re hace falta la viscosidad
    if (D <= 0 || eps < 0 || (v == 1 && Q <= 0) || (v == 2 && V <= 0) || (v == 3 && Re <= 0) ||
        (v != 3 && nu <= 0)) {
        cout << "Datos invalidos\n";
        return;
    }
    bool traza = leerEntero("Ver iteraciones? (1=si 0=no): ", 0, 1) == 1;
    cout << "\n";
    if (v == 1) {
        V = 4 * Q / (PI * D * D);
        cout << "V = Q/(pi D^2/4) = " << V << " " << vel() << "\n";
    }
    if (v != 3) {
        Re = V * D / nu;
        cout << (rho > 0 ? "Re = rho V D / mu\n" : "Re = V D / nu\n");
    }
    mostrarRegimen(Re);
    mostrarFriccion(Re, eps / D, traza);
}

// ---------------------------------------------------------------- opcion 2: tipo 1
static void opTipo1() {
    cout << "\nTIPO 1: perdida hL (dado Q)\nDatos: Q, D, L, e\n";
    double Q = pedir("Q", U->Q), D = pedir("D", U->L), L = pedir("L", U->L);
    double eps = pedir("e (0 si liso)", U->L);
    double nu, rho = leerFluido(nu);
    if (Q <= 0 || D <= 0 || L <= 0 || eps < 0 || nu <= 0) { cout << "Datos invalidos\n"; return; }
    Tuberia t = tuberiaHf(Q, D, L, eps, nu);
    cout << "\nV = " << t.v << " " << vel() << "\n";
    mostrarRegimen(t.Re);
    mostrarFriccion(t.Re, eps / D);
    cout << "hL = " << t.hf << " " << U->L << "  (f Colebrook)\n";
    if (t.Re >= 2300) cout << "hL = " << t.hfH << " " << U->L << "  (f Haaland)\n";
    mostrarPresion(rho, t.hf, Q);
    cout << "hL Swamee-Jain = " << swameeHf(Q, D, L, eps, nu) << " " << U->L << "\n";
    avisoExplicita(eps, D, t.Re, 3000);
}

// ---------------------------------------------------------------- opcion 3: tipo 2
static void opTipo2() {
    cout << "\nTIPO 2: caudal Q (dado hL)\nDatos: hL, D, L, e\n";
    double hf = pedir("hL", U->L), D = pedir("D", U->L), L = pedir("L", U->L);
    double eps = pedir("e (0 si liso)", U->L);
    double nu, rho = leerFluido(nu);
    double f0 = leerNum("f inicial supuesta (ej 0.04): ");
    if (hf <= 0 || D <= 0 || L <= 0 || eps < 0 || nu <= 0 || f0 <= 0) { cout << "Datos invalidos\n"; return; }
    Tuberia t;
    cout << "\n";
    if (!tuberiaQ(hf, D, L, eps, nu, t, true, f0, 1e-6)) { cout << "No convergio\n"; return; }
    mostrarRegimen(t.Re);
    mostrarFriccion(t.Re, eps / D);
    // Ultimo paso: Q despejado de Darcy con la f de Colebrook final y la hL dada
    double V, Qd = qDarcy(t.f, D, L, hf, V);
    cout << "V = sqrt(2 g hL/(f L/D)) = " << V << " " << vel() << "\n"
         << "Q = V pi D^2/4 = " << Qd << " " << U->Q << "\n";
    mostrarPresion(rho, hf, Qd);
    cout << "Q Swamee-Jain = " << swameeQ(hf, D, L, eps, nu) << " " << U->Q << "\n";
    avisoExplicita(eps, D, t.Re, 2000);
}

// Resultado final de un tipo 3: D, e/D, V, Re, f, error y la perdida resultante contra la pedida.
static void resumenTipo3(double D, double eps, const Tuberia& t, double hf, double L, double rho) {
    cout << "D = " << D << " " << U->L << "\nV = " << t.v << " " << vel() << "\n";
    mostrarRegimen(t.Re);
    mostrarFriccion(t.Re, eps / D);
    // Ultimo paso: D despejado de Darcy con la f de Colebrook final y la hL pedida
    cout << "D despejado de Darcy = " << dDarcy(t.f, L, t.Q, hf) << " " << U->L
         << "  (con f Colebrook y hL pedida)\n";
    cout << "hL = " << t.hf << " " << U->L << "  (f Colebrook)\n";
    if (t.Re >= 2300) cout << "hL = " << t.hfH << " " << U->L << "  (f Haaland)\n";
    cout << "hL pedida = " << hf << " " << U->L << "  -> "
         << (t.hf <= hf * (1 + 1e-6) ? "cumple" : "NO cumple") << "\n";
    mostrarPresion(rho, t.hf, t.Q);
}

// ---------------------------------------------------------------- opcion 4: tipo 3, Swamee-Jain
static void opTipo3Swamee() {
    cout << "\nTIPO 3: D por Swamee-Jain\nDatos: Q, hL, L, e\n";
    double Q = pedir("Q", U->Q), hf = pedir("hL maxima", U->L), L = pedir("L", U->L);
    double eps = pedir("e (0 si liso)", U->L);
    double nu, rho = leerFluido(nu);
    if (Q <= 0 || hf <= 0 || L <= 0 || eps < 0 || nu <= 0) { cout << "Datos invalidos\n"; return; }
    double D = swameeD(Q, hf, L, eps, nu);
    cout << "\nD Swamee-Jain = " << D << " " << U->L << "\n";
    Tuberia t = tuberiaHf(Q, D, L, eps, nu);   // con ese D: V, Re, f y la perdida que resulta
    resumenTipo3(D, eps, t, hf, L, rho);
    avisoExplicita(eps, D, t.Re, 5000);
}

// ---------------------------------------------------------------- opcion 5: tipo 3, iterando D
static void opTipo3Iterado() {
    cout << "\nTIPO 3: D iterando hasta hL\nDatos: Q, hL, L, e\n";
    double Q = pedir("Q", U->Q), hf = pedir("hL pedida", U->L), L = pedir("L", U->L);
    double eps = pedir("e (0 si liso)", U->L);
    double nu, rho = leerFluido(nu);
    if (Q <= 0 || hf <= 0 || L <= 0 || eps < 0 || nu <= 0) { cout << "Datos invalidos\n"; return; }
    double D0 = swameeD(Q, hf, L, eps, nu);   // estimado inicial (diap. 25)
    if (!(D0 > 0)) D0 = 0.1;
    cout << "\nD inicial (Swamee-Jain) = " << D0 << " " << U->L << "\n";
    double D;
    Tuberia t;
    int iter;
    if (!tuberiaDiter(Q, hf, L, eps, nu, D0, D, t, iter, true)) { cout << "No convergio\n"; return; }
    cout << "Convergio en " << iter << " vueltas\n";
    // Error del profesor (Ej. 8-4): cuanto se aparta el D de Swamee-Jain del D final (diap. 25: < 2 %)
    cout << "Error D (Swamee vs final) = " << std::fabs(D0 - D) / D * 100 << " %\n";
    resumenTipo3(D, eps, t, hf, L, rho);
}

// ---------------------------------------------------------------- opcion 6 (otro tema)
static void opManning() {
    cout << "\nCanal trapezoidal (Manning)\nz=0 rectangular, b=0 triangular\n";
    double Q = pedir("Q", U->Q), n = leerNum("n de Manning: "), S = leerNum("Pendiente S (adim.): ");
    double b = pedir("Ancho de base b", U->L), z = leerNum("Talud z (H:1V): ");
    if (Q <= 0 || n <= 0 || S <= 0 || b < 0 || z < 0 || (b == 0 && z == 0)) {
        cout << "Datos invalidos\n";
        return;
    }
    Canal c = manning(Q, n, S, b, z);
    if (!c.ok) { cout << "No se encontro profundidad\n"; return; }
    cout << "y  = " << c.y << " " << U->L << "\nA  = " << c.A << " " << U->L << "^2\nv  = " << c.v << " "
         << vel() << "\nFr = " << c.Fr << (c.Fr < 1 ? "  (subcritico)\n" : "  (supercritico)\n");
    if (ingles) cout << "(Manning con k = 1.486)\n";
}

// ---------------------------------------------------------------- opciones 8 y 9: Darcy despejada
// Ultimo paso de los tipos 3 y 2, para cuando ya tienes la f (por ejemplo la de Colebrook a mano).
static void opDespejarD() {
    cout << "\nDESPEJAR D DE DARCY (tipo 3)\nD = [8 f L Q^2 / (pi^2 g hL)]^(1/5)\n";
    double f = leerNum("f (Colebrook): "), L = pedir("L", U->L);
    double Q = pedir("Q", U->Q), hf = pedir("hL pedida", U->L);
    if (f <= 0 || L <= 0 || Q <= 0 || hf <= 0) { cout << "Datos invalidos\n"; return; }
    double D = dDarcy(f, L, Q, hf);
    cout << "\nD = " << D << " " << U->L << "\nV = " << 4 * Q / (PI * D * D) << " " << vel() << "\n";
}

static void opDespejarQ() {
    cout << "\nDESPEJAR Q DE DARCY (tipo 2)\nV = sqrt(2 g D hL / (f L)),  Q = V pi D^2/4\n";
    double f = leerNum("f (Colebrook): "), L = pedir("L", U->L);
    double D = pedir("D", U->L), hf = pedir("hL", U->L);
    if (f <= 0 || L <= 0 || D <= 0 || hf <= 0) { cout << "Datos invalidos\n"; return; }
    double V, Q = qDarcy(f, D, L, hf, V);
    cout << "\nV = " << V << " " << vel() << "\nQ = " << Q << " " << U->Q << "\n";
}

void menuFluidos() {
    elegirUnidades();
    int op;
    do {
        cout << "\n--- FLUIDOS (" << (ingles ? "ingles" : "SI") << ") ---\n"
             << "1. Factor f (con V, Re y e/D)\n"
             << "2. Tipo 1: perdida hL (dado Q)\n"
             << "3. Tipo 2: caudal Q (dado hL)\n"
             << "4. Tipo 3: D por Swamee-Jain\n"
             << "5. Tipo 3: D iterando hasta hL\n"
             << "6. Canal Manning (otro tema)\n"
             << "7. Cambiar sistema de unidades\n"
             << "8. Despejar D de Darcy (dado f)\n"
             << "9. Despejar Q de Darcy (dado f)\n"
             << "0. Salir\n";
        op = leerEntero("Opcion: ", 0, 9);
        switch (op) {
            case 1: opFriccion(); break;
            case 2: opTipo1(); break;
            case 3: opTipo2(); break;
            case 4: opTipo3Swamee(); break;
            case 5: opTipo3Iterado(); break;
            case 6: opManning(); break;
            case 7: elegirUnidades(); break;
            case 8: opDespejarD(); break;
            case 9: opDespejarQ(); break;
            default: break;
        }
    } while (op != 0);
}
