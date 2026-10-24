// incluyo los .hpp menos la base (ElementoFinito), internamente llama a los otros 
#include "ElementoTriangular.hpp"
#include "ElementoCuadrilatero.hpp"
#include <iostream>
#include <memory>
#include <vector>

Matriz<double> ensamblar(const std::vector<std::unique_ptr<ElementoFinito>>& malla) {
    Matriz<double> resultante(2, 2);
    for (const auto& e : malla) {
        resultante = resultante + e->matrizLocal();
    }
    return resultante;
}

int main() {
    std::vector<std::unique_ptr<ElementoFinito>> elementos;
    elementos.push_back(std::make_unique<ElementoTriangular>(2.0, 3.0));
    elementos.push_back(std::make_unique<ElementoCuadrilatero>(4.0, 5.0));

    Matriz<double> global = ensamblar(elementos);
    std::cout << global(0,0) << " " << global(1,1) << "\n";

    return 0;
}
