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
    int n = (int)data.size();
    int left = 0, right = n - 1;
    while(left <= right) {
        // center 1 esta a 1 / 3 desde la derecha
        int center1 = left + (right - left) / 3;
        int center2 = right + (left - right) / 3; 
        if(data[center1] == valor) {
            return center1;
        } else if(data[center2] == valor) {
            return center2;
        } else if(data[center1] < valor && valor < data[center2]) {
            left = center1 + 1;
            right = center2 - 1;
        } else if(data[center1] < valor && data[center2] < valor) {
            left = center2 + 1;
        } else {
            right = center1 - 1;
        }
    }
    // si no lo encuentra
    return -1;
}

int main() {

    return 0;
}