#ifndef SALA_HPP
#define SALA_HPP
#include "hospital/Cama.hpp"

class Sala {
private:
    Cama* cabeza;
    Cama* cola;
    Cama* camaActual; // donde esta parado el doctor en este momento

    static const int cantidadCamas = 10;

    void agregarCama(int nc);

public:
    Sala();

    ~Sala();

    Cama& getCamaActual() const;

    bool moverDerecha();
    bool moverIzquierda();

    int camasDesocupadas() const;

    void mostrar() const;
};

#endif
