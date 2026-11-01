#include "usuario.hpp"

std::string Usuario::getNombre() const { return nombre; }
int Usuario::getCedula() const { return cedula; }
double Usuario::getSaldo() const { return saldo; }
    
double Usuario::getTotTranf() const { return totalTransferido; }
double Usuario::getTotRecib() const { return totalRecibido; }

void Usuario::sumarSaldo(double valor) {
    saldo += valor;
    totalRecibido += valor;
}
void Usuario::restarSaldo(double valor) {
    saldo -= valor;
    totalTransferido += valor;
}