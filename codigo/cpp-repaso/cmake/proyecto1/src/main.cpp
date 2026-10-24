#include "Vector2D.hpp"
#include <iostream>

int main() {
    Vector2D a(1, 2), b(3, 4);
    std::cout << (a + b).magnitud() << "\n";
}
