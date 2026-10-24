// aca solo vamos a difinir el tema de la matriz 
#pragma once
#include <vector>
#include <stdexcept>

// como es template NO HAY .cpp, TODO EN EL .hpp

template <typename T>
class Matriz {
private:    
    std::vector<T> datos;
    int filas, columnas;
public:
    Matriz(int f, int c): datos(f*c), filas(f), columnas(c) {} 
    ~Matriz() {}

    T& operator()(int f, int j) {
    if(f > filas -1 || j > columnas -1) {
        throw std::out_of_range("Elemento fuera de rango");
    }
    return datos[f * columnas + j];
    }

    T operator()(int f, int j) const {
        if(f > filas -1 || j > columnas -1) {
            throw std::out_of_range("Elemento fuera de rango");
        }
        return datos[f * columnas + j];
    }


    Matriz operator+(const Matriz& otra) const {
        if(filas != otra.filas || columnas != otra.columnas) {
            throw std::invalid_argument("Matrices de diferente tamano");
        }

        Matriz resultado(filas, columnas);

        for(int k=0; k<filas*columnas; ++k) {
            resultado.datos[k] = datos[k] + otra.datos[k];
        }

        return resultado;
    }

    Matriz operator-(const Matriz& otra) const {
       if(filas != otra.filas || columnas != otra.columnas) {
            throw std::invalid_argument("Matrices de diferente tamano");
        } 
        Matriz resultado(filas, columnas);

        for(int k=0; k<filas*columnas; ++k) {
            resultado.datos[k] = datos[k] - otra.datos[k];
        }

        return resultado;
    }

    Matriz operator*(const Matriz& otra) const {
        if(columnas != otra.filas) {
            throw std::invalid_argument("Columnas y Filas no coinciden");
        }
        Matriz resultado(filas, otra.columnas);

        for(int i=0; i<filas; ++i) {
            for(int j=0; j<otra.columnas; ++j) {
                T suma = 0;
                for(int k=0; k < columnas; ++k) {
                    suma += (*this)(i,k)*(otra)(k,j);
                }
                (resultado)(i,j) = suma;
            }
        }
        return resultado;
    }
};