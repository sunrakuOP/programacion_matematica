#pragma once

class NodoDoble {
public:
    int valor;
    NodoDoble* siguiente;
    NodoDoble* anterior;

    NodoDoble(int v, NodoDoble* s, NodoDoble* a): valor(v), siguiente(s), anterior(a) {}
};
