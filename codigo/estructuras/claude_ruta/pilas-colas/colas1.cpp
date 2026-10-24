#include <iostream>
#include <cmath>
#include <iomanip>

/* Ya vimos PILAS (LIFO): Last in first out 

std::queue<int> cola; 
    Igual que PILA pero lo que hace es que desocupa en el mismo orden en el que se introducen
    Primer elemento sale de ultimo


A veces es util porque es mas rapido que vector O(1)

Vector es muy rapido sacando al final, pero muy lento sacando al frente 
*/

// procesar un elemento finito en orden
struct Nodo {
    double x,y,z;
};

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

    // metodo para formatear la matriz y desplegar en pantalla 
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

class ElementoFinito {
private:
    int numNodos;
public:
    ElementoFinito(int n): numNodos(n) {} 
    virtual ~ElementoFinito() {}

    int getNumNodos() const { return numNodos; }

    virtual double area() = 0;
};

class ElementoBarra: public ElementoFinito {
private:
    double e, a;
    Nodo n1, n2; // una barra tiene 2 nodos 
public:
    ElementoBarra(double e, double a, Nodo n1, Nodo n2): ElementoFinito(2), e(e), a(a), n1(n1), n2(n2) {}

    double area() override {
        return a;
    }

    double longNodo() const {
        double dx = n2.x - n1.x;
        double dy = n2.y - n1.y;
        double dz = n2.z - n1.z;
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }

    Matriz<double> matrizLocal() const {
        double l = longNodo();
        Matriz<double> K(2,2);

        K(0,0) = +(e*a)/ l;
        K(0,1) = -(e*a)/l;
        K(1,0) = -(e*a)/ l;
        K(1,1) = +(e*a)/ l;

        return K;
    }


};

int main() {
    // usar la cola para calcular Elementos de barra en orden de llegada
    Nodo n1 = {0, 0, 0};
    Nodo n2 = {1, 0, 0};
    Nodo n3 = {2, 0, 0};
    Nodo n4 = {3, 0, 0};

    std::queue<ElementoBarra*> colaDeCalculo;
    colaDeCalculo.push(new ElementoBarra(200e9, 0.001, n1, n2));
    colaDeCalculo.push(new ElementoBarra(200e9, 0.002, n2, n3));
    colaDeCalculo.push(new ElementoBarra(200e9, 0.0015, n3, n4));

    // ahora realizar la matriz de rigidez en orden
    while(!colaDeCalculo.empty()) {
        ElementoBarra* actual = colaDeCalculo.front();
        Matriz<double> K = actual->matrizLocal();
        std::cout << "\nBarra (L=" << actual->longNodo() << "):\n";
        K.imprimir();
        colaDeCalculo.pop();
    }

    return 0;
}