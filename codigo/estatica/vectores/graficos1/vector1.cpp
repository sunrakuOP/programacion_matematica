#include <iostream>
#include <cmath>
// para casos de arco funciones (inversas) usar algortihm para hacer que los valores queden en ranfo (CLAMP)
#include <algorithm>

/* ANGULOS Y FUNCIONES TRIGONOMETRICAS
Viven en CMATH, el tema es que vienen en radianes, no en grados (Hay que convertirlos)

*/

const double PI = 3.14159265358979323846;


struct Vector2D {
    double x, y;

    double magnitud() const {
        return std::sqrt(x*x + y*y);
    }

    Vector2D sumaVector(const Vector2D& otro) const {
        Vector2D resultadoSuma{x + otro.x, y + otro.y};
        return resultadoSuma;
    }

    Vector2D restaVector(const Vector2D& otro) const {
        Vector2D resultadoResta{x - otro.x, y - otro.y};
        return resultadoResta;
    }

    double productoPunto(const Vector2D& otro) const {  // es una cantidad escalar
        return x*otro.x + y*otro.y;
    }   

    double anguloInterno(const Vector2D& otro) const {
        double magnitudA = this->magnitud();
        double magnitudB = otro.magnitud();

        double prodPunto = this->productoPunto(otro);
        double valor = prodPunto / (magnitudA*magnitudB);
        valor = std::clamp(valor, -1.0, 1.0);
        return std::acos(valor) * 180.0 / PI;
    }

    // sobrecarga de operadores para usar forma mas comum de vectores y no usando operando
    Vector2D operator+(const Vector2D& otro) const { return {x + otro.x, y + otro.y}; }

    Vector2D operator-(const Vector2D& otro) const { return {x - otro.x, y - otro.y}; }

    Vector2D operator*(double escalar) const { return { escalar*x, escalar*y }; }
};

struct Vector3D {
    double x, y, z;

    double magnitud() const {
        return std::sqrt(x*x + y*y + z*z);
    }

    Vector3D operator+(const Vector3D& otro) const { return {x + otro.x, y + otro.y, z + otro.z}; }

    Vector3D operator-(const Vector3D& otro) const { return {x - otro.x, y - otro.y, z - otro.z}; }

    Vector3D operator*(double escalar) const { return {escalar*x, escalar*y, escalar*z}; }

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

    // producto cruz: NO existe en 2D, es especifico de 3D.
    // devuelve un vector NUEVO, perpendicular a "this" y a "otro" -- esto es
    // literalmente como se calcula la normal de una superficie (2 vectores
    // sobre el plano -> su cruz da el vector que apunta "hacia afuera" del
    // plano). Lo vas a necesitar pronto para graficos (normales de una malla).
    Vector3D productoCruz(const Vector3D& otro) const {
        return {
            y*otro.z - z*otro.y,
            z*otro.x - x*otro.z,
            x*otro.y - y*otro.x
        };
    }
};

// operator<< NO puede ser metodo miembro de Vector2D: el operando izquierdo
// de "os << v" es el std::ostream, no el Vector2D -- si fuera miembro,
// tendrias que escribir "v << os" (al reves). Por eso va como funcion libre,
// recibiendo los dos operandos explicitos.
std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

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

    std::cout << "\n--- Vector3D ---" << std::endl;
    Vector3D i{1, 0, 0};
    Vector3D j{0, 1, 0};
    Vector3D c{2, 3, 4};
    Vector3D d{5, 6, 7};

    std::cout << "magnitud(c) = " << c.magnitud() << " (esperado: " << std::sqrt(4.0+9.0+16.0) << ")" << std::endl;
    std::cout << "c + d = " << (c + d) << " (esperado: (7, 9, 11))" << std::endl;
    std::cout << "c . d = " << c.productoPunto(d) << " (esperado: 56)" << std::endl;
    std::cout << "i x j = " << i.productoCruz(j) << " (esperado: (0, 0, 1))" << std::endl;
    std::cout << "angulo(i, j) = " << i.anguloInterno(j) << " (esperado: 90)" << std::endl;

    return 0;
}