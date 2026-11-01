#include <iostream>
#include <limits>
#include <string>
#include "Historial.h"
using namespace std;

// Lee un entero sin quedar colgado si el usuario escribe letras.
// Si se acaba la entrada (EOF) devuelve 6 (salir) para no entrar en un bucle infinito.
int leerEntero() {
    int valor;
    while (!(cin >> valor)) {
        if (cin.eof()) return 6;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida, ingrese un numero: ";
    }
    return valor;
}

void mostrarActual(const Historial& historial) {
    const visitaPag* actual = historial.obtenerActual();
    cout << "--------------------" << endl;
    if (actual == nullptr) cout << "No quedan sitios abiertos" << endl;
    else cout << "Pagina actual: " << actual->obtenerSitio() << endl;
    cout << "--------------------" << endl;
}

int main() {
    cout << "Ingrese su ID de usuario: "; // Se usa el mismo ID para todas las visitas, como si se iniciara sesion
    int id = leerEntero();
    Historial historial(id);

    int opcion = 0;
    do {
        cout << "Seleccione una opcion:" << endl;
        cout << "1. Abrir un sitio" << endl;
        cout << "2. Ir atras" << endl;
        cout << "3. Ir adelante" << endl;
        cout << "4. Cerrar un sitio" << endl;
        cout << "5. Ver historial" << endl;
        cout << "6. Salir" << endl;
        opcion = leerEntero();

        switch (opcion) {
            case 1: {
                cout << "Ingrese el sitio que desea abrir: ";
                string url;
                cin >> url;
                historial.abrirSitio(url);
                mostrarActual(historial);
                break;
            }
            case 2:
                if (historial.irAtras()) mostrarActual(historial);
                else cout << "No hay ningun sitio anterior para ir atras." << endl;
                break;
            case 3:
                if (historial.irAdelante()) mostrarActual(historial);
                else cout << "No hay ningun sitio siguiente para ir adelante." << endl;
                break;
            case 4: {
                if (historial.contarSitios() == 0) {
                    cout << "No hay ningun sitio abierto para cerrar." << endl;
                    break;
                }
                int seleccion = 0;
                while (seleccion < 1 || seleccion > historial.contarSitios()) {
                    cout << "Seleccione un sitio para cerrar:" << endl;
                    historial.mostrarSitios();
                    seleccion = leerEntero();
                }
                historial.cerrarSitio(seleccion);
                mostrarActual(historial);
                break;
            }
            case 5:
                historial.mostrarHistorial();
                break;
            case 6:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 6);

    return 0; // ~Historial libera todos los nodos
}
// Las respuestas a las preguntas y la complejidad algoritmica se encuentran en el archivo PDF
