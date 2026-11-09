#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include "datos2d.hpp"

struct Nodo {
    int campo = -1;            // 0 = x, 1 = y ; -1 = hoja
    double umbral = 0;
    int clase = 0;
    std::unique_ptr<Nodo> izq, der;
};

double gini(int n0, int n1) {                               // 1 - sum p^2
    double n = n0 + n1;
    if (n == 0) return 0;
    double p0 = n0 / n, p1 = n1 / n;
    return 1 - p0 * p0 - p1 * p1;
}
double valor(const Punto& p, int campo) { return campo == 0 ? p.x : p.y; }

std::unique_ptr<Nodo> construir(const std::vector<Punto>& d, int prof, int maxProf) {
    auto nodo = std::make_unique<Nodo>();
    int c1 = 0;
    for (auto& p : d) c1 += p.clase;
    int c0 = d.size() - c1;
    nodo->clase = c1 > c0;
    if (prof == maxProf || c0 == 0 || c1 == 0 || d.size() < 2) return nodo;

    double mejor = gini(c0, c1), mejorUmbral = 0; int mejorCampo = -1;
    for (int campo = 0; campo < 2; ++campo)
        for (auto& cand : d) {                              // cada valor es un umbral candidato
            double u = valor(cand, campo);
            int l0 = 0, l1 = 0, r0 = 0, r1 = 0;
            for (auto& p : d) { bool izq = valor(p, campo) <= u; (izq ? (p.clase ? l1 : l0) : (p.clase ? r1 : r0))++; }
            if (l0 + l1 == 0 || r0 + r1 == 0) continue;
            double g = (gini(l0, l1) * (l0 + l1) + gini(r0, r1) * (r0 + r1)) / d.size();
            if (g < mejor - 1e-12) { mejor = g; mejorUmbral = u; mejorCampo = campo; }
        }
    if (mejorCampo < 0) return nodo;

    std::vector<Punto> izq, der;
    for (auto& p : d) (valor(p, mejorCampo) <= mejorUmbral ? izq : der).push_back(p);
    nodo->campo = mejorCampo; nodo->umbral = mejorUmbral;
    nodo->izq = construir(izq, prof + 1, maxProf);          // recursion: el mismo problema, mas chico
    nodo->der = construir(der, prof + 1, maxProf);
    return nodo;
}
int predecir(const Nodo* n, const Punto& p) {
    while (n->campo >= 0) n = valor(p, n->campo) <= n->umbral ? n->izq.get() : n->der.get();
    return n->clase;
}

int main() {
    auto train = anillo(400, 1), test = anillo(400, 2);
    std::cout << "profundidad   exactitud train   exactitud test\n";
    for (int prof : {1, 2, 3, 5, 8, 20}) {
        auto raiz = construir(train, 0, prof);
        int okT = 0, okS = 0;
        for (auto& p : train) okT += predecir(raiz.get(), p) == p.clase;
        for (auto& p : test) okS += predecir(raiz.get(), p) == p.clase;
        std::cout << "    " << prof << "              " << double(okT) / train.size() << "             " << double(okS) / test.size() << "\n";
    }
}
