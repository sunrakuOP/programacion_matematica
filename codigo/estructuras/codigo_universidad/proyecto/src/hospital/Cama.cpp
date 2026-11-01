#include "hospital/Cama.hpp"
#include "modelo/Paciente.hpp"

EstadoCama Cama::getEstadoCama() const { return estadoC; }
Paciente* Cama::getPaciente() const { return paciente; }
int Cama::getTurnosRestantes() const { return turnosRestantes; }


bool Cama::estaVacia() {
    if(this->estadoC == EstadoCama::vacia) {
        return true;
    }
    return false;
}

void Cama::cambiarEstadoCama(EstadoCama nuevoEstado) {
    // primero comparar que no sea el mismo estado porque da lo mismo
    if(this->estadoC == nuevoEstado) {
        return;
    } else if(this->paciente != nullptr && nuevoEstado == EstadoCama::mantenimiento) {
        return;
    } else if(this->paciente != nullptr && nuevoEstado == EstadoCama::vacia) {
        return;
    } else if(this->paciente == nullptr && nuevoEstado == EstadoCama::ocupada) {
        return;
    }
    this->estadoC = nuevoEstado;
}

/*
voy a usar el "this" en vez del atributo (solo para practicar la sintaxis, se ve mas profesional)
cambie algunos metodos de void a bool para que no hayan salidas silenciosas del programa
(antes solo los dejaba en return, ahora avisa)
*/

bool Cama::asignarPaciente(Paciente* pacienteP) {
    if(this->estadoC != EstadoCama::vacia) {
        return false;
    } else if(this->paciente == pacienteP) {
        return false;
    }
    paciente = pacienteP;
    this->estadoC = EstadoCama::ocupada;
    turnosRestantes = pacienteP->turnoDeTratamiento();
    return true;
}

bool Cama::tratar() {
    if(this->paciente == nullptr || turnosRestantes <= 0) {
        return false;
    }
    turnosRestantes--;
    return true;
}

bool Cama::tratamientoCompleto() {
    // para que la cama solo dependa de los metodos de la cama, si no compararia con los del paciente y rompe la regla de encapsulacion que enseño la profe Luisa ( de algo me acuerdo )
    if(this->paciente == nullptr || turnosRestantes != 0) {
        return false;
    }
    return true;
}

Paciente* Cama::liberar() {
    if(this->paciente == nullptr) {
        return nullptr;
    } else if(!tratamientoCompleto()) {
        return nullptr;
    }
    this->turnosRestantes = 0;
    Paciente* copia = this->paciente;
    this->paciente = nullptr;
    this->estadoC = EstadoCama::vacia;
    return copia;
}
