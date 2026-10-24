#include <iostream>

/* HERENCIA

Generar una clase base con ciertos metodos y atributos, y crear una hija que contenga esos y adicione otros si requiere
*/

class ElementoFinito {
protected: // porque las clases hijas pueden acceder 
    int numNodos;
public:
    ElementoFinito(int nm): numNodos(nm) {}
    virtual ~ElementoFinito() {} // destructor debe ser virtual, hay algun metodo virtual 

    void infoElemento() const {
        std::cout<<"Elemento con "<<numNodos<<" nodos."<<std::endl;
    }

    int area() const {
        return 0;
    }
};

class ElementoTriangular: public ElementoFinito {
public:
    ElementoTriangular(): ElementoFinito(3) {} // triangulo tiene 3 nodos 

};

/* Tips para tener en cuenta 

Un metodo private, no es accesible desde la clase derivada, solo desde la propia clase.
Protected si es visible desde las clases hijas 

Al construir la base de la clase derivada, siempre se llama a la del padre
*/

class ElementoCuadrilatero: public ElementoFinito {
public:
    ElementoCuadrilatero(): ElementoFinito(4) {}

};


int main() {

    return 0;
}