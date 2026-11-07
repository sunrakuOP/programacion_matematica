#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <map>
#include <algorithm>

/* INTEGRADOR (mapas, sets, stl basica)

Aprender a usar bien el tema de iteradores, como se manejan los mapas por abajo y los sets

Ejercicio: Es un inventario de una tienda y sus ventas. 
*/

class Producto {
private:    
    std::string codigo;
    std::string nombre;
    int precio;
    int stock;
public:
    Producto(const std::string& c, const std::string& n, int p, int s): codigo(c), nombre(n), precio(p), stock(s) {}

    std::string getCodigo() const { return codigo; }
    std::string getNombre() const { return nombre; }
    int getPrecio() const { return precio; }
    int getStock() const { return stock; }

    void setStock(int s) {
        if(this->stock == s || s < 0) {
            return;
        }
        this->stock = s;
    }

    bool descontarStock(int cantidadVenta) {
        if(this->stock < cantidadVenta) {
            return false;
        }
        this->stock -= cantidadVenta;
        return true;
    }

};

class Venta {
private:
    std::string codigoP;
    int cantidad;
    std::string nombreCliente;
    int precioUnitario;
public:
    Venta(const std::string& cp, int c, const std::string& nc, int pu): codigoP(cp), cantidad(c), nombreCliente(nc), precioUnitario(pu) {}

    std::string getCodigoProducto() const { return codigoP; }
    int getCantidad() const { return cantidad; }
    std::string getNombreCliente() const { return nombreCliente; }
    int getPrecioUnitario() const { return precioUnitario; }
};  



class Tienda {
private:
    std::unordered_map<std::string, Producto> inventario;

    // no puedo usar set porque es solo para ventas repetidas 
    std::vector<Venta> ventas;
public:
    Tienda() {} // ambos se crean vacios

    bool registrarProducto(const Producto& p) {
        std::string codigo = p.getCodigo();
        // verificar que el codigo existe, si ya esta devuelve el .second FALSE
        return inventario.try_emplace(codigo, p).second;
    }

    /* ACLARACION DE:      try_emplace, insert
        devuelven un par: pair<iterator, bool>
        Si ya existe el bool es false porque no se agrego, la diferencia con el insert y try_emplace es que el 
            try no crea el objeto hasta no saber que no existe (no deja copia)
    */


    // para poder separar de STOCK a INEXISTENTE (devolviendo int ambos devolverian 0) 
    std::pair<int, bool> consultarStock(const std::string& codigo) {
        // forma de saber si esta: puedo usar .count(p) para saber si existe, .find(p) si necesito pararme en el elemeto
        auto it = inventario.find(codigo);
        if(it == inventario.end()) {
            return {-1, false};
        }
        // it->second => Es el producto como tal
        return {it->second.getStock(), true};
    }


    bool vender(const std::string& codigo, int cantidadVenta, const std::string& nombreCliente) {
        auto it = inventario.find(codigo);
        if(it == inventario.end() || cantidadVenta <= 0) {
            return false;
        }
        // el metodo de descontar stock es false, asi que comprobar que no fallo por falta de stock por ejemplo
        if(!it->second.descontarStock(cantidadVenta)) {
            return false;
        }
        // sacar el precio del inventario
        int precio = it->second.getPrecio();
        ventas.push_back(Venta(codigo, cantidadVenta, nombreCliente, precio));
        return true;
    }

    // devolver los clientes distintos, el set los ordena y no admite repetidos
    std::set<std::string> clientesDistintos() const {
        std::set<std::string> clientesDist;

        for(auto it = ventas.begin(); it != ventas.end(); ++it) {
            std::string nombreCliente = it->getNombreCliente();
            clientesDist.insert(nombreCliente);
        }
        return clientesDist;
    }

    std::map<std::string, long> totalPorCliente() const {
        std::map<std::string, long>  resumen;
        for(auto it = ventas.begin(); it != ventas.end(); ++it) {
            std::string nombreCliente = it->getNombreCliente();

            // std::string codigoDeVenta = it->getCodigoProducto();

            int cantidad = it->getCantidad();
            int precio = it->getPrecioUnitario();

            /*  Esto lo hacia antes de agregar el campo directamente en Venta

            con el codigo de la venta va y busca en inventario el precio
            auto it2 = inventario.find(codigoDeVenta);
            if(it2 == inventario.end()) {
                continue; // no se encontro el producto, puede que lo hayan eliminado 
            }
            int precio = it2->second.getPrecio();

            */

            // no debo verificar si existe, solo con los [] si existe suma si no lo agrega
            resumen[nombreCliente] += static_cast<long>(precio) * cantidad;
        }
        return resumen;
    }

    std::pair<std::string, long> clienteMasGasto() {
        std::map<std::string, long> clientes = this->totalPorCliente();
        if(clientes.empty()) {
            return {"vacio", 0};
        }
        std::pair<std::string, long> mayorAcual; 
        for(auto it = clientes.begin(); it != clientes.end(); ++it) {
            long precio = it->second;
            if(precio >= mayorAcual.second) {
                std::string nombre = it->first;
                mayorAcual.first = nombre;
                mayorAcual.second = precio;
            }
        }
        return mayorAcual;
    }

    // ============== BORRAR CON ITERADORES =============

    void eliminarAgotados() {
        // recorrer el mapa y verificar cuales estan vacios
        for(auto it = inventario.begin(); it != inventario.end();) {
            if(it->second.getStock() == 0) {
                it = inventario.erase(it);
                continue;
            }
            it++;
        }
    }

    // eliminar usando erase en un vector (FORMA LENTA)
    void elimarVentasClienteOn2(const std::string& cliente) {
        for(auto it = ventas.begin(); it != ventas.end();) {
            if(it->getNombreCliente() == cliente) {
                it = ventas.erase(it);
                continue;
            }
            ++it;
        }
    }


    // eliminar usando remove_if (FORMA RAPIDA)
    void eliminarVentasClienteOn(const std::string& cliente) {
        ventas.erase(std::remove_if(ventas.begin(), ventas.end(),
            [&cliente](const Venta& v){ return cliente == v.getNombreCliente(); }),
        ventas.end());
    }



    // ========= CONSULTAS MEZCLADAS =================

    // productos nunca vendidos, debo ver cuales de los de Inventario no estan en Ventas
    std::vector<std::string> productosNuncaVendidos() const {
        std::unordered_set<std::string> vendidos; // []
        std::vector<std::string> noVendidos;
        for(int i=0; i < (int)ventas.size(); ++i) {
            // como no admite repetidos pues no discriminamos condiciones
            std::string codigo = ventas[i].getCodigoProducto();
            vendidos.insert(codigo);
        }

        // ya tenemos el set de los codigos que se vendieron
        for(auto it = inventario.begin(); it != inventario.end(); ++it) {
            if(vendidos.count(it->first)) {
                // si esta en vendididos pues no se agrega en el final
                continue;
            }
            noVendidos.push_back(it->first);
        }
        return noVendidos;
    }


    // devolver los 3 mas vendidos 
    std::vector<std::pair<int, std::string>> top3ProductosMasVendidos() const {
        std::unordered_map<std::string, int> topVendidos;
        std::vector<std::pair<int, std::string>> paresOrdenados; // para poder usar el sort con el int (.first) CREOOO

        // armar el mapa de los productos <codigo, cantidadVentas >
        for(auto it = ventas.begin(); it != ventas.end(); ++it) {
            std::string codigoProducto = it->getCodigoProducto();
            int cantidad = it->getCantidad();
            topVendidos[codigoProducto] += cantidad;
        }

        // ahora pasar ese mapa a un vector de pares 
        for(auto it = topVendidos.begin(); it != topVendidos.end(); ++it) {
            paresOrdenados.push_back({it->second, it->first});
        }
        
        // la idea es aprender a usar lambdas asi que ordenemoslo de mayor a menor 
        std::sort(paresOrdenados.begin(), paresOrdenados.end(),
            [](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b){return a > b; });

        int sizeV = (int)paresOrdenados.size();
        if(sizeV < 3) {
            return paresOrdenados;
        }
        paresOrdenados.erase(paresOrdenados.begin() + 3, paresOrdenados.end());
        return paresOrdenados;
        
        /*
        Otra forma de hacerlo:
        for(auto it = paresOrdenados.rbegin(); it != paresOrdenados.rend() + 3; ++it) 
        */       
    }   

    std::vector<std::string> codigosVendidosOrdenados() const {
        // usar el unique para eliminar repetidos, pasar los codigos de ventas al vector, ordenar, unique, eliminar
        std::vector<std::string> vectorCodigos;
        for(auto it = ventas.begin(); it != ventas.end(); ++it) {
            vectorCodigos.push_back(it->getCodigoProducto());
        }

        // ordenar el vector 
        std::sort(vectorCodigos.begin(), vectorCodigos.end());
        auto nuevoFin = std::unique(vectorCodigos.begin(), vectorCodigos.end());
        vectorCodigos.erase(nuevoFin, vectorCodigos.end());
        
        return vectorCodigos;
    }
};








int main() {

    return 0;
}