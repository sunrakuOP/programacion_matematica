/*
Ejemplo de uso TAD lista implementación estructuras enlazadas simples.
*/

#include "practList.hpp"
#include <iostream>

// opera siempre y cuando infolista responda con algún dato
// en otro caso responde con -1
int minLista(Lista l){
    int menor = -1;
    if (!l.isEmptyLista()) {
        menor = l.searchPosLista(0);
        for(int i = 1; i <= l.lenLista(); i++){
            if (l.searchPosLista(i) < menor)
                menor = l.searchPosLista(i);
        }
    }
    return menor;
}


int main() {
    Lista l;

    l.insSortLista(20);
    l.insSortLista(7);
    l.insSortLista(9);
    l.insSortLista(5);
    l.insSortLista(12);
    l.insSortLista(31);
    l.insSortLista(4);
    l.insSortLista(2);


    cout << "Valor posicion 1: " << l.searchPosLista(1) << endl;
    cout << "Valor posicion 2: " << l.searchPosLista(2) << endl;
    cout << "Valor posicion 3: " << l.searchPosLista(3) << endl;
    cout << "Tamanio: " << l.lenLista() << endl;

    l.insertLista(100, 5);

    cout << "Tamanio: " << l.lenLista() << endl;

    if(l.isEmptyLista())
        cout << "Lista Vacia" << endl;
    else
        cout << "Lista No Vacia" << endl;

    // RETIRA EL ELEMENTO DE LA POSICIÓN TRES
    l.delLista(3);
    cout << endl;

    cout << "El menor elemento de la lista es:" << endl;
    cout << l.minLista() << endl;


    return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.