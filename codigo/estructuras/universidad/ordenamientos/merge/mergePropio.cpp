#include <iostream>
#include <vector>

// ejemplo de factorial
int factorial(int n) {
    if(n == 0) return 1; 
    return n*factorial(n-1);
}

// borrar usando iteradores
/*
std::vector<double> mergeIntentoA(std::vector<double>& a, std::vector<double>& b) {
    std::vector<double> resultado;

    if((int)a.size() == 0) {
        return b;
    } else if((int)b.size() == 0) {
        return a;
    }

    for(int i=0; i < (int)a.size(); ++i) {
        for(int j=0; j < (int)b.size(); ++j) {
            if(a[i] > b[j]) {
                resultado.push_back(a[i]);
                a.erase(a.begin() + 0); // eliminar la primera posicion
            } else if(a[i] == b[j]) {
                // que hago en este caso? 
            } else {
                resultado.push_back(b[i]);
            }
        } 
    }
}
*/

std::vector<double> merge(std::vector<double>& a, std::vector<double>& b) {
    std::vector<double> resultado;
    int i = 0, j = 0;
    int n_a = (int)a.size(), n_b = (int)b.size();

    // solo para comparar si ambos tienen elementos
    while(i < n_a && j < n_b) {
        if(a[i] < b[j]) {
            resultado.push_back(a[i]);
            i++;
        } else if(a[i] == b[j]) {
            resultado.push_back(a[i]);
            resultado.push_back(b[j]);
            i++;
            j++;
        } else {  
            resultado.push_back(b[j]);
            j++;
        }
    }
    if(i < n_a) {
        for(int x = i; x < n_a; ++x) {
            resultado.push_back(a[x]);
        }
    } else if(j < n_b) {
        for(int y = j; y < n_b; ++y) {
            resultado.push_back(b[y]);
        }
    } 

    return resultado;
}


// metodo para partir el arreglo de a dos en dos 

std::vector<double> mergeSort(std::vector<double>& v) {
    int n = (int)v.size();
    std::vector<double> izquierda;
    std::vector<double> derecha;
    if(n <= 1) {
        return v;
    }
    int n_med = n / 2;

    for(int i=0; i< n_med; ++i) {
        izquierda.push_back(v[i]);
    }
    for(int j = n_med; j < n; ++j) {
        derecha.push_back(v[j]);
    }
    // debo oredenar la mitad izquierda y derecha antes
    izquierda = mergeSort(izquierda);
    derecha = mergeSort(derecha);
    return merge(izquierda, derecha);
}


int main() {
    std::vector<double> a = {1,6,7};
    std::vector<double> b = {2,3,10};

    std::vector<double> c = merge(a,b);

    for(auto x: c) {
        std::cout<< x <<", ";
    }

    return 0;
}