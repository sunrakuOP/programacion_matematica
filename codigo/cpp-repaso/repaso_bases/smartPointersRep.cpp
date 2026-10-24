#include <iostream>
#include <memory>

/* Lo que hacen los "smart pointers" es manejar la memoria por mi
    Es una forma mas util de trabajar con apuntadores (en el heap), sin tener que preocuparme por borrar memoria

unique_ptr:
    El que voy a usar el 90% del tiempo
    Es el dueno de un solo recurso, no se puede copiar. SOLO SE MUEVE

*/

class ElementoFinito {
private:    
    int numNodos;
public:
    ElementoFinito(int nn): numNodos(nn) {}
    virtual ~ElementoFinito() {}

    // lo hago virtual para que cada derivada herede y pueda definirlo a su manera
    virtual double area() const { return 0; } 
};


class ElementoTriangular: public ElementoFinito {
private:
    double base, altura;
public:
    ElementoTriangular(double b, double h): ElementoFinito(3), base(b), altura(h) {}

    double getAltura() const { return base; }
    double getBase() const { return altura; }

    double area() const override {
        return (base*altura) / 2.0;
    }
};

class ElementoCuadrilatero: public ElementoFinito {
private:
    double ancho, altura;
public:
    ElementoCuadrilatero(double a, double w): ElementoFinito(3), altura(a), ancho(w) {}

    double getAncho() const { return ancho; }
    double getAltura() const { return altura; }

    double area() const override {
        return ancho*altura;
    }
};


int main() {
    std::vector<std::unique_ptr<ElementoFinito>> malla; // aca creamos el vector que contiene los elementos (MALLA)
    malla.push_back(std::make_unique<ElementoTriangular>(3.0,4.0));
    malla.push_back(std::make_unique<ElementoCuadrilatero>(2.0, 5.0));

    // ya tenemos una malla con 2 elementos 

    return 0;
}