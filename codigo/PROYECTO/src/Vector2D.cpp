#include "Vector2D.hpp"
#include <cmath>
#include <algorithm>

namespace {
    const double PI = 3.14159265358979323846;
}

double Vector2D::magnitud() const {
    return std::sqrt(x*x + y*y);
}

double Vector2D::productoPunto(const Vector2D& otro) const {
    return x*otro.x + y*otro.y;
}

double Vector2D::anguloInterno(const Vector2D& otro) const {
    double magnitudA = this->magnitud();
    double magnitudB = otro.magnitud();

    double prodPunto = this->productoPunto(otro);
    double valor = prodPunto / (magnitudA*magnitudB);
    valor = std::clamp(valor, -1.0, 1.0);
    return std::acos(valor) * 180.0 / PI;
}

Vector2D Vector2D::operator+(const Vector2D& otro) const { return {x + otro.x, y + otro.y}; }
Vector2D Vector2D::operator-(const Vector2D& otro) const { return {x - otro.x, y - otro.y}; }
Vector2D Vector2D::operator*(double escalar) const { return {escalar*x, escalar*y}; }

Vector2D operator-(const Punto2D& p2, const Punto2D& p1) {
    return {p2.x - p1.x, p2.y - p1.y};
}

Punto2D operator+(const Punto2D& p, const Vector2D& v) {
    return {p.x + v.x, p.y + v.y};
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Punto2D& p) {
    os << "[" << p.x << ", " << p.y << "]";
    return os;
}
