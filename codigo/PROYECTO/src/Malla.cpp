#include "Malla.hpp"

Malla::Malla() {}

Malla::~Malla() {
    while (!colaElementos.empty()) {
        delete colaElementos.front();
        colaElementos.pop();
    }
    for (const auto& n : nodos) {
        delete n;
    }
    nodos.clear();
    idExternos.clear();
}

void Malla::agregarNodo(double x, double y, double z, int id) {
    Nodo* nuevo = new Nodo{x, y, z};
    nodos.push_back(nuevo);
    idExternos.insert({id, nuevo});
}

void Malla::agregarBarra(double e, double a, int idNodo1, int idNodo2) {
    colaElementos.push(new ElementoBarra(e, a, *idExternos[idNodo1], *idExternos[idNodo2]));
}

void Malla::procesarCola() {
    while (!colaElementos.empty()) {
        ElementoBarra* barraActual = colaElementos.front();
        Matriz<double> K = barraActual->matrizLocal();
        K.imprimir();
        delete barraActual;
        colaElementos.pop();
    }
}
