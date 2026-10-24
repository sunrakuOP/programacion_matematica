#include <iostream>

/* Dentro de la clase necesito definir todos los operadores, generalmente los 5

1. Destructor
2. Copia
3. operador de asignacion (por copia)
4. constructor de movimiento
5. operador de asignacion por movimiento

Para que sirve cada uno????

1. Destrctor: Liberar la memoria que vamos a guardar en el heap

2. Copia: pasamos una matriz y genera otra con los datos de la que pasamos 
    Objeto nuevo independiente de la matriz que pasamos 

3. Asignacion (por copia):
    Se hace por sobrecarga 
    Matriz& operator=(Matriz&& otra)

    Objeto ya existente recibe los valores de la matriz que pasamos (reasignar los valores)

4. Constructor de movimiento: 
    Crear objeto nuevo robando recursos a un objeto temporarl



std::copy(origen_inicio, origen_fin, destino) , el fin es + tam que es por posiciones, entonces es la final
    Y se guarda en la variable "datos"

*/



class Matriz {
private:
    double* datos;
    int tam; // tamano de la matriz

public:
    // aca va el constructor, crea un arreglo en memoria dinamica del tamano n
    Matriz(int n): datos(new double[n]), tam(n) {}

    ~Matriz() {
        delete[] datos; // no hay que hacerle el for, delete[] ya sabe que borra ese arreglo
    }

    // constructor de copia
    Matriz(const Matriz& otra): datos(new double[otra.tam]), tam(otra.tam) { // crear una nueva matriz con los datos de otra
        std::copy(otra.datos, otra.datos + tam, datos);
    }

    // reasignar los datos de una matriz con otros 
    Matriz& operator=(const Matriz& otra) {
        if(this == &otra) return *this;
        delete[] datos;
        tam = otra.tam;
        datos = new double[tam];
        std::copy(otra.datos, otra.datos + tam, datos);
        return *this;
    }

    // GETTER que devuelva el valor de un dato
    double get(int i) { return datos[i]; }
    void set(int i, double valor) { datos[i] = valor; }
    int tamano() const { return tam; }
    

    // 
};


class MatrizReal {
private:
    double* datos;
    int filas, columnas;
public:
    MatrizReal(int f, int c): datos(new double[f*c]), filas(f), columnas(c) {}
    ~MatrizReal() {
        delete[] datos;
    }

    double get(int i, int j) const { return datos[i * columnas + j]; }
    void set(int i, int j, double v) { datos[i * columnas + j] = v; }

};

int main() {

    return 0;
}