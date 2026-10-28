#include <iostream>
#include <vector>

/* INSERCION

Empiezo al final, y voy comparando 
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

void otroPropio(std::vector<double>& v) {
    int n = (int)v.size();
    for(int i= n-1; i >= 0; --i) {
        int clave = i;
        for(int j=i - 1; j >= 0; --j) {
            if(v[i] < v[j]) {
                swap(v,i,j);
                clave = j;
            }    
        }
    }
}

int main() {

    return 0;
}