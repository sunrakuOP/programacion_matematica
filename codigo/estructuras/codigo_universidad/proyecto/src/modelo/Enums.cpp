#include "modelo/Enums.hpp"

std::string aTexto(EstadoPaciente estado) {
    switch (estado) {
    case EstadoPaciente::espera:     return "espera";
    case EstadoPaciente::cama:       return "cama";
    case EstadoPaciente::alta:       return "alta";
    case EstadoPaciente::perdido:    return "perdido";
    }
return "desconocido";
}

int aNumero(Gravedad g) {
    switch (g) {
    case Gravedad::critico:     return 1;
    case Gravedad::severo:      return 2;
    case Gravedad::moderado:    return 3;
    case Gravedad::leve:        return 4;
    case Gravedad::consulta:    return 5;
    }
return -1;
}
