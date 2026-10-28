#include <iostream>
#include <vector>

int busqudaBinaria(std::vector<int>& data, int valor) {
    int n = (int)data.size();
    int left = 0, right = n - 1;
    int mid = 0;
    while(left <= right ) {
        mid = left + (right - left) / 2;
        if(data[mid] == valor) {
            // si es el valor lo retorna de una vez
            return mid;
        } else if(data[mid] < valor) {
            // se descarta la mitad inferior
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int ternaria(std::vector<int>& data, int valor) {

}

int main() {

    return 0;
}