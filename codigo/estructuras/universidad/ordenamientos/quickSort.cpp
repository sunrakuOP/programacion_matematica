#include <iostream>
#include <vector>

/* QUICK SORT

Elige un valor (pivote), y hace el trabajo antes de cursar.

Idea:
Partir el arreglo de modo que el pivote quede en su lugar definitivo, 
con todo lo menor a su izquierda y todo lo mayor a su derecha.

cada particion pone al pivote en su lugar definitivo y nunca mas lo toca
*/

void swap(std::vector<int>& v, int a, int b) {
    if(b >= (int)(v.size()) || a >= (int)v.size()) {
        return;
    } else if(a < 0 || b < 0) {
        return;
    } else {
        int pivote = v[a];
        v[a] = v[b];
        v[b] = pivote;
        return;
    }
}

int partition(std::vector<int>& data, int low, int high) {
    int pivote = data[high];
    int i = low; // guarda el indice final donde va a quedar el pivote, j compara de inicio a fin
    for(int j = low; j < high; ++j) {
        if(data[j] <= pivote) {
            swap(data,i,j);
            i++;
        }
    }
    swap(data, i, high);
    return i;
}

void quickSort(std::vector<int>& data, int low, int high) {
    if(low < high) {
        int piv = partition(data, low, high);
        quickSort(data, low, piv - 1);
        quickSort(data, piv + 1, high);
    }
}

int main() {

    return 0;
}