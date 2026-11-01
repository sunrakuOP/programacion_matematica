#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>

// otra forma de resolver el problema => NODO TEMPLATE
template <typename T>

class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    Nodo(T d, Nodo<T>* s, Nodo<T>* a): dato(d), siguiente(s), anterior(a) {}
};

// ==========================

class TablaHash {
private:
    std::vector<std::list<std::pair<int, std::string>>> tablaHash;
    int m;

    int funcionHash(int clave) const {
        return clave % m;
    }

public: 
    // creamos la tabla hash con 17 posiciones de predeterminado
    TablaHash(int t = 17): m(t), tablaHash(std::vector<std::list<std::pair<int, std::string>>>(t)) {}

    void insertar(int clave, const std::string& valor) {
        int indice = funcionHash(clave);

        // comparar que en la lista del indice no hayan claves repetidas
        for(auto& par: tablaHash[indice]) {
            if(par.first == clave) {
                return;
            }
        }
        tablaHash[indice].push_back(std::make_pair(clave, valor));
    }

    bool buscar(int clave) {
        int indice = funcionHash(clave);
        for(auto& par: tablaHash[indice]) {
            if(par.first == clave) {
                return true;
            }
        }
        return false;
    }

    std::string buscarValor(int clave) {
        int indice = funcionHash(clave);

        for(auto& par: tablaHash[indice]) {
            if(par.first == clave) {
                return par.second;
            }
        }
        return "Inexistente";
    }

    void eliminar(int clave) {
        int indice = funcionHash(clave);
        for(auto it = tablaHash[indice].begin(); it != tablaHash[indice].end(); ++it) {
            if(it->first == clave) {
                tablaHash[indice].erase(it);
                return;
            }
        }
    }

    // recorrer toda la tabla por posicion, y la lista dentro de cada posicion
    void mostrarTabla() {
        for(int i=0; i < (int)tablaHash.size(); ++i) {
            std::cout<<"Indice: "<< i <<std::endl;
            for(auto& par: tablaHash[i]) {
                std::cout<<"Clave: "<<par.first<<", Valor: "<<par.second <<std::endl;
            }
        }
    }
};



int main() {

    return 0;
}