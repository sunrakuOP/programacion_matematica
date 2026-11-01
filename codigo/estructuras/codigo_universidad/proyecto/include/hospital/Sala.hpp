#ifndef SALA_HPP
#define SALA_HPP
#include "hospital/Cama.hpp"

class Sala {
private:
    Cama* cabeza;
    Cama* cola;
    int n;
public:
    Sala(int t): cabeza(nullptr), cola(nullptr), n(t) {}

    ~Sala();

    void agregarCama(int nc);
};

#endif
