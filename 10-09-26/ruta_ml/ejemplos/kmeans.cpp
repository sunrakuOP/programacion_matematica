#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

struct P { double x, y; };

int main() {
    std::mt19937 gen(11);
    std::normal_distribution<double> r(0, 0.8);
    P centros[3] = {{0, 0}, {6, 0}, {3, 5}};
    std::vector<P> datos;
    for (auto& c : centros) for (int i = 0; i < 100; ++i) datos.push_back({c.x + r(gen), c.y + r(gen)});

    const int K = 3;
    std::vector<P> mu = {datos[0], datos[150], datos[250]};   // inicializacion simple: 3 puntos cualquiera
    std::vector<int> asign(datos.size(), -1);
    for (int iter = 1; iter <= 100; ++iter) {
        bool cambio = false;
        for (size_t i = 0; i < datos.size(); ++i) {           // 1) asignar al centroide mas cercano
            int mejor = 0; double dm = 1e18;
            for (int k = 0; k < K; ++k) {
                double d = std::pow(datos[i].x - mu[k].x, 2) + std::pow(datos[i].y - mu[k].y, 2);
                if (d < dm) { dm = d; mejor = k; }
            }
            if (asign[i] != mejor) { asign[i] = mejor; cambio = true; }
        }
        P suma[K] = {}; int cuenta[K] = {};
        for (size_t i = 0; i < datos.size(); ++i) { suma[asign[i]].x += datos[i].x; suma[asign[i]].y += datos[i].y; ++cuenta[asign[i]]; }
        for (int k = 0; k < K; ++k) if (cuenta[k]) mu[k] = {suma[k].x / cuenta[k], suma[k].y / cuenta[k]};   // 2) mover
        if (!cambio) {
            double inercia = 0;
            for (size_t i = 0; i < datos.size(); ++i) inercia += std::pow(datos[i].x - mu[asign[i]].x, 2) + std::pow(datos[i].y - mu[asign[i]].y, 2);
            std::sort(mu.begin(), mu.end(), [](const P& a, const P& b) { return a.x < b.x; });
            std::cout << "convergio en " << iter << " iteraciones, inercia = " << inercia << "\n";
            for (auto& m : mu) std::cout << "centroide (" << m.x << ", " << m.y << ")\n";
            break;
        }
    }
}
