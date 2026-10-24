#include <iostream>
#include "ListaDoble.hpp"

int main() {
    ListaDoble lista;

    lista.agregarInicio(6);
    lista.agregarInicio(5);
    lista.agregarInicio(4);
    lista.agregarInicio(3);
    lista.agregarInicio(2);
    lista.agregarInicio(1);

    lista.imprimirAdelante();

    // lista.invertir();
    // lista.imprimirAdelante();

    ListaDoble lista2;
    lista2.agregarInicio(15);
    lista2.agregarInicio(14);
    lista2.agregarInicio(13);
    lista2.agregarInicio(12);
    lista2.agregarInicio(11);
    lista2.agregarInicio(10);

    lista2.imprimirAdelante();

    lista.fusionarOrdenadamente(lista2);
    lista.imprimirAdelante();
    
    return 0;
}