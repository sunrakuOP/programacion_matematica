#pragma once
#include "expr.hpp"

// Toda la entrada pasa por aqui. Si cin falla (fin de entrada) el programa termina.
double leerNum(const char* msg);                       // acepta expresiones: 1e-6, 0.046/100, pi
int    leerEntero(const char* msg, int min, int max);
Expr   leerFuncion(const char* msg);                   // f(x) o f(x,y), sin espacios
