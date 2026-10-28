#include <iostream>
#include <vector>

/* BUBLE SORT
Compara pares de valores para ver si el siguiente es mayor o menor que el anterior

va desde j =0; j < n - i - 1
Sabiendo que i avanza de uno en uno 
*/

void swap(std::vector<double>& v, int a, int b) {
    if(b >= (int)(v.size()) || a >= (int)v.size()) {
        return;
    } else if(a < 0 || b < 0) {
        return;
    } else {
        double pivote = v[a];
        v[a] = v[b];
        v[b] = pivote;
        return;
    }
}

void bubbleSort(std::vector<double>& v) {
    if((int)v.size() == 0 || (int)v.size() == 1) {
        // caso corto
        return;
    }
    
    for(int i=0; i < (int)v.size(); ++i) {
        bool swapped = false;
        for(int j = 0; j < (int)v.size()- i - 1; ++j) {
            if(v[j] > v[j+1]) {
                swap(v, j, j+1);
                swapped = true;
            } 
        }
        if(!swapped) {
            return; // no se hizo ningun swap
        }
    }
}


int main() {

    return 0;
}