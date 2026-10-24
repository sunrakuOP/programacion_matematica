// Version "plana" de Nodo, RegistroCalculo, Matriz<T>, la jerarquia de
// ElementoFinito, y Malla -- todo en un solo archivo. En el proyecto real
// (PROYECTO/include + src/) esto esta separado en un .hpp/.cpp por clase,
// esta version es solo para leer todo seguido sin saltar entre archivos.
//
// Compilar y correr:
//   g++ -std=c++17 -Wall -Wextra elementos_malla.cpp -o elementos_malla && ./elementos_malla

#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <stdexcept>
#include <cmath>

// ============================================================
// Nodo -- posicion de un punto de la malla (FEM)
// ============================================================

struct Nodo {
    double x, y, z;
};

// ============================================================
// RegistroCalculo -- guarda los datos usados en cada calculo de barra
// ============================================================

struct RegistroCalculo {
    double E, A, L;
    double EA_L;
};

// ============================================================
// Matriz<T> -- template, va completa aca (el compilador necesita el
// cuerpo completo en el punto de instanciacion)
// ============================================================

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

// ============================================================
// ElementoFinito -- clase base abstracta
// ============================================================

class ElementoFinito {
private:
    int numNodos;
public:
    ElementoFinito(int n): numNodos(n) {}
    virtual ~ElementoFinito() {}

    int getNumNodos() const { return numNodos; }
    virtual double area() = 0;
};

// ============================================================
// ElementoTriangular / ElementoCuadrilatero
// ============================================================

class ElementoTriangular: public ElementoFinito {
private:
    int base, altura;
public:
    ElementoTriangular(int b, int h): ElementoFinito(3), base(b), altura(h) {}
    double area() override { return (base * altura) / 2.0; }
};

class ElementoCuadrilatero: public ElementoFinito {
private:
    int base, altura;
public:
    ElementoCuadrilatero(int b, int h): ElementoFinito(4), base(b), altura(h) {}
    double area() override { return base * altura; }
};

// ============================================================
// ElementoBarra -- el que realmente calcula rigidez
// ============================================================

class ElementoBarra: public ElementoFinito {
private:
    double e, a;
    Nodo n1, n2;
    std::stack<RegistroCalculo> pilaRegistros;
public:
    ElementoBarra(double e, double a, Nodo n1, Nodo n2)
        : ElementoFinito(2), e(e), a(a), n1(n1), n2(n2) {}

    double areaTransversal() const { return a; }
    double area() override { return areaTransversal(); }

    double longNodo() const {
        double dx = n2.x - n1.x;
        double dy = n2.y - n1.y;
        double dz = n2.z - n1.z;
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }

    Matriz<double> matrizLocal() {
        double l = longNodo();
        RegistroCalculo registro{e, a, l, e*a/l};
        pilaRegistros.push(registro);

        Matriz<double> K(2, 2);
        K(0,0) = +(e*a)/l;
        K(0,1) = -(e*a)/l;
        K(1,0) = -(e*a)/l;
        K(1,1) = +(e*a)/l;
        return K;
    }
};

// ============================================================
// Malla -- dueña de los nodos y elementos, resuelve por ID via hash
// ============================================================

class Malla {
private:
    std::vector<Nodo*> nodos;
    std::unordered_map<int, Nodo*> idExternos;
    std::queue<ElementoBarra*> colaElementos;
public:
    Malla() {}

    ~Malla() {
        while (!colaElementos.empty()) {
            delete colaElementos.front();
            colaElementos.pop();
        }
        for (const auto& n : nodos) {
            delete n;
        }
        nodos.clear();
        idExternos.clear();
    }

    void agregarNodo(double x, double y, double z, int id) {
        Nodo* nuevo = new Nodo{x, y, z};
        nodos.push_back(nuevo);
        idExternos.insert({id, nuevo});
    }

    void agregarBarra(double e, double a, int idNodo1, int idNodo2) {
        colaElementos.push(new ElementoBarra(e, a, *idExternos[idNodo1], *idExternos[idNodo2]));
    }

    void procesarCola() {
        while (!colaElementos.empty()) {
            ElementoBarra* barraActual = colaElementos.front();
            Matriz<double> K = barraActual->matrizLocal();
            K.imprimir();
            delete barraActual;
            colaElementos.pop();
        }
    }
};

// ============================================================
// main de verificacion -- mismo caso que ya corriste en PROYECTO/src/main.cpp
// ============================================================

int main() {
    Malla malla;

    malla.agregarNodo(0.0, 0.0, 0.0, 100);
    malla.agregarNodo(2.0, 1.0, 0.0, 205);
    malla.agregarNodo(4.0, 1.0, 1.5, 310);
    malla.agregarNodo(6.0, 0.0, 1.5, 415);

    malla.agregarBarra(200e9, 0.001,  100, 205);
    malla.agregarBarra(200e9, 0.0015, 205, 310);
    malla.agregarBarra(200e9, 0.0008, 310, 415);

    malla.procesarCola();

    return 0;
}
