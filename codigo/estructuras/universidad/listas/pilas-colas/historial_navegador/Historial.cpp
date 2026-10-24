#include "Historial.h"
#include <iostream>
#include <ctime>

Historial::Historial(int id) : ultimo(nullptr), actual(nullptr), idUsuario(id), cantidad(0) {}

Historial::~Historial() {
    visitaPag* recorrido = ultimo;
    while (recorrido != nullptr) {
        visitaPag* anteriorNodo = recorrido->anterior; // guardar ANTES de borrar
        delete recorrido;
        recorrido = anteriorNodo;
    }
}

void Historial::abrirSitio(const std::string& sitio) {
    visitaPag* nuevo = new visitaPag(sitio, idUsuario, std::time(nullptr));
    if (actual != nullptr) {
        // Descartar el "futuro": todo lo que estaba despues de la pagina actual.
        visitaPag* descartar = actual->siguiente;
        while (descartar != nullptr) {
            visitaPag* siguienteNodo = descartar->siguiente; // guardar ANTES de borrar
            delete descartar;
            cantidad--;
            descartar = siguienteNodo;
        }
        actual->siguiente = nuevo;
        nuevo->anterior = actual;
    }
    ultimo = nuevo;
    actual = nuevo;
    cantidad++;
}

bool Historial::irAtras() {
    if (actual == nullptr || actual->anterior == nullptr) return false;
    actual = actual->anterior;
    return true;
}

bool Historial::irAdelante() {
    if (actual == nullptr || actual->siguiente == nullptr) return false;
    actual = actual->siguiente;
    return true;
}

bool Historial::cerrarSitio(int posicion) {
    if (posicion < 1 || posicion > cantidad) return false;

    visitaPag* objetivo = ultimo;
    for (int i = 1; i < posicion; i++) {
        objetivo = objetivo->anterior;
    }

    // Desenlazar el nodo (los vecinos se conectan entre si).
    if (objetivo->anterior != nullptr) objetivo->anterior->siguiente = objetivo->siguiente;
    if (objetivo->siguiente != nullptr) objetivo->siguiente->anterior = objetivo->anterior;
    if (objetivo == ultimo) ultimo = objetivo->anterior;
    if (objetivo == actual) {
        actual = (objetivo->anterior != nullptr) ? objetivo->anterior : objetivo->siguiente;
    }

    delete objetivo;
    cantidad--;
    return true;
}

void Historial::mostrarHistorial() const {
    if (ultimo == nullptr) {
        std::cout << "No hay ningun sitio visitado en el historial" << std::endl;
        return;
    }
    std::cout << "Historial de sitios visitados (del mas reciente al mas antiguo):" << std::endl;
    for (const visitaPag* recorrido = ultimo; recorrido != nullptr; recorrido = recorrido->anterior) {
        std::time_t fecha = recorrido->fechaVisita;
        std::cout << "Sitio visitado: " << recorrido->sitioVisitado
                  << ", ID de usuario: " << recorrido->idUsuario
                  << ", Fecha de visita: " << std::ctime(&fecha);
        if (recorrido == actual) std::cout << "   ^ pagina actual" << std::endl;
    }
}

void Historial::mostrarSitios() const {
    int numero = 1;
    for (const visitaPag* recorrido = ultimo; recorrido != nullptr; recorrido = recorrido->anterior) {
        std::cout << "Sitio #" << numero << ": " << recorrido->sitioVisitado << std::endl;
        numero++;
    }
}

const visitaPag* Historial::obtenerActual() const { return actual; }

int Historial::contarSitios() const { return cantidad; }
