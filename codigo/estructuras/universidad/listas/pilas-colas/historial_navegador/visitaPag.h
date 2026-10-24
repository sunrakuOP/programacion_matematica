#ifndef VISITAPAG_H
#define VISITAPAG_H
#include <string>
#include <ctime>

class Historial;

// Nodo del historial: una visita a un sitio.
// Los enlaces son privados; solo Historial (friend) puede tocarlos.
class visitaPag {
    friend class Historial;
private:
    std::string sitioVisitado; // La ingresa el usuario
    int idUsuario;             // Se ingresa una vez al iniciar sesion
    std::time_t fechaVisita;   // Se obtiene con time() al crear el nodo
    visitaPag* siguiente;      // Visita mas reciente que esta
    visitaPag* anterior;       // Visita mas antigua que esta
public:
    visitaPag(std::string sitio, int id, std::time_t fecha)
        : sitioVisitado(sitio), idUsuario(id), fechaVisita(fecha),
          siguiente(nullptr), anterior(nullptr) {}

    std::string obtenerSitio() const { return sitioVisitado; }
    int obtenerIdUsuario() const { return idUsuario; }
    std::time_t obtenerFecha() const { return fechaVisita; }
};
#endif // VISITAPAG_H
