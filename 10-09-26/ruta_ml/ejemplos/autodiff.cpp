#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_set>
#include <cmath>

struct Nodo;
using V = std::shared_ptr<Nodo>;

struct Nodo {
    double dato, grad = 0;
    std::vector<V> hijos;                                   // de quien depende este valor
    std::function<void()> retroceder = [] {};               // la regla de la cadena de ESTA operacion
    explicit Nodo(double d) : dato(d) {}
};
V valor(double d) { return std::make_shared<Nodo>(d); }

V operator+(V a, V b) {
    V o = valor(a->dato + b->dato);
    o->hijos = {a, b};
    Nodo* p = o.get();
    o->retroceder = [a, b, p] { a->grad += p->grad; b->grad += p->grad; };
    return o;
}
V operator*(V a, V b) {
    V o = valor(a->dato * b->dato);
    o->hijos = {a, b};
    Nodo* p = o.get();
    o->retroceder = [a, b, p] { a->grad += b->dato * p->grad; b->grad += a->dato * p->grad; };
    return o;
}
V tanh(V a) {
    V o = valor(std::tanh(a->dato));
    o->hijos = {a};
    Nodo* p = o.get();
    o->retroceder = [a, p] { a->grad += (1 - p->dato * p->dato) * p->grad; };
    return o;
}

void backward(V salida) {
    std::vector<Nodo*> orden;                               // orden topologico (DFS)
    std::unordered_set<Nodo*> visto;
    std::function<void(Nodo*)> visitar = [&](Nodo* n) {
        if (!visto.insert(n).second) return;
        for (auto& h : n->hijos) visitar(h.get());
        orden.push_back(n);
    };
    visitar(salida.get());
    salida->grad = 1;
    for (auto it = orden.rbegin(); it != orden.rend(); ++it) (*it)->retroceder();
}

int main() {
    V a = valor(2.0), b = valor(-3.0), c = valor(10.0);
    V f = tanh(a * b + c);                                  // f = tanh(a*b + c)
    backward(f);
    double z = 2.0 * -3.0 + 10.0, d = 1 - std::tanh(z) * std::tanh(z);   // derivada a mano
    std::cout << "f = " << f->dato << "\n";
    std::cout << "df/da = " << a->grad << "   (a mano: " << d * -3.0 << ")\n";
    std::cout << "df/db = " << b->grad << "   (a mano: " << d * 2.0 << ")\n";
    std::cout << "df/dc = " << c->grad << "   (a mano: " << d << ")\n";
}
