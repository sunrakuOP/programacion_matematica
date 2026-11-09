#include <iostream>

// f(x) = (x - 3)^2   ->   f'(x) = 2(x - 3)   ->   minimo en x = 3
int main() {
    for (double lr : {0.1, 0.9, 1.0, 1.1}) {
        double x = 0.0;
        for (int it = 0; it < 20; ++it) x -= lr * 2 * (x - 3);
        std::cout << "lr = " << lr << "   x tras 20 pasos = " << x << "\n";
    }
}
