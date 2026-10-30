#include <iostream>
#include <string>
#include <limits>
#include "tablaHash.hpp"

using namespace std;

// Prototipos de funciones
void mostrarMenu();
void registrarUsuario(TablaHash& tabla);
void consultarSaldo(TablaHash& tabla);
void realizarTransferencia(TablaHash& tabla);
void consultarTransferido(TablaHash& tabla);
void consultarRecibido(TablaHash& tabla);
void eliminarUsuario(TablaHash& tabla);


// ==========================================
// MAIN
// ==========================================

int main() {

    TablaHash tabla(1009);
    int opcion;

    do {

        mostrarMenu();

        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nOpcion invalida.\n";
            opcion = -1;
            continue;
        }

        switch(opcion) {

            case 1:
                registrarUsuario(tabla);
                break;

            case 2:
                consultarSaldo(tabla);
                break;

            case 3:
                realizarTransferencia(tabla);
                break;

            case 4:
                consultarTransferido(tabla);
                break;

            case 5:
                consultarRecibido(tabla);
                break;

            case 6:
                eliminarUsuario(tabla);
                break;

            case 0:
                cout << "\nSaliendo del programa...\n";
                break;

            default:
                cout << "\nOpcion no valida. Intente nuevamente.\n";
        }

    } while(opcion != 0);

    return 0;
}


// ==========================================
// MOSTRAR MENU
// ==========================================

void mostrarMenu() {

    cout << "\n========== SISTEMA BANCARIO ==========\n";
    cout << "1. Registrar usuario\n";
    cout << "2. Consultar saldo\n";
    cout << "3. Transferir dinero\n";
    cout << "4. Consultar monto total transferido\n";
    cout << "5. Consultar monto total recibido\n";
    cout << "6. Eliminar usuario\n";
    cout << "0. Salir\n";
    cout << "======================================\n";

}


// ==========================================
// REGISTRAR USUARIO
// ==========================================

void registrarUsuario(TablaHash& tabla) {

    string llave;
    string nombre;
    int cedula;
    double saldo;

    cout << "\n========== REGISTRAR USUARIO ==========\n";

    cout << "Ingrese la llave: ";
    cin >> llave;

    if(!tabla.esLlaveValida(llave)) {
        cout << "Error: la llave no tiene un formato valido.\n";
        return;
    }

    if(tabla.existeLlave(llave)) {
        cout << "Error: la llave ya se encuentra registrada.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ingrese el nombre: ";
    getline(cin, nombre);

    cout << "Ingrese la cedula: ";
    cin >> cedula;

    if(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: cedula invalida.\n";
        return;
    }

    cout << "Ingrese el saldo inicial: ";
    cin >> saldo;

    if(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: saldo invalido.\n";
        return;
    }

    if(saldo < 0) {
        cout << "Error: el saldo no puede ser negativo.\n";
        return;
    }

    tabla.registrar(llave, nombre, cedula, saldo);

    cout << "\nUsuario registrado correctamente.\n";

}


// ==========================================
// CONSULTAR SALDO
// ==========================================

void consultarSaldo(TablaHash& tabla) {

    string llave;

    cout << "\n========== CONSULTAR SALDO ==========\n";

    cout << "Ingrese la llave del usuario: ";
    cin >> llave;

    double saldo = tabla.consultarSaldo(llave);

    if(saldo == -1) {
        cout << "Error: usuario no encontrado.\n";
    }
    else {
        cout << "Saldo disponible: $" << saldo << "\n";
    }

}


// ==========================================
// REALIZAR TRANSFERENCIA
// ==========================================

void realizarTransferencia(TablaHash& tabla) {

    string llavePasa;
    string llaveRecibe;
    double valor;

    cout << "\n========== REALIZAR TRANSFERENCIA ==========\n";

    cout << "Ingrese la llave del usuario que envia: ";
    cin >> llavePasa;

    cout << "Ingrese la llave del usuario que recibe: ";
    cin >> llaveRecibe;

    if(!tabla.existeLlave(llavePasa)) {
        cout << "Error: el usuario que envia no existe.\n";
        return;
    }

    if(!tabla.existeLlave(llaveRecibe)) {
        cout << "Error: el usuario que recibe no existe.\n";
        return;
    }

    if(llavePasa == llaveRecibe) {
        cout << "Error: no se puede transferir a la misma cuenta.\n";
        return;
    }

    cout << "Ingrese el valor a transferir: ";
    cin >> valor;

    if(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: valor invalido.\n";
        return;
    }

    if(valor <= 0) {
        cout << "Error: el valor debe ser mayor que cero.\n";
        return;
    }

    if(tabla.consultarSaldo(llavePasa) < valor) {
        cout << "Error: saldo insuficiente.\n";
        return;
    }

    tabla.transferirSaldo(llavePasa, llaveRecibe, valor);

    cout << "\nTransferencia realizada correctamente.\n";

}


// ==========================================
// CONSULTAR MONTO TOTAL TRANSFERIDO
// ==========================================

void consultarTransferido(TablaHash& tabla) {

    string llave;

    cout << "\n========== MONTO TOTAL TRANSFERIDO ==========\n";

    cout << "Ingrese la llave del usuario: ";
    cin >> llave;

    double total = tabla.montoTransferido(llave);

    if(total == -1) {
        cout << "Error: usuario no encontrado.\n";
    }
    else {
        cout << "Monto total transferido: $" << total << "\n";
    }

}


// ==========================================
// CONSULTAR MONTO TOTAL RECIBIDO
// ==========================================

void consultarRecibido(TablaHash& tabla) {

    string llave;

    cout << "\n========== MONTO TOTAL RECIBIDO ==========\n";

    cout << "Ingrese la llave del usuario: ";
    cin >> llave;

    double total = tabla.montoRecibido(llave);

    if(total == -1) {
        cout << "Error: usuario no encontrado.\n";
    }
    else {
        cout << "Monto total recibido: $" << total << "\n";
    }

}


// ==========================================
// ELIMINAR USUARIO
// ==========================================

void eliminarUsuario(TablaHash& tabla) {

    string llave;

    cout << "\n========== ELIMINAR USUARIO ==========\n";

    cout << "Ingrese la llave del usuario: ";
    cin >> llave;

    if(!tabla.existeLlave(llave)) {
        cout << "Error: el usuario no existe.\n";
        return;
    }

    tabla.eliminarUsario(llave);

    cout << "\nUsuario eliminado correctamente.\n";

}
