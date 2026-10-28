#include <iostream>
#include <vector>

/* MERGE SORT (con el algoritmo del profesor)

La diferencia no es la mezlca, esa es casi la misma, es como viven los datos 
Aca es un solo arreglo "DATA", y no se copia, se marca un rango [left, right]

Devuelvo una funcion void, reordeno data en su lugar

*/

class MergeSort {
private:    
    std::vector<double> data;
public:
    MergeSort(std::vector<double>& d): data(d) {}

    // metodos de ordenamiento
    void merge(int left, int mid, int right) {
        std::vector<double> L(data.begin()+ left, data.begin() + mid + 1);
        std::vector<double> R(data.begin() + mid + 1, data.begin() + right + 1);

        int i = 0, j = 0, k = left;

        // misma comparacion que ya teniamos antes pero partiendo el arreglo en la mitad en vez de pasar 2
        while(i < L.size() && j < R.size()) {
            if(L[i] <= R[j]) {
                data[k] = L[i];
                ++i;
            } else {
                data[k] = R[j];
                ++j;
            }
            k++;
        }
        // ahora si quedan remanentes de alguno de los dos vectores se agregan como vienen
        while(i < L.size()) {
            data[k++] = L[i++];
        }
        while(j < R.size()) {
            data[k++] = R[j++];
        }
    }


    // paso dos numeros 
    void mergeSort(int left, int right) {
        if(left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(left, mid); 
            mergeSort(mid + 1, right);
            merge(left, mid, right);
        }
    }

    // punto de entrada: ordena todo el arreglo
    void sort() {
        mergeSort(0, (int)data.size() - 1);
    }

};

int main() {

    return 0;
}