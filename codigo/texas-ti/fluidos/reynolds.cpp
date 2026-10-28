#include <iostream>
#include <cmath>
#include <iomanip>
#include <os.h>

const double TOL = 1e-8;
const int MAX_ITER = 100;

// Haaland: 1/sqrt(f) = -1.8 log10[ (e/D / 3.7)^1.11 + 6.9/Re ]
double haaland(double Re, double eD) {
    double x = -1.8 * std::log10(std::pow(eD / 3.7, 1.11) + 6.9 / Re);
    return 1.0 / (x * x);
}

// Colebrook por punto fijo, partiendo de f0. Devuelve true si converge.
bool colebrook(double Re, double eD, double f0, double &f, int &iter) {
    f = f0;
    double err = 1.0;
    iter = 0;
    std::cout << "\niter        f            error\n";
    while (err > TOL && iter < MAX_ITER) {
        double inv = -2.0 * std::log10(eD / 3.7 + 2.51 / (Re * std::sqrt(f)));
        double fNuevo = 1.0 / (inv * inv);
        err = std::fabs(fNuevo - f);
        f = fNuevo;
        iter++;
        std::cout << std::setw(4) << iter << "   " << f << "   " << err << "\n";
    }
    return err <= TOL;
}

void calcular() {
    double Re, eps, D;
    std::cout << "\nNumero de Reynolds (Re): ";
    std::cin >> Re;
    std::cout << "Rugosidad absoluta (e): ";
    std::cin >> eps;
    std::cout << "Diametro (D, mismas unidades que e): ";
    std::cin >> D;

    if (!std::cin || Re <= 0 || eps < 0 || D <= 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Entrada invalida (Re > 0, e >= 0, D > 0).\n";
        return;
    }

    double eD = eps / D;
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "\nRugosidad relativa e/D = " << eD << "\n";

    if (Re < 2300) {
        std::cout << "Re < 2300: flujo laminar, Colebrook no aplica.\n"
                  << "f = 64/Re = " << 64.0 / Re << "\n";
        return;
    }

    double f0 = haaland(Re, eD);
    std::cout << "Semilla Haaland: f0 = " << f0 << "\n";

    double f;
    int iter;
    if (colebrook(Re, eD, f0, f, iter))
        std::cout << "\nf (Colebrook) = " << f << "  (" << iter << " iteraciones)\n";
    else
        std::cout << "\nNo convergio en " << MAX_ITER << " iteraciones.\n";
}

int main() {
    
    int op;
    do {
        std::cout << "\n=== Factor de friccion (Haaland + Colebrook) ===\n"
                  << "1. Calcular f\n"
                  << "0. Salir\n"
                  << "Opcion: ";
        std::cin >> op;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            op = -1;
        }
        switch (op) {
            case 1: calcular(); break;
            case 0: break;
            default: std::cout << "Opcion invalida.\n";
        }
    } while (op != 0);
    return 0;
}
