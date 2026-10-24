#include <iostream>
#include <memory>

/* PROCESO PEQUENO DE FEM

Cada elemento aporta una matriz locla, y se suman todas en una matriz global



*/
template <typename T>
class Matriz {
private:
    std::vector<T> datos; 
    int filas, columnas;
public:     
    Matriz(int f, int c): datos(f*c), filas(f), columnas(c) {}
    ~Matriz() {}
    
    T& operator()(int i, int j) {
        return datos[i * columnas + j];
    }

    T operator()(int i, int j) const {
        return datos[i * columnas + j];
    }

    Matriz operator+(const Matriz& otra) const { // devolver por valor 
        // pero deben ser del mismo tamano
        if(this->filas != otra.filas || this->columnas != otra.columnas) {
            return *this;
        }

        Matriz resultado(filas, columnas);

        // Si estamos usando 1 DIMENSION, solo se debe hacer un for
        for(int k=0; k < filas*columnas; k++) {
            resultado.datos[k] = datos[k] + otra.datos[k];  // recordar acceder por metodos
        }

        return resultado; // devuelve una nueva matriz 
    }

    Matriz operator-(const Matriz& otra) const { // devolver por valor 
        // pero deben ser del mismo tamano
        if(this->filas != otra.filas || this->columnas != otra.columnas) {
            return *this;
        }

        Matriz resultado(filas, columnas);

        // Si estamos usando 1 DIMENSION, solo se debe hacer un for
        for(int k=0; k < filas*columnas; k++) {
            resultado.datos[k] = datos[k] - otra.datos[k];  // recordar acceder por metodos
        }

        return resultado; // devuelve una nueva matriz 
    }


    // operador de multiplicacion (3 for anidados) 
    Matriz operator*(const Matriz& otra) const {
        if(columnas != otra.filas) {
            return *this;
        }

        Matriz resultado(filas, otra.columnas);

        // ahora si empezar con la multiplicacion para ir guardando
        for(int i=0; i<filas; ++i) {
            for(int j=0; j< otra.columnas; ++j) {
                double suma = 0;
                for(int k=0; k<columnas; ++k) {
                    suma += (*this)(i,k)*(otra)(k,j);
                }
                (resultado)(i,j) = suma;
            }
        }

        return resultado;
    }
};


class ElementoFinito {
private:
    int numNodos;
public:
    ElementoFinito(int n): numNodos(n) {}   
    virtual ~ElementoFinito() {}

    int getNumNodos() const { return numNodos; }

    virtual Matriz<double> matrizLocal() const = 0; // para implementarlo en cada lado
    
};


class ElementoTriangular: public ElementoFinito {
private:    
    double base, altura;
public: 
    ElementoTriangular(double b, double h): ElementoFinito(3), base(b), altura(h) {}

    double getBase() const { return base; }
    double getAltura() const { return altura; }

    Matriz<double> matrizLocal() const override {
        Matriz<double> m(2,2); // crear la matriz 2x2

        m(0,0) = base;
        m(0,1) = altura;
        m(1,0) = altura;
        m(1,1) = base*altura;

        return m;
    }
};

class ElementoCuadrilatero: public ElementoFinito {
private:
    double base, ancho;
public:
    ElementoCuadrilatero(double b, double w): ElementoFinito(4), base(b), ancho(w) {}

    double getBase() const { return base; }
    double getAncho() const { return ancho; }

    Matriz<double> matrizLocal() const override {
        Matriz<double> m(2,2);

        m(0,0) = base;
        m(0,1) = ancho;
        m(1,0) = ancho;
        m(1,1) = base*ancho;
        
        return m;
    }


};


// funcion libre ensamblar
Matriz<double> ensamblar(const std::vector<std::unique_ptr<ElementoFinito>>& malla){
    Matriz<double> resultante(2,2);
    for(const auto& e: malla) {
        resultante = resultante + e->matrizLocal();  // suma las matrices (no se puede += pues no lo hemos definido)
    }   

    return resultante;
}

int main() {
    // escribir datos a mano
    std::vector<std::unique_ptr<ElementoFinito>> elementos;
    elementos.push_back(std::make_unique<ElementoTriangular>(2.0, 3.0));
    elementos.push_back(std::make_unique<ElementoCuadrilatero>(4.0, 5.0));
    elementos.push_back(std::make_unique<ElementoTriangular>(1.0, 6.0));

    Matriz<double> global = ensamblar(elementos);
    std::cout << global(0,0) << " " << global(1,1) << "\n";


    return 0;
}