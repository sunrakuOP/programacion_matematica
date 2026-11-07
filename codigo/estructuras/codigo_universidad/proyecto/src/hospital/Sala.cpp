#include "hospital/Sala.hpp"
#include "modelo/Paciente.hpp"
#include <iostream>

void Sala::agregarCama(int nc) {
    if(nc <= 0 || nc > cantidadCamas) {
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

Sala::Sala(): cabeza(nullptr), cola(nullptr), camaActual(nullptr) {
    for(int i=1; i < cantidadCamas + 1; ++i) {
        agregarCama(i);
    }
    camaActual = cabeza;
}

Sala::~Sala() {
    Cama* auxiliar = cabeza;
    while(auxiliar != nullptr) {
        Cama* siguienteCama = auxiliar->siguiente;
        delete auxiliar;
        auxiliar = siguienteCama;
    }
}

Cama& Sala::getCamaActual() const { return *(camaActual); } // desreferenciando

bool Sala::moverDerecha() {
    if(this->camaActual->siguiente == nullptr) {
        return false;
    }
    camaActual = camaActual->siguiente;
    return true;
}

bool Sala::moverIzquierda() {
    if(this->camaActual->anterior == nullptr) {
        return false;
    }
    camaActual = camaActual->anterior;
    return true;
}


int Sala::camasDesocupadas() const {
    Cama* auxiliar = cabeza;
    int cuenta = 0;
    while(auxiliar != nullptr) {
        if(auxiliar->getEstadoCama() == EstadoCama::vacia) {
            cuenta++;
        }
        auxiliar = auxiliar->siguiente;
    }
    return cuenta;
}


void Sala::mostrar() const {
    // linea 1: las camas, con "=" solo entre ellas
    Cama* auxiliar = cabeza;
    while(auxiliar != nullptr) {
        if(auxiliar->numeroCama < 10) {
            std::cout<<"[ #"<< auxiliar->numeroCama <<":";
        } else {
            std::cout<<"[#"<< auxiliar->numeroCama <<":";
        }

        if(auxiliar->getEstadoCama() == EstadoCama::vacia) {
            std::cout<<"V  ]";
        } else if(auxiliar->getEstadoCama() == EstadoCama::mantenimiento) {
            std::cout<<"X  ]";
        } else if(auxiliar->getPaciente()->getGravedad() == Gravedad::critico) {
            std::cout<<"P1*]";
        } else {
            std::cout<<"P"<< aNumero(auxiliar->getPaciente()->getGravedad()) <<" ]";
        }

        if(auxiliar->siguiente != nullptr) {
            std::cout<<"=";
        }
        auxiliar = auxiliar->siguiente;
    }
    std::cout<<std::endl;

    // linea 2: la M debajo de la cama actual (cada celda mide 9, igual que arriba)
    auxiliar = cabeza;
    while(auxiliar != nullptr) {
        if(auxiliar == camaActual) {
            std::cout<<"    M    ";
        } else {
            std::cout<<"         ";
        }

        if(auxiliar->siguiente != nullptr) {
            std::cout<<" ";
        }
        auxiliar = auxiliar->siguiente;
    }
    std::cout<<std::endl;
}
