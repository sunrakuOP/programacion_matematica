#include "Vector3D.hpp"
#include <cmath>
#include <algorithm>

namespace {
    const double PI = 3.14159265358979323846;
}

double Vector3D::magnitud() const {
    return std::sqrt(x*x + y*y + z*z);
}

double Vector3D::productoPunto(const Vector3D& otro) const {
    return x*otro.x + y*otro.y + z*otro.z;
}

double Vector3D::anguloInterno(const Vector3D& otro) const {
    double magnitudA = this->magnitud();
    double magnitudB = otro.magnitud();

    double prodPunto = this->productoPunto(otro);
    double valor = prodPunto / (magnitudA*magnitudB);
    valor = std::clamp(valor, -1.0, 1.0);
    return std::acos(valor) * 180.0 / PI;
}

Vector3D Vector3D::productoCruz(const Vector3D& otro) const {
    return {
        y*otro.z - z*otro.y,
        z*otro.x - x*otro.z,
        x*otro.y - y*otro.x
    };
}

Vector3D Vector3D::operator+(const Vector3D& otro) const { return {x + otro.x, y + otro.y, z + otro.z}; }
Vector3D Vector3D::operator-(const Vector3D& otro) const { return {x - otro.x, y - otro.y, z - otro.z}; }
Vector3D Vector3D::operator*(double escalar) const { return {escalar*x, escalar*y, escalar*z}; }

Vector3D operator-(const Punto3D& p2, const Punto3D& p1) {
    return {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
}

Punto3D operator+(const Punto3D& p, const Vector3D& v) {
    return {p.x + v.x, p.y + v.y, p.z + v.z};
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Punto3D& p) {
    os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
    return os;
}
