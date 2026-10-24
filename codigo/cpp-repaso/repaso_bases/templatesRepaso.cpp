#include <iostream>
#include <vector>

/* TEMPLATES
Para no repetir codigo, solo generarlo una vez y usarlo si cumple las condiciones

Solo creo la matriz de tipo <T>
    Matriz<T> y asi recibe cualquier tipo de dato
*/

template <typename T>
class Matriz {
private:
    std::vector<T> datos;
    int filas, columnas;
public:
    Matriz(int f, int c) : datos(f * c), filas(f), columnas(c) {}

    T& operator()(int i, int j) { return datos[i * columnas + j]; }
    T operator()(int i, int j) const { return datos[i * columnas + j]; }

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


int main() {
    Matriz<double> a(2,2), b(2,2);
    a(0,0)=1; a(0,1)=2; a(1,0)=3; a(1,1)=4;
    b(0,0)=5; b(0,1)=6; b(1,0)=7; b(1,1)=8;
    Matriz<double> c = a + b;
    std::cout << c(0,0) << " " << c(1,1) << "\n";

    Matriz<int> x(2,2), y(2,2);
    // ... llenar y sumar igual, con enteros

    return 0;
}