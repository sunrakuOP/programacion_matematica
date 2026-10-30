#ifndef TABLAHASH_HPP
#define TABLAHASH_HPP

#include <vector>
#include <list>
#include <utility>
#include <cctype>

#include "usuario.hpp"

class TablaHash {
private:
    std::vector<std::list<std::pair<std::string, Usuario>>> tablaHash;
    int m; // numero de elementos

    int funcionHash(const std::string& llave) const;

public:
    TablaHash(int t = 1009): tablaHash(std::vector<std::list<std::pair<std::string, Usuario>>> (t)), m(t) {}

    bool existeLlave(const std::string& llave);
    
    bool esLlaveValida(const std::string& llave);

    void registrar(const std::string& llave, const std::string& nombre, int cedula, double saldo);


    double consultarSaldo(const std::string& llave);

    void transferirSaldo(const std::string& llavePasa, const std::string& llaveRecibe, double saldoPasar);
        
    double montoTransferido(const std::string& llave);

    double montoRecibido(const std::string& llave);
    
    void eliminarUsario(const std::string& llave);
};  

#endif





