#ifndef HISTORIAL_H
#define HISTORIAL_H
#include <string>
#include "visitaPag.h"

// Historial de navegacion: lista doblemente enlazada con un cursor (actual).
//   ultimo -> visita mas reciente (el "tope" de la pila de visitas)
//   actual -> pagina que se esta viendo (puede estar antes de ultimo si se fue atras)
class Historial {
private:
    visitaPag* ultimo;
    visitaPag* actual;
    int idUsuario;
    int cantidad;
public:
    explicit Historial(int id);
    ~Historial();
    // Regla de los tres: copiar el historial duplicaria punteros y liberaria dos veces.
    Historial(const Historial&) = delete;
    Historial& operator=(const Historial&) = delete;

    // Post: la pagina nueva queda como actual y como ultima; lo que habia
    // "adelante" de la actual se descarta (igual que un navegador real).
    void abrirSitio(const std::string& sitio);

    // Devuelven false (sin cambios) si no hay a donde ir.
    bool irAtras();
    bool irAdelante();

    // Pre: 1 <= posicion <= cantidad (1 = la visita mas reciente). Devuelve false si no se cumple.
    // Si se cierra la actual, la actual pasa a la anterior (o a la siguiente si no hay anterior).
    bool cerrarSitio(int posicion);

    void mostrarHistorial() const;
    void mostrarSitios() const; // lista numerada para elegir cual cerrar

    // nullptr si el historial esta vacio.
    const visitaPag* obtenerActual() const;
    int contarSitios() const;
};
#endif // HISTORIAL_H
