#pragma once
#include <string>

// Evaluador de expresiones en x e y: "x^3-x-2", "sin(x)*exp(-y)", "0.046/100".
// Sin espacios en la entrada de la calculadora (cin >> string corta en el espacio).
struct Expr {
    std::string src;
    double eval(double x = 0, double y = 0) const;   // NaN si la sintaxis es invalida
};

// Valida la sintaxis y guarda la expresion. false si esta mal escrita.
bool compilar(const std::string& s, Expr& out);
