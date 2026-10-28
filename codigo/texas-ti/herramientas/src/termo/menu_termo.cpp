#include <cmath>
#include <iostream>
#include "io.hpp"
#include "termo.hpp"

using std::cout;

static void avisoExtrapolacion(double x1, double x2, double x) {
    double lo = std::fmin(x1, x2), hi = std::fmax(x1, x2);
    if (x < lo || x > hi) cout << "Aviso: x esta fuera de las filas, esto extrapola\n";
}

static void opInterp() {
    cout << "\nInterpolacion lineal\n";
    double x1 = leerNum("x1: "), y1 = leerNum("y1: ");
    double x2 = leerNum("x2: "), y2 = leerNum("y2: ");
    double x = leerNum("x buscado: ");
    double y = interpLineal(x1, y1, x2, y2, x);
    if (std::isnan(y)) { cout << "x1 y x2 no pueden ser iguales\n"; return; }
    avisoExtrapolacion(x1, x2, x);
    cout << "y = " << y << "\n";
}

static void opDesdeCalidad() {
    cout << "\nPropiedad desde la calidad\n(v, u, h o s = f + x(g - f))\n";
    double f = leerNum("f (liquido sat): "), g = leerNum("g (vapor sat): ");
    double x = leerNum("calidad x (0 a 1): ");
    if (x < 0 || x > 1) cout << "Aviso: x fuera de [0,1], no es mezcla\n";
    cout << "propiedad = " << propMezcla(f, g, x) << "\n";
}

static void opDesdePropiedad() {
    cout << "\nCalidad desde una propiedad\n";
    double prop = leerNum("propiedad (v,u,h,s): ");
    double f = leerNum("f (liquido sat): "), g = leerNum("g (vapor sat): ");
    double x = calidad(prop, f, g);
    if (std::isnan(x)) { cout << "f y g no pueden ser iguales\n"; return; }
    cout << "x = " << x << "\n";
    if (x < 0) cout << "x < 0: liquido comprimido\n";
    else if (x > 1) cout << "x > 1: vapor sobrecalentado\n";
}

// Caso tipico: T (o P) cae entre dos filas de la tabla de saturacion, y ademas hay calidad.
static void opSaturadoEntreFilas() {
    cout << "\nSaturado entre 2 filas + calidad\n";
    double t = leerNum("T (o P) buscada: ");
    double x1 = leerNum("Fila 1: T (o P): "), f1 = leerNum("  f1: "), g1 = leerNum("  g1: ");
    double x2 = leerNum("Fila 2: T (o P): "), f2 = leerNum("  f2: "), g2 = leerNum("  g2: ");
    double f = interpLineal(x1, f1, x2, f2, t);
    double g = interpLineal(x1, g1, x2, g2, t);
    if (std::isnan(f)) { cout << "Las dos filas no pueden ser iguales\n"; return; }
    avisoExtrapolacion(x1, x2, t);
    cout << "f(T) = " << f << "\ng(T) = " << g << "\n";
    cout << "1. Tengo x, busco la propiedad\n2. Tengo la propiedad, busco x\n";
    if (leerEntero("Opcion: ", 1, 2) == 1) {
        double x = leerNum("x (0 a 1): ");
        cout << "propiedad = " << propMezcla(f, g, x) << "\n";
    } else {
        double prop = leerNum("propiedad: ");
        double x = calidad(prop, f, g);
        if (std::isnan(x)) { cout << "f y g iguales\n"; return; }
        cout << "x = " << x << "\n";
    }
}

static void opBilineal() {
    cout << "\nDoble interpolacion (sobrecalentado)\n";
    cout << "x = P o T de las columnas, y = la otra\n";
    double x1 = leerNum("x1: "), x2 = leerNum("x2: ");
    double y1 = leerNum("y1: "), y2 = leerNum("y2: ");
    double q11 = leerNum("valor en (x1,y1): "), q21 = leerNum("valor en (x2,y1): ");
    double q12 = leerNum("valor en (x1,y2): "), q22 = leerNum("valor en (x2,y2): ");
    double x = leerNum("x buscado: "), y = leerNum("y buscado: ");
    double q = bilineal(x1, x2, y1, y2, q11, q21, q12, q22, x, y);
    if (std::isnan(q)) { cout << "x1=x2 o y1=y2: no se puede\n"; return; }
    avisoExtrapolacion(x1, x2, x);
    avisoExtrapolacion(y1, y2, y);
    cout << "valor = " << q << "\n";
}

void menuTermo() {
    int op;
    do {
        cout << "\n--- TERMODINAMICA ---\n"
             << "1. Interpolacion lineal\n"
             << "2. Propiedad desde calidad x\n"
             << "3. Calidad x desde propiedad\n"
             << "4. Saturado entre 2 filas + x\n"
             << "5. Doble interpolacion\n"
             << "0. Salir\n";
        op = leerEntero("Opcion: ", 0, 5);
        switch (op) {
            case 1: opInterp(); break;
            case 2: opDesdeCalidad(); break;
            case 3: opDesdePropiedad(); break;
            case 4: opSaturadoEntreFilas(); break;
            case 5: opBilineal(); break;
            default: break;
        }
    } while (op != 0);
}
