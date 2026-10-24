#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>

// template -- va completo aca, el compilador necesita el cuerpo en el punto de instanciacion
template <typename T>
class Matriz {
private:
    std::vector<T> datos;
    int filas, columnas;
public:
    Matriz(int f, int c): datos(f*c), filas(f), columnas(c) {}
    ~Matriz() {}

    T& operator()(int i, int j) {
        if(i > filas-1 || j > columnas-1) {
            throw std::out_of_range("Elemento fuera de rango");
        }
        return datos[i* columnas + j];
    }

    T operator()(int i, int j) const {
        if(i > filas-1 || j > columnas-1) {
            throw std::out_of_range("Elemento fuera de rango");
        }
        return datos[i* columnas + j];
    }

    Matriz operator+(const Matriz& otra) const {
        if(filas != otra.filas || columnas != otra.columnas) {
            throw std::invalid_argument(
                "Matriz::operator+ -- dimensiones incompatibles: (" +
                std::to_string(filas) + "x" + std::to_string(columnas) + ") vs (" +
                std::to_string(otra.filas) + "x" + std::to_string(otra.columnas) + ")"
            );
        }

        Matriz suma(filas, columnas);

        for(int k=0; k < filas*columnas; ++k) {
            suma.datos[k] = datos[k] + otra.datos[k];
        }

        return suma;
    }

    Matriz operator*(const Matriz& otra) const {
        if(columnas != otra.filas) {
            throw std::invalid_argument("Incompatibilidad de filas * columnas");
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

    void imprimir() const {
        for (int i = 0; i < filas; ++i) {
            std::cout << "[ ";
            for (int j = 0; j < columnas; ++j) {
                std::cout << std::setw(14) << std::scientific << std::setprecision(3) << (*this)(i, j) << " ";
            }
            std::cout << "]\n";
        }
    }
};
