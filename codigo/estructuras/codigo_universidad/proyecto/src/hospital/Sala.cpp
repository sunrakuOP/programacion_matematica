#include "hospital/Sala.hpp"

Sala::~Sala() {
    Cama* auxiliar = cabeza;
    while(auxiliar != nullptr) {
        Cama* siguienteCama = auxiliar->siguiente;
        delete auxiliar;
        auxiliar = siguienteCama;
    }
}

void Sala::agregarCama(int nc) {
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
