#include <iostream>
#include <string>

/* ARCHIVO DE ORGANIZACION

Aca voy a organizar todas las clases para tener un idea y construccion mas rapida, 
conforme vaya escribiendo este archivo voy creando las construcciones de los .hpp y .cpp separados

Iba a hacer la clase persona y que de ahi heredara Paciente y Medico pero no se justifica
*/

// ====================  ORGANIZACION DE LOS ARCHIVOS  ======================

// Clase de enums
enum class Gravedad {
    critico,
    severo,
    moderado,
    leve,
    consulta
};

enum class EstadoPaciente {
    espera, 
    cama,
    alta,
    perdido
};

enum class EstadoCama {
    vacia,
    ocupada,
    mantenimiento
};

// forma de mostrar EstadoPaciente y Gravedad
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


// clase paciente en su propio archivo .hpp
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
    std::string getNombre() const { return nombre; }
    std::string getCedula() const { return cedula; }
    Gravedad getGravedad() const { return x; }
    std::string getCondicion() const { return condicion; }
    int getTurnoLlegada() const { return turnoLlegada; }
    int getTiempoEspera() const { return tiempoEspera; }
    int getContadorRiesgo() const { return contadorRiesgo; }
    EstadoPaciente getEstadoPaciente() const { return estadoP; }
    std::string getNombreMedico() const { return nombreMedico; }
    int getTurnoAlta() const { return turnoAlta; }

    
    // resto de metodos
    void esperarUnTurno() {
        tiempoEspera = tiempoEspera + minutosPorTurno;
        if(x == Gravedad::critico) {
            contadorRiesgo++;
        }
    }

    bool estaPerdido() const {
        if(x != Gravedad::critico) {
            return false;
        }
        if(contadorRiesgo > limiteRiesgo) {
            return true;
        }
        return false;
    }

    void marcarEnCama() {
        estadoP = EstadoPaciente::cama;
    }

    void marcarAlta(const std::string& nomMed, int turno) {
        estadoP = EstadoPaciente::alta;
        nombreMedico = nomMed;
        turnoAlta = turno;
    }

    void marcarPerdido() {
        estadoP = EstadoPaciente::perdido;
    }

    int turnoDeTratamiento() const { return 5 - static_cast<int>(x); }

    void mostrarDatosPaciente() const {
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
};


// clase Cama en su propio archivo .hpp
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
        numeroCama(nc), estadoC(EstadoCama::vacia), paciente(nullptr), turnosRestantes(0), siguiente(s), anterior(a) {}

    // getters de los atributos privados para usar fuera de la clase
    EstadoCama getEstadoCama() const { return estadoC; }
    Paciente* getPaciente() const { return paciente; }
    int getTurnosRestantes() const { return turnosRestantes; }


    bool estaVacia() {
        if(this->estadoC == EstadoCama::vacia) {
            return true;
        }
        return false;
    }

    void cambiarEstadoCama(EstadoCama nuevoEstado) {
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

    bool asignarPaciente(Paciente* pacienteP) {
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

    bool tratar() {
        if(this->paciente == nullptr || turnosRestantes <= 0) {
            return false;
        }
        turnosRestantes--;
        return true;
    }

    bool tratamientoCompleto() {
        // para que la cama solo dependa de los metodos de la cama, si no compararia con los del paciente y rompe la regla de encapsulacion que enseño la profe Luisa ( de algo me acuerdo )
        if(this->paciente == nullptr || turnosRestantes != 0) {
            return false;
        }
        return true;
    }

    Paciente* liberar() {
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
};



// clase Sala en su propio archivo .hpp
class Sala {    
private:
    Cama* cabeza; 
    Cama* cola;
    int n;
public:
    Sala(int t): cabeza(nullptr), cola(nullptr), n(t) {}
    
    ~Sala() {
        Cama* auxiliar = cabeza;
        while(auxiliar != nullptr) {
            Cama* siguienteCama = auxiliar->siguiente;
            delete auxiliar;
            auxiliar = siguienteCama;
        }
    }

    void agregarCama(int nc) {
        if(nc <= 0 || nc > 10) {
            return;
        }

        if(cabeza == nullptr) {
            Cama* nueva = new Cama(nc, nullptr, nullptr);
            cabeza = nueva;
            cola = nueva;
            return;
        }
        Cama* nueva = new Cama(nc, nullptr, cola);
        cola->siguiente = nueva;
        cola = nueva;
    }
};








int main() {

    return 0;
}