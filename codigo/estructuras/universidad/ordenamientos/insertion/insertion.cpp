#include <iostream>
#include <vector>
/* INSERTION

Se asume que el primer elemento ya esta ordenado, de ahi se compara la zona no ordenada y se va organizando
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

void insertion(std::vector<double>& v) {
    for(int i=1; i < (int)v.size(); ++i) {
        int pivote = i;
        for(int j = i -1; j >= 0; --j) {
            if(v[pivote] < v[j]) {
                swap(v, pivote, j);
                pivote = j;
            }
        }
    }
}

int main() {

    return 0;
}