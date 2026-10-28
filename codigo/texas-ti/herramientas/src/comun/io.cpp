#include "io.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

static std::string leerToken(const char* msg) {
    std::string t;
    std::cout << msg;
    if (!(std::cin >> t)) {
        std::cout << "\n";
        std::exit(0);
    }
    return t;
}

double leerNum(const char* msg) {
    for (;;) {
        Expr e;
        if (compilar(leerToken(msg), e)) {
            double v = e.eval();
            if (std::isfinite(v)) return v;
        }
        std::cout << "Valor invalido (ej: 0.5, 1e-6, 2/3)\n";
    }
}

int leerEntero(const char* msg, int min, int max) {
    for (;;) {
        int n = (int)std::lround(leerNum(msg));
        if (n >= min && n <= max) return n;
        std::cout << "Debe estar entre " << min << " y " << max << "\n";
    }
}

Expr leerFuncion(const char* msg) {
    for (;;) {
        Expr e;
        if (compilar(leerToken(msg), e)) return e;
        std::cout << "Expresion invalida (sin espacios)\n";
    }
}
