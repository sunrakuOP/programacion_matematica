#pragma once

// aca lo que hacemos es solo declarar la clase, no definimos nada (solo poner que hay)

class Vector2D {
private:
    double x,y;
public:
// todo termina en ; (no se define nada) solo firma, sin el cuerpo
    Vector2D(double x, double y);
    double magnitud() const;
    Vector2D operator+(const Vector2D& otro) const;
};   

