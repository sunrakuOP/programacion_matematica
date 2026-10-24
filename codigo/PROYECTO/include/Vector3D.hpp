#pragma once
#include <iostream>
#include "Punto3D.hpp"

struct Vector3D {
    double x, y, z;

    double magnitud() const;
    double productoPunto(const Vector3D& otro) const;
    double anguloInterno(const Vector3D& otro) const;

    // producto cruz: solo existe en 3D. Devuelve un vector nuevo, perpendicular
    // a "this" y a "otro" -- es como se calcula la normal de una superficie.
    Vector3D productoCruz(const Vector3D& otro) const;

    Vector3D operator+(const Vector3D& otro) const;
    Vector3D operator-(const Vector3D& otro) const;
    Vector3D operator*(double escalar) const;
};

Vector3D operator-(const Punto3D& p2, const Punto3D& p1);
Punto3D operator+(const Punto3D& p, const Vector3D& v);

std::ostream& operator<<(std::ostream& os, const Vector3D& v);
std::ostream& operator<<(std::ostream& os, const Punto3D& p);
