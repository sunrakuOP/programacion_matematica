#ifndef MEDICO_HPP
#define MEDICO_HPP
#include <string>
#include <list>

class Medico {
private:
    std::string nombreMedico;
    int turnosJornadaActual;
    bool enJornada;

    // iba a hacer yo mismo la implementacion de la lista pero quiero aprender a usar la stl entonces lo hare asi
    std::list<int> historialJornadas;

    static const int maxTurnosJornada = 50;

public:
    Medico(const std::string& n): nombreMedico(n), turnosJornadaActual(0), enJornada(false) {}

    std::string getNombreMedico() const;

    bool iniciarJornada();
    bool registrarTurno();
    bool jornadaCompleta() const;
    bool terminarJornada();
    int jornadasTrabajadas() const;
    int turnoDeJornada(int indice) const;
    void mostrar() const;
};

#endif
