#include <iostream>
#include <stdexcept>

/* Necesaria para:
    std::invalid_argument, std::out_of_range

    Cuando la voy a usar????
        Cuando al sumar matrices el tamano sea incompatible o haya algun error que requiera devolver error

    Cuando uso el operador + para sumar dos matrices y el tamano es incompatible 
    hago return *this; 
Es decir devuelvo algo valido que realmente es un error 

Usar una EXCEPCION: Esto no se puede completar y no voy a fingir que si (datos invalidos por ejemplo...)
    INTERRUMPE LA EJECUCION Y ME OBLIGA A DECIDIR QUE HACER

*/

template <typename T>
class Matriz {
private:
    std::vector<T> datos; // vamos a hacerlo aca con vector de vectores para practicar 
    int filas, columnas;
public:
    Matriz(int f, int c): datos(f*c), filas(f), columnas(c) {}
    ~Matriz() {}

    // agregar el operador de () 
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

    // ahora la parte nueva, EXCEPCIONES, si el tipo no cuadra se hace manejo con throw del error 
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

    // operador de * (mult de matrices)
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

};


int main() {
    Matriz<double> A(2,2);
    Matriz<double> B(3,3);
    Matriz<double> D(2,4);   // renombrala, ya no la necesitás llamar C

    try {
        Matriz<double> suma = A + B;      // dispara invalid_argument
        std::cout << "suma ok\n";
    } catch(const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    } catch(const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << "\n";
    } catch(const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    try {
        Matriz<double> prod = A * D;      // ¿esto dispara error? revisá dimensiones
        // si no dispara, agregá una línea que acceda a prod(algún_indice_invalido)
        prod(9,9);
    } catch(const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    } catch(const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << "\n";
    } catch(const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
