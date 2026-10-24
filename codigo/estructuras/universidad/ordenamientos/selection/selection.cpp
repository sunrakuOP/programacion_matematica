#include <iostream>
#include <vector>
#include <chrono>

/* SELECTION ORDENAMIENTO

Se busca en cada pasada el menor de lo que quede del arreglo por ordenar, y se cambia de indice, y asi hasta n-1
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

void selection(std::vector<double>& v) {
    // medir el iincio de la funcion
    if((int)v.size() <= 1) {
        return; // si es 1 devuelve lo mismo, ignora los negativo o si esta vacio
    }

    for(int i=0; i < (int)v.size(); ++i) {
        int indice = i;
        for(int j=i+1; j < (int)v.size(); ++j) {
            if(v[indice] > v[j]) {
                indice = j;
            } 
        }
        
        swap(v, i, indice);
    }
}


int main() {

    return 0;
}