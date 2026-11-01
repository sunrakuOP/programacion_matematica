#include "tablaHash.hpp"

int TablaHash::funcionHash(const std::string& llave) const {
        unsigned long long h = 0;
        for(int i=0; i < (int)llave.size(); ++i) {
            h = ((31*h) + static_cast<unsigned char>(llave[i])) % (m);
        }
        return h;
    }

bool TablaHash::existeLlave(const std::string& llave) {
        int indice = funcionHash(llave);
        for(auto& par: tablaHash[indice]) {
            if(par.first == llave) {
                return true;
            }
        }
        return false;
    }
    
bool TablaHash::esLlaveValida(const std::string& llave) {
    if((int)llave.size() <= 1) {
        return false;
    } else if(llave[0] == '@' && (int)llave.size() <= 20) {
        for(int i=1; i < (int)llave.size(); ++i) {
            // is alnum es numero + letra
            if(!std::isalnum(static_cast<unsigned char>(llave[i]))) {
                return false;
            }
        }
        return true;
    } else if(llave[0] == '3' && (int)llave.size() == 10) {
        for(int i=1; i < (int)llave.size(); ++i) {
            // is digit es solo numeros
            if(!std::isdigit(static_cast<unsigned char>(llave[i]))) {
                return false;
            }
        }
        return true;
    }
    return false;
} 


void TablaHash::registrar(const std::string& llave, const std::string& nombre, int cedula, double saldo) {
    if(!esLlaveValida(llave)) {
        return;
    }
    int indice = funcionHash(llave);
    // como cada indice del vector es una lista, comparar que la llave no este
    for(auto& par: tablaHash[indice]) {
        if(par.first == llave) {
            return;
        }
    }

    // si no esta repetida lo agrego
    Usuario usuarioNuevo = Usuario(nombre, cedula, saldo);
    tablaHash[indice].push_back(std::make_pair(llave, usuarioNuevo));
} 


double TablaHash::consultarSaldo(const std::string& llave) {
    // buscar si esta la llave, solo lo hago una vez directo
    int indice = funcionHash(llave);
    for(auto& par: tablaHash[indice]) {
        if(par.first == llave) {
            return par.second.getSaldo();
        }
    }
    return -1;
}

void TablaHash::transferirSaldo(const std::string& llavePasa, const std::string& llaveRecibe, double saldoPasar) {
    if(llavePasa == llaveRecibe) {
        return;
    }
    int indice1 = funcionHash(llavePasa);
    int indice2 = funcionHash(llaveRecibe);
    
    if(!existeLlave(llavePasa) || !existeLlave(llaveRecibe)) {
        return;
    }

    for(auto& par: tablaHash[indice1]) {
        if(par.first == llavePasa) {
            if(par.second.getSaldo() < saldoPasar || saldoPasar <= 0) {
                return;
            }
            par.second.restarSaldo(saldoPasar);
        }
    }

    for(auto& par: tablaHash[indice2]) {
        if(par.first == llaveRecibe) {
            par.second.sumarSaldo(saldoPasar);
        }
    }   
}

double TablaHash::montoTransferido(const std::string& llave) {
    int indice = funcionHash(llave);

    for(auto& par: tablaHash[indice]) {
        if(par.first == llave) {
            return par.second.getTotTranf();
        }
    }
    return -1;
}

double TablaHash::montoRecibido(const std::string& llave) {
    int indice = funcionHash(llave);

    for(auto& par: tablaHash[indice]) {
        if(par.first == llave) {
            return par.second.getTotRecib();
        }
    }
    return -1;
}

void TablaHash::eliminarUsario(const std::string& llave) {
    // toca hacerlo con iteradores y erase(it)
    int indice = funcionHash(llave);
    for(auto it = tablaHash[indice].begin(); it != tablaHash[indice].end(); ++it) {
        if(it->first == llave) {
            tablaHash[indice].erase(it);
            return;
        }
    }
}

