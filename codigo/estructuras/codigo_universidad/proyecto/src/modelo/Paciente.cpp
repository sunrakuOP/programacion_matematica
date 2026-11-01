#include "modelo/Paciente.hpp"
#include <iostream>

std::string Paciente::getNombre() const { return nombre; }
std::string Paciente::getCedula() const { return cedula; }
Gravedad Paciente::getGravedad() const { return x; }
std::string Paciente::getCondicion() const { return condicion; }
int Paciente::getTurnoLlegada() const { return turnoLlegada; }
int Paciente::getTiempoEspera() const { return tiempoEspera; }
int Paciente::getContadorRiesgo() const { return contadorRiesgo; }
EstadoPaciente Paciente::getEstadoPaciente() const { return estadoP; }
std::string Paciente::getNombreMedico() const { return nombreMedico; }
int Paciente::getTurnoAlta() const { return turnoAlta; }


void Paciente::esperarUnTurno() {
    tiempoEspera = tiempoEspera + minutosPorTurno;
    if(x == Gravedad::critico) {
        contadorRiesgo++;
    }
}

bool Paciente::estaPerdido() const {
    if(x != Gravedad::critico) {
        return false;
    }
    if(contadorRiesgo > limiteRiesgo) {
        return true;
    }
    return false;
}

void Paciente::marcarEnCama() {
    estadoP = EstadoPaciente::cama;
}

void Paciente::marcarAlta(const std::string& nomMed, int turno) {
    estadoP = EstadoPaciente::alta;
    nombreMedico = nomMed;
    turnoAlta = turno;
}

void Paciente::marcarPerdido() {
    estadoP = EstadoPaciente::perdido;
}

int Paciente::turnoDeTratamiento() const { return 5 - static_cast<int>(x); }

void Paciente::mostrarDatosPaciente() const {
    std::cout<<"Nombre: "<< nombre <<std::endl;
    std::cout<<"Cedula: "<< cedula <<std::endl;
    std::cout<<"Gravedad: "<< aNumero(x) <<std::endl;
    std::cout<<"Condicion: "<< condicion <<std::endl;
    std::cout<<"Turno llegado: "<< turnoLlegada <<std::endl;
    std::cout<<"Tiempo espera: "<< tiempoEspera <<std::endl;
    std::cout<<"Contador riesgo: "<< contadorRiesgo <<std::endl;
    std::cout<<"Estado paciente: "<< aTexto(estadoP) <<std::endl;
    std::cout<<"Nombre medica: "<< nombreMedico <<std::endl;
    std::cout<<"Turno de alta: "<< turnoAlta <<std::endl;
}
