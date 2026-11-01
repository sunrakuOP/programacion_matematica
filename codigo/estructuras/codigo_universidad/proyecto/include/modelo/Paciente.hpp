#ifndef PACIENTE_HPP
#define PACIENTE_HPP
#include <string>
#include "modelo/Enums.hpp"

class Paciente {
private:
    std::string nombre;
    std::string cedula;
    Gravedad x;
    std::string condicion;
    int turnoLlegada;
    int tiempoEspera;
    int contadorRiesgo;
    EstadoPaciente estadoP;
    std::string nombreMedico;
    int turnoAlta;

    // constantes para la comparacion
    static const int minutosPorTurno = 5;
    static const int limiteRiesgo = 6;
public:
    Paciente(const std::string& n, const std::string& c, Gravedad y, const std::string& co, int tl):
        nombre(n), cedula(c), x(y), condicion(co), turnoLlegada(tl), tiempoEspera(0), contadorRiesgo(0),
        estadoP(EstadoPaciente::espera), nombreMedico(""), turnoAlta(0) {}


    // getters de los atributos para usar fuera de la funcion
    std::string getNombre() const;
    std::string getCedula() const;
    Gravedad getGravedad() const;
    std::string getCondicion() const;
    int getTurnoLlegada() const;
    int getTiempoEspera() const;
    int getContadorRiesgo() const;
    EstadoPaciente getEstadoPaciente() const;
    std::string getNombreMedico() const;
    int getTurnoAlta() const;


    // resto de metodos
    void esperarUnTurno();
    bool estaPerdido() const;
    void marcarEnCama();
    void marcarAlta(const std::string& nomMed, int turno);
    void marcarPerdido();
    int turnoDeTratamiento() const;
    void mostrarDatosPaciente() const;
};

#endif
