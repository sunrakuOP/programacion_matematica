#include <iostream>
#include <string>
#include <vector>

class NodoLista {
public:
    int clave;
    std::string valor;
    NodoLista* siguiente;
    NodoLista* anterior;

    NodoLista(int c, const std::string& v, NodoLista* s, NodoLista* a): 
        clave(c), valor(v), siguiente(s), anterior(a) {}

    int getClave() const { return clave; }
    std::string getValor() const { return valor; }
};

class ListaPropia {
private:    
    NodoLista* cabeza;
    NodoLista* cola;
public:
    ListaPropia(): cabeza(nullptr), cola(nullptr) {}
    ~ListaPropia() {
        NodoLista* auxiliar = cabeza;
        while(auxiliar != nullptr) {
            NodoLista* siguienteNodo = auxiliar->siguiente;
            delete auxiliar;
            auxiliar = siguienteNodo;
        }
    }
private:
    // auxiliar: borra todos los nodos y deja la lista vacia
    void vaciar() {
        NodoLista* auxiliar = cabeza;
        while(auxiliar != nullptr) {
            NodoLista* siguienteNodo = auxiliar->siguiente;
            delete auxiliar;
            auxiliar = siguienteNodo;
        }
        cabeza = nullptr;
        cola = nullptr;
    }

    // auxiliar: agrega al FINAL en O(1) gracias a cola; asi la copia conserva el orden
    void agregarAtras(int clave, const std::string& valor) {
        NodoLista* nuevo = new NodoLista(clave, valor, nullptr, cola);
        if(cola == nullptr) {       // lista vacia
            cabeza = nuevo;
        } else {
            cola->siguiente = nuevo;
        }
        cola = nuevo;
    }

public:
    // constructor de copia: copia PROFUNDA (nodos nuevos, no los mismos punteros)
    ListaPropia(const ListaPropia& otra): cabeza(nullptr), cola(nullptr) {
        for(NodoLista* p = otra.cabeza; p != nullptr; p = p->siguiente) {
            agregarAtras(p->clave, p->valor);
        }
    }

    // operador de asignacion
    ListaPropia& operator=(const ListaPropia& otra) {
        if(this == &otra) {         // autoasignacion: si no, borrariamos lo que queremos copiar
            return *this;
        }
        vaciar();                   // liberar lo que tenia esta lista
        for(NodoLista* p = otra.cabeza; p != nullptr; p = p->siguiente) {
            agregarAtras(p->clave, p->valor);
        }
        return *this;
    }

    void agregarAdelante(int clave, const std::string& valor) {
        if(cabeza == nullptr) {
            NodoLista* nuevo = new NodoLista(clave, valor, nullptr, nullptr);
            cabeza = nuevo;
            cola = nuevo;
            return;
        }
        NodoLista* nuevo = new NodoLista(clave, valor,cabeza, nullptr);
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    }

    bool buscarPorClave(int claveBuscar) {
        if(cabeza == nullptr) {
            return false;
        }
        NodoLista* auxiliar = cabeza;
        while(auxiliar != nullptr) {
            if(auxiliar->clave == claveBuscar) {
                return true;
            }
            auxiliar = auxiliar->siguiente;
        }
        return false;
    }


    void eliminar(int claveBuscar) {
        if(!buscarPorClave(claveBuscar)) {
            return;
        }
        // hay que encontrar el indice y limpiarlo, dejarlo sin nodo
        NodoLista* auxiliar = cabeza;

        while(auxiliar != nullptr) {
            NodoLista* siguienteNodo = auxiliar->siguiente;
            NodoLista* anteriorNodo = auxiliar->anterior;
            if(auxiliar->clave == claveBuscar) {
                if(auxiliar == cabeza && auxiliar == cola) {
                    delete auxiliar;
                    cabeza = nullptr;
                    cola = nullptr;
                } else if(auxiliar == cola) {
                    anteriorNodo->siguiente = nullptr;
                    cola = anteriorNodo;
                    delete auxiliar;
                } else if(auxiliar == cabeza) {
                    siguienteNodo->anterior = nullptr;
                    cabeza = siguienteNodo;
                    delete auxiliar;
                } else {
                    anteriorNodo->siguiente = siguienteNodo;
                    siguienteNodo->anterior = anteriorNodo;
                    delete auxiliar; 
                }
            }
            auxiliar = siguienteNodo;
        }
    }

    void mostrarLista() {
        if(cabeza == nullptr) {
            return;
        }
        NodoLista* auxiliar = cabeza;
        while(auxiliar != nullptr) {
            std::cout<<"Clave: "<<auxiliar->clave <<", valor: "<<auxiliar->valor<<std::endl;
            auxiliar = auxiliar->siguiente;
        }
    }
};

class TablaHash {
private:
    std::vector<ListaPropia> tabla; 
    int m;

    int funcionHash(int clave) const {
        // como es el mismo numero la clave, solo dividir con modulo
        return clave % m;
    }

public:
    TablaHash(int t = 17): m(t), tabla(std::vector<ListaPropia> (t))  {}
    ~TablaHash()  {}

    void insertar(int clave, const std::string& valor) {
        int indice = funcionHash(clave);
        if(tabla[indice].buscarPorClave(clave)) return;
        tabla[indice].agregarAdelante(clave, valor);
    }

    bool existe(int claveBuscar) {
        int indice = funcionHash(claveBuscar);
        if(!tabla[indice].buscarPorClave(claveBuscar)) {
            return false;
        }
        return true;
    }

    std::string buscar(int claveBuscar) {
        if(!existe(claveBuscar)){
            return "inexistente";
        }
        int indice = funcionHash(claveBuscar);
        return tabla[indice].
    }

    // calcula el indice, confirma si existe y elimina la lista
    void eliminarIndice(int claveBuscar) {
        if(!existe(claveBuscar)) {
            return;
        }
        int indice = funcionHash(claveBuscar);
        tabla[indice].eliminar(claveBuscar);
    }

    void mostrarTabla() {
        for(int i=0; i < m; ++i) {
            std::cout<<"Indice: "<<i<<std::endl;
            tabla[i].mostrarLista();
        }
    }
 };






int main() {

    return 0;
}