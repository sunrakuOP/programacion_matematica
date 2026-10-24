#pragma once
#include "NodoDoble.hpp"

class ListaDoble {
private:
    NodoDoble* cabeza;
    NodoDoble* cola;
public:
    ListaDoble();
    ~ListaDoble();

    void agregarInicio(int valor);
    void agregarFinal(int valor);
    void agregarMedioIndice(int indice, int valor);
    void insertarMedioValor(int valor, int valorBuscar);
    void eliminarPorValor(int valorEliminar);

    // metodos de impresion (Adelante y Atras)
    void imprimirAdelante();
    void imprimirAtras();

    // ejercicio adeicionales
    void invertir();
    void fusionarOrdenadamente(ListaDoble& lista);
};
