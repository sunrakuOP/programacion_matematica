#pragma once
#include <vector>
#include <unordered_map>
#include <queue>
#include "Nodo.hpp"
#include "ElementoBarra.hpp"

class Malla {
private:
    std::vector<Nodo*> nodos;
    std::unordered_map<int, Nodo*> idExternos;
    std::queue<ElementoBarra*> colaElementos;
public:
    Malla();
    ~Malla();

    void agregarNodo(double x, double y, double z, int id);
    void agregarBarra(double e, double a, int idNodo1, int idNodo2);
    void procesarCola();
};
