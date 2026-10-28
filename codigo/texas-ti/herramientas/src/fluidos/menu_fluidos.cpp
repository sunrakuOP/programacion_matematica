#include <iostream>
#include "fluidos.hpp"
#include "io.hpp"

using std::cout;

static void imprimir(const Tuberia& t) {
    cout << "Re = " << t.Re << "\nf  = " << t.f << "\nv  = " << t.v << " m/s\n"
         << "Q  = " << t.Q << " m3/s\nhf = " << t.hf << " m\n";
    if (t.Re >= 2300 && t.Re < 4000) cout << "Aviso: Re en zona de transicion\n";
}

static void opFriccion() {
    cout << "\nFactor de friccion\n";
    double Re = leerNum("Re: ");
    double eps = leerNum("Rugosidad e: ");
    double D = leerNum("Diametro D (mismas unid.): ");
    if (Re <= 0 || eps < 0 || D <= 0) { cout << "Re>0, e>=0, D>0\n"; return; }
    double eD = eps / D;
    cout << "e/D = " << eD << "\n";
    if (Re < 2300) cout << "Laminar (Re<2300): f = 64/Re\n";
    Friccion r = factorFriccion(Re, eD, true, 1e-8);
    if (Re >= 2300) cout << "Haaland (f0) = " << r.f0 << "\n";
    cout << (r.ok ? "f = " : "No convergio, f = ") << r.f;
    if (Re >= 2300) cout << "  (" << r.iter << " iter)";
    cout << "\n";
}

static void opHf() {
    cout << "\nPerdida hf (dado el caudal)\nSI: m, m3/s, m2/s\n";
    double Q = leerNum("Q (m3/s): "), D = leerNum("D (m): "), L = leerNum("L (m): ");
    double eps = leerNum("e (m): "), nu = leerNum("nu (agua 20C = 1.004e-6): ");
    if (Q <= 0 || D <= 0 || L <= 0 || eps < 0 || nu <= 0) { cout << "Datos invalidos\n"; return; }
    imprimir(tuberiaHf(Q, D, L, eps, nu));
}

static void opCaudal() {
    cout << "\nCaudal Q (dado hf)\nSI: m, m3/s, m2/s\n";
    double hf = leerNum("hf (m): "), D = leerNum("D (m): "), L = leerNum("L (m): ");
    double eps = leerNum("e (m): "), nu = leerNum("nu (agua 20C = 1.004e-6): ");
    if (hf <= 0 || D <= 0 || L <= 0 || eps < 0 || nu <= 0) { cout << "Datos invalidos\n"; return; }
    Tuberia t;
    if (!tuberiaQ(hf, D, L, eps, nu, t)) { cout << "No convergio\n"; return; }
    imprimir(t);
}

static void opDiametro() {
    cout << "\nDiametro D (dado Q y hf)\nSI: m, m3/s, m2/s\n";
    double Q = leerNum("Q (m3/s): "), hf = leerNum("hf (m): "), L = leerNum("L (m): ");
    double eps = leerNum("e (m): "), nu = leerNum("nu (agua 20C = 1.004e-6): ");
    if (Q <= 0 || hf <= 0 || L <= 0 || eps < 0 || nu <= 0) { cout << "Datos invalidos\n"; return; }
    double D;
    Tuberia t;
    if (!tuberiaD(Q, hf, L, eps, nu, D, t)) { cout << "Sin solucion entre 0.1 mm y 10 m\n"; return; }
    cout << "D  = " << D << " m\n";
    imprimir(t);
}

static void opManning() {
    cout << "\nCanal trapezoidal (Manning)\nz=0 rectangular, b=0 triangular\n";
    double Q = leerNum("Q (m3/s): "), n = leerNum("n de Manning: "), S = leerNum("Pendiente S (m/m): ");
    double b = leerNum("Ancho de base b (m): "), z = leerNum("Talud z (H:1V): ");
    if (Q <= 0 || n <= 0 || S <= 0 || b < 0 || z < 0 || (b == 0 && z == 0)) {
        cout << "Datos invalidos\n";
        return;
    }
    Canal c = manning(Q, n, S, b, z);
    if (!c.ok) { cout << "No se encontro profundidad\n"; return; }
    cout << "y  = " << c.y << " m\nA  = " << c.A << " m2\nv  = " << c.v << " m/s\nFr = " << c.Fr
         << (c.Fr < 1 ? "  (subcritico)\n" : "  (supercritico)\n");
}

void menuFluidos() {
    int op;
    do {
        cout << "\n--- FLUIDOS ---\n"
             << "1. Factor f (Haaland+Colebrook)\n"
             << "2. Perdida hf (dado Q)\n"
             << "3. Caudal Q (dado hf)\n"
             << "4. Diametro D (dado Q y hf)\n"
             << "5. Canal Manning (y normal)\n"
             << "0. Salir\n";
        op = leerEntero("Opcion: ", 0, 5);
        switch (op) {
            case 1: opFriccion(); break;
            case 2: opHf(); break;
            case 3: opCaudal(); break;
            case 4: opDiametro(); break;
            case 5: opManning(); break;
            default: break;
        }
    } while (op != 0);
}
