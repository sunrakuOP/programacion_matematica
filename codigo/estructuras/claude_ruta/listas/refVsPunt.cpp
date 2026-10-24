#include <iostream>

/* YA TENEMOS NUEVA PANTALLA
El ultimo regalo de mi papa, con esta pantalla voy a terminar mi proyecto de grado, 
voy a terminar la carrera, me voy a graduar y voy a terminar su proyecto. LO JURO
*/

/* REFERENCIA VS PUNTERO

Variable: Guarda el valor que se almacena
    int x = 10;
Puntero: Guarda la direccion de memoria de la variable 
    int* ptr = &x;

Referencia:     int& r = x;
    Alias para la misma direccion de memoria que x (otro nombre para el mismo casillero)
    No puede ser nula, NUNCA SE PUEDE REAPUNTAR DESPUES

Cuando usar cada cosa?? (Puntero vs Referencia)
Referencia:
    Cuando tengo algo valido a lo que referirme, no debo re apuntar la variable 
    Mas simple y segura

Puntero:
    Cuando puede que no haya nada a lo que apuntar (nullptr)
    Cuando necesito reasignar la variabe


La Referencia como el puntero SON LA MISMA COSA PARA EL COMPILADOR (misma direccion de memoria)

*/

void intercambiarPuntero(int* a, int* b) {
    int temp = *a;
    *a = *b; 
    *b = temp;
}

void intercambiarReferencia(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// mas facil la sintaxis con referencias, mas intuitivo

int main() {


    return 0;
}