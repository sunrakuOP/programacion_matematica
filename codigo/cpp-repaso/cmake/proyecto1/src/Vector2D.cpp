#include "Vector2D.hpp"
#include <cmath>

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

double Vector2D::magnitud() const {
    return std::sqrt(x*x + y*y);
}

Vector2D Vector2D::operator+(const Vector2D& otro) const {
    return Vector2D(x + otro.x, y + otro.y);
}