#include <iostream>
#include <map>

/* CLAVES COMPUESTAS

Un malla triangular son 3 triangulos, cada triangulo son 3 nodos. Los lados del triangulo son las aristas

        1
       / \
      /   \
     2-----3        Triángulo A: nodos (1, 2, 3)
      \   /
       \ /          Triángulo B: nodos (3, 2, 4)
        4

Ambos triangulos comparten nodos. 
!!!!! ARISTA = LADO (del triangulo)
Como se identifica la arista ????  => Con los NODOS que une 

Aristas de A: (1-2), (2-3), (3-1)
Aristas de B: (2-4), (3-2), (4-3)

Lo que una escribe como (2-3), otra lo escribe como (3-2)
!! LA ARISTA COMPARTIDA DEBE APARECER DOS VECES EN EL CONTADOR

COMO LO RESUELVO????
Normalizar, siempre guardar primero el numero menor, luego el mayor

(2,3) → (2,3)        (3,2) → (2,3)        ← ahora las dos dan la MISMA clave
(3,1) → (1,3)        (4,3) → (3,4)        (2,4) → (2,4)    (1,2) → (1,2)

las que comparten clave, se le suma el contador: PARA SABER QUE SON UNIONES

ENTONCES: 
Usarlo ordea
!!!! MAPA <clave, valor> => CLAVE es los nodos que une, ejemplo 1-2
                            VALOR es cuantos triangulos comparten la arista


!!!!!!!!!!!!!!!!!  Para que quiero saber cuantos triangulos comparten arista ?????

Porque los que tienen cuenta de 1 arista => BORDE (aca se le aplican las cargas etc...)
(solo puede compartir arista entre 2, no mas)


*/


int main() {

    return 0;
}