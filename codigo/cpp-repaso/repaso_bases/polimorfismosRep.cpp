#include <iostream>

/* Ya vimos herencia, ahora con el polimorfismo es:
    Que cada clase hija maneje sus metodos a su manera, que se comporte diferente
    Ej: Un perro no maulla, un gato no ladra, pero ambos son animales

    Se hace mediante VIRTUAL, despacho por tipo real, no por tipo declarado.


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

/* 
Usando el virtual y el override podemos hacer que un mismo metodo se comporte diferente en cada clase
*/

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

/* DYNAMIC CAST

Cuando tengo un puntero a la clase base, y necesito confirmar de que tipo es.
Siempre se crea el puntero a la base y de ahi se derivan los if para comprobar el tipo de derivada 
*/

int main() {
    ElementoFinito* elemento = new ElementoTriangular(5,4); // puntero de tipo base apuntando a un tipo triangulo

    ElementoTriangular* t = dynamic_cast<ElementoTriangular*>(elemento);
    if(t != nullptr) {
        std::cout<<"Es un triangulo de base: "<<t->getAltura()<<", altura: "<<t->getBase()<<", area: "<< t->area() <<std::endl;
    } else {
        std::cout<<"No es un triangulo."<<std::endl;
    }


    // si no es del tipo, devuelve un puntero nulo, sino devuelve algo

    return 0;
}