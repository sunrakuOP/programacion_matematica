#include <iostream>
#include <vector>

/* Ya vimos la parte de las matrices como clases y como usar vector

Ahora vamos a ver como sobrecargar operadores para por ejemplo sumar/restar/dividir... matrices 
o acceder a elementos de forma mas natural
*/

class Matriz {
private:
    std::vector<double> datos;
    int filas, columnas; // recordar que se hace en formato 1D (lineal)
public:
// como lo hacemos con vector no necesitamos copias ni nada, el lo hace internamente
    Matriz(int f, int c): datos(f*c), filas(f), columnas(c) {}

// Hacerle los respectivos operadores para poder sumar, mult y tales
    // operador acceso
    double& operator() (int i, int j) {              // SIN const: para escribir, devuelve referencia
        return datos[i * columnas + j];
    }

    double operator() (int i, int j) const {         // CON const: para leer, devuelve copia
        return datos[i * columnas + j];
    }

    // operador suma
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

    return 0;
}