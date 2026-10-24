#include <iostream>
#include <vector>

//prototipo de merge
void merge(std::vector<int>& v, int inicio, int medio, int fin);   // la escribimos despues


/* PREREQUISITO A LAMBDAS
Mi algoritmo de busqueda binaria exige DATOS ORDENADOS (orden logico)
    Si se entrega un vector desordenado debemos ordenarlo antes de poder hacer alguna busqueda

Ordenar es mas caro que buscar => O(n^2)

1. Oredenamiento por insercion:
    Mover los elementos e ir cambiandoles la posicion dependiendo de como sea su valor 
*/

// nos entregan un vector desordenado, la idea es irlo recorriendo y ordenandolo
void ordenamientoPorInsercion(std::vector<int>& v) {
    for(size_t i=1; i < v.size(); ++i) { // arrancamos desde v[1], primer elemento quieto
        int clave = v[i]; // elemento actual del arreglo
        int j = (int)i-1; // elemento anterior a clave, 1era iteracion: v[0]
        while(j >= 0 && v[j] > clave) { // para no pasar a ser negativo, compara que el anterior sea mayor al siguiente
            // corre del elemento j hacia atras 
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = clave;
    }
}

/* El merge sort parte en dos el vector hasta quedar en elementos separados 

Luego subo de vuelta cuando ya tengo los valores separados (mezclo pares con los mas alejados)

DIVIDIR (recursión hasta llegar a 1 elemento):

{5, 2, 8, 1, 9, 3}
        |
   split en mitades
        |
{5, 2, 8}          {1, 9, 3}
    |                   |
{5}  {2, 8}         {1}  {9, 3}
        |                    |
     {2} {8}              {9} {3}

MEZCLAR (subiendo de vuelta, combinando pares ordenados):

{2} + {8}       -> merge -> {2, 8}
{9} + {3}       -> merge -> {3, 9}

{5} + {2, 8}    -> merge -> {2, 5, 8}
{1} + {3, 9}    -> merge -> {1, 3, 9}

{2, 5, 8} + {1, 3, 9}  -> merge -> {1, 2, 3, 5, 8, 9}


Mientras agrupa y suma el mismo va ordenando y guardando hasta llegar al total de elementos otra vez 
*/

// 1. Recursivamente separa los elementos 
void mergesort(std::vector<int>& v, int inicio, int fin) {
    if((int)v.size() <= 1) return;
    
    int medio = inicio + (fin - inicio) / 2;
    mergesort(v, inicio, fin);
    mergesort(v, medio + 1, fin);
    merge(v, inicio, medio, fin);
}

// Une los elementos separados y ordenados
void merge(std::vector<int>& v, int inicio, int midad, int fin) {
    
}


int main() {

    return 0;
}