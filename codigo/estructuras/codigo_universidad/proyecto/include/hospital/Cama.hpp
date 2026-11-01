#ifndef CAMA_HPP
#define CAMA_HPP
#include "modelo/Enums.hpp"

class Paciente;

class Cama {
private:
    EstadoCama estadoC;
    Paciente* paciente; // inicia vacia
    int turnosRestantes;

public:
    int numeroCama; // de default mientras leo que tipo debe tener

    Cama* siguiente;
    Cama* anterior;

    Cama(int nc, Cama* s, Cama* a):
        estadoC(EstadoCama::vacia), paciente(nullptr), turnosRestantes(0), numeroCama(nc), siguiente(s), anterior(a) {}

    // getters de los atributos privados para usar fuera de la clase
    EstadoCama getEstadoCama() const;
    Paciente* getPaciente() const;
    int getTurnosRestantes() const;


    bool estaVacia();
    void cambiarEstadoCama(EstadoCama nuevoEstado);
    bool asignarPaciente(Paciente* pacienteP);
    bool tratar();
    bool tratamientoCompleto();
    Paciente* liberar();
};

#endif
