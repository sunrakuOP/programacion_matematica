// Version "plana" de Punto2D/Punto3D/Vector2D/Vector3D -- todo en un solo
// archivo, declaracion e implementacion juntas, como venimos trabajando en
// los ejercicios sueltos. En el proyecto real (PROYECTO/include + src/) esto
// esta separado en .hpp/.cpp, esta version es solo para leer mas comodo.
//
// Compilar y correr:
//   g++ -std=c++17 -Wall -Wextra vectores.cpp -o vectores && ./vectores

#include <iostream>
#include <cmath>
#include <algorithm>

namespace {
    const double PI = 3.14159265358979323846;
}

// ============================================================
// PUNTOS -- solo posicion, sin algebra vectorial a proposito.
// ============================================================

struct Punto2D {
    double x, y;
};

struct Punto3D {
    double x, y, z;
};

// ============================================================
// VECTOR2D
// ============================================================

struct Vector2D {
    double x, y;

    double magnitud() const {
        return std::sqrt(x*x + y*y);
    }

    double productoPunto(const Vector2D& otro) const {
        return x*otro.x + y*otro.y;
    }

    double anguloInterno(const Vector2D& otro) const {
        double magnitudA = this->magnitud();
        double magnitudB = otro.magnitud();
        double prodPunto = this->productoPunto(otro);
        double valor = prodPunto / (magnitudA*magnitudB);
        valor = std::clamp(valor, -1.0, 1.0);   // evita NaN por error de redondeo
        return std::acos(valor) * 180.0 / PI;
    }

    Vector2D operator+(const Vector2D& otro) const { return {x + otro.x, y + otro.y}; }
    Vector2D operator-(const Vector2D& otro) const { return {x - otro.x, y - otro.y}; }
    Vector2D operator*(double escalar) const { return {escalar*x, escalar*y}; }
};

// punto - punto = vector (direccion entre dos posiciones)
Vector2D operator-(const Punto2D& p2, const Punto2D& p1) {
    return {p2.x - p1.x, p2.y - p1.y};
}

// punto + vector = punto (desplazar una posicion)
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

// ============================================================
// VECTOR3D
// ============================================================

struct Vector3D {
    double x, y, z;

    double magnitud() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    double productoPunto(const Vector3D& otro) const {
        return x*otro.x + y*otro.y + z*otro.z;
    }

    double anguloInterno(const Vector3D& otro) const {
        double magnitudA = this->magnitud();
        double magnitudB = otro.magnitud();
        double prodPunto = this->productoPunto(otro);
        double valor = prodPunto / (magnitudA*magnitudB);
        valor = std::clamp(valor, -1.0, 1.0);
        return std::acos(valor) * 180.0 / PI;
    }

    // producto cruz: solo existe en 3D. Perpendicular a "this" y a "otro" --
    // es como se calcula la normal de una superficie.
    Vector3D productoCruz(const Vector3D& otro) const {
        return {
            y*otro.z - z*otro.y,
            z*otro.x - x*otro.z,
            x*otro.y - y*otro.x
        };
    }

    Vector3D operator+(const Vector3D& otro) const { return {x + otro.x, y + otro.y, z + otro.z}; }
    Vector3D operator-(const Vector3D& otro) const { return {x - otro.x, y - otro.y, z - otro.z}; }
    Vector3D operator*(double escalar) const { return {escalar*x, escalar*y, escalar*z}; }
};

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

// ============================================================
// main de verificacion -- mismos casos que ya corriste en vector1.cpp
// ============================================================

int main() {
    std::cout << "--- Vector2D ---" << std::endl;
    Vector2D a{3, 4};
    Vector2D b{4, 3};
    Vector2D perpA{1, 0};
    Vector2D perpB{0, 1};

    std::cout << "a = " << a << ", magnitud(a) = " << a.magnitud() << " (esperado: 5)" << std::endl;
    std::cout << "a + b = " << (a + b) << " (esperado: (7, 7))" << std::endl;
    std::cout << "a - b = " << (a - b) << " (esperado: (-1, 1))" << std::endl;
    std::cout << "a * 2 = " << (a * 2.0) << " (esperado: (6, 8))" << std::endl;
    std::cout << "a . b = " << a.productoPunto(b) << " (esperado: 24)" << std::endl;
    std::cout << "angulo(perpA, perpB) = " << perpA.anguloInterno(perpB) << " (esperado: 90)" << std::endl;
    std::cout << "angulo(a, a) = " << a.anguloInterno(a) << " (esperado: 0, prueba el clamp)" << std::endl;

    std::cout << "\n--- Punto2D + Vector2D ---" << std::endl;
    Punto2D p1{0.0, 0.0};
    Punto2D p2{3.0, 4.0};
    Vector2D direccion = p2 - p1;
    std::cout << "direccion(" << p1 << ", " << p2 << ") = " << direccion << std::endl;
    std::cout << "p1 + direccion = " << (p1 + direccion) << " (debe volver a dar " << p2 << ")" << std::endl;

    std::cout << "\n--- Vector3D ---" << std::endl;
    Vector3D i{1, 0, 0};
    Vector3D j{0, 1, 0};
    Vector3D c{2, 3, 4};
    Vector3D d{5, 6, 7};

    std::cout << "magnitud(c) = " << c.magnitud() << std::endl;
    std::cout << "c + d = " << (c + d) << " (esperado: (7, 9, 11))" << std::endl;
    std::cout << "c . d = " << c.productoPunto(d) << " (esperado: 56)" << std::endl;
    std::cout << "i x j = " << i.productoCruz(j) << " (esperado: (0, 0, 1))" << std::endl;
    std::cout << "angulo(i, j) = " << i.anguloInterno(j) << " (esperado: 90)" << std::endl;

    return 0;
}
