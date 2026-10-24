#include <iostream>

/* CLASES
Datos: PRIVATE
Listas de incializacion en todos los constructores, no asignar en cuerpo de contructor
    si puedo asignar directo
*/

class Robot {
private:
    std::string nombre;
    int bateria;
public:
    // Constructor 
    Robot(std::string& n, int& b): nombre(n), bateria(b) {}
    // Destructor, mismo nombre de la clase, sin tipo de retorno
    ~Robot() {} // se ejecuta automaticamente cuando el obj sale del scope 
    // se usa cuando maneje memeoria yo mismo

    /* 
    Aca en el cuerpo pueden haber mas cosas

    1. metodos van aca, const si no modifican objeto
    2. Getters/Setters para tener valores o setearlos
    3. Sobrecarga de operadores 
    4. Tipos anidados
    */

};

// declarar el static afuera de la clase 

class Vehiculo {
private:
    std::string modelo;
    double velocidad;
    static int contadorVehiculos;
public:
    Vehiculo(const std::string& m): modelo(m), velocidad(0) {
        contadorVehiculos++; // cada vez que se crea se suma uno
    }
    ~Vehiculo() {}

    void acelerar(double cantidad) {
        velocidad += cantidad;
    }

    std::string getModelo() const { return modelo; }
    double getVelocidad() const { return velocidad; }

    static int getContador() { return contadorVehiculos; }
};

int Vehiculo::contadorVehiculos = 0;

int main() {

    return 0;
};