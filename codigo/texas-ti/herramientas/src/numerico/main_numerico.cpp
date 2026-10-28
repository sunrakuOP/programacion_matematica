#include <iomanip>
#include <iostream>

void menuNumerico();

int main() {
    std::cout << std::setprecision(8);   // 8 cifras significativas en todos los resultados
    menuNumerico();
    return 0;
}
