#pragma once
#include <iostream>
#include "Punto2D.hpp"

struct Vector2D {
    double x, y;

    double magnitud() const;
    double productoPunto(const Vector2D& otro) const;
    double anguloInterno(const Vector2D& otro) const;

    Vector2D operator+(const Vector2D& otro) const;
    Vector2D operator-(const Vector2D& otro) const;
    Vector2D operator*(double escalar) const;
};

// punto - punto = vector (la direccion entre dos posiciones).
// Esto es lo que en el archivo suelto (vector1.cpp) se llamaba "desdePuntos" --
// con Punto2D y Vector2D ya separados, la operacion se expresa directo como
// una resta, sin necesitar una funcion con nombre aparte.
Vector2D operator-(const Punto2D& p2, const Punto2D& p1);

// punto + vector = punto (desplazar una posicion en esa direccion).
Punto2D operator+(const Punto2D& p, const Vector2D& v);

std::ostream& operator<<(std::ostream& os, const Vector2D& v);
std::ostream& operator<<(std::ostream& os, const Punto2D& p);
