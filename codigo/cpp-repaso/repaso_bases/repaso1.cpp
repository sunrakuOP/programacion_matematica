#include <iostream>

// intercambiar dos enteros usando punteros 
void intercambiar(int* a, int* b) {
    // a y b son direcciones de memoria como tal
    int temp = *a;
    *a = *b; 
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    intercambiar(&x, &y);

}