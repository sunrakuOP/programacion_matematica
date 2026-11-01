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

// funcion de medicion de tiempo
template <typename F>
double medir(F f) {
    auto inicio = std::chrono::steady_clock::now();
    f();
    auto fin = std::chrono::steady_clock::now();

    return std::chrono::duration<double, std::milli>(fin - inicio).count();   // double, en milisegundos
}

// solo lo escribi para comparar tiempos

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

void selection(std::vector<double>& v) {
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
    std::vector<double> v1 = { 3,4,5,3,1,2,3,3,1,1,3,5,6,5 };
    std::vector<double> v2 = { 3,4,5,3,1,2,3,3,1,1,3,5,6,5 };

    double ms2 = medir([&]{ bubbleSort(v2); });
    std::cout << "burbuja: " << ms2 << " ms\n";
    
    double ms = medir([&]{ selection(v1); });
    std::cout << "selection: " << ms << " ms\n";

    return 0;
}