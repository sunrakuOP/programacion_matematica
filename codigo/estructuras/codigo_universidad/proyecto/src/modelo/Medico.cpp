#include "modelo/Medico.hpp"
#include <iostream>

std::string Medico::getNombreMedico() const { return nombreMedico; }

bool Medico::iniciarJornada() {
    if(enJornada) {
        return false;
    }
    enJornada = true;
    turnosJornadaActual = 0;
    return true;
}

bool Medico::registrarTurno() {
    if(this->turnosJornadaActual >= maxTurnosJornada || !enJornada) {
        return false;
    }
    turnosJornadaActual++;
    return true;
}

bool Medico::jornadaCompleta() const {
    if(turnosJornadaActual == maxTurnosJornada) {
        return true;
    }
    return false;
}

bool Medico::terminarJornada() {
    if(!enJornada) {
        return false;
    }
    historialJornadas.push_back(turnosJornadaActual);
    enJornada = false;
    return true;
}

int Medico::jornadasTrabajadas() const {
    return (int)historialJornadas.size();
}

int Medico::turnoDeJornada(int indice) const {
    int tamanoLista = (int)historialJornadas.size();
    if(indice > tamanoLista - 1 || indice < 0) {
        return -1;
    }

    // usar iteradores para moverse por la lista
    auto it = historialJornadas.begin();
    for(int i=0; i < indice && it != historialJornadas.end(); ++i) {
        it++;
    }
    return *it;
}

void Medico::mostrar() const {
    std::cout<<"Nombre medico: "<< nombreMedico <<std::endl;
    std::cout<<"Jornadas: "<< jornadasTrabajadas() <<std::endl;
    int i = 0;
    for(auto it = historialJornadas.begin(); it != historialJornadas.end(); ++it) {
        std::cout<<"Jornada "<< i <<": "<< *it <<std::endl;
        ++i;
    }
}
