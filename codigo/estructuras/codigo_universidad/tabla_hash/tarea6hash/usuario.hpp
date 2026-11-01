#ifndef USARIOS_HPP
#define USUARIOS_HPP
#include <string>

class Usuario {
private:
    std::string nombre;
    int cedula;
    double saldo;

    double totalTransferido;
    double totalRecibido;

public:
    Usuario(const std::string& n, int c, double s): 
        nombre(n), cedula(c), saldo(s), totalTransferido(0.0), totalRecibido(0.0) {}

    std::string getNombre() const;
    int getCedula() const;
    double getSaldo() const;
    
    double getTotTranf() const;
    double getTotRecib() const;

    void sumarSaldo(double valor);
    void restarSaldo(double valor);
};

#endif