#include "../include/Lenguaje.hpp"

Lenguaje::Lenguaje() {

}

Lenguaje::Lenguaje(const int id) {
    set_id(id);
}

Lenguaje::~Lenguaje() {

}

void Lenguaje::set_id(const int& id) {
    _id = id;
}

const int& Lenguaje::get_id() {
    return _id;
}

Lenguaje::Lenguaje(const Lenguaje& lenguaje) {
    *this = lenguaje;
}

Lenguaje::Lenguaje(std::string s) {
    definir(s);
}

const std::set<std::string>& Lenguaje::get_cadenas() {
    return _cadenas;
}

void Lenguaje::insertar_cadena(const std::string& cadena) {
    _cadenas.insert(cadena);
}

void Lenguaje::definir(std::string& lenguaje) {  
    
    if(lenguaje == "{}")
        _vacio = true;
    else {
        _vacio = false;
        std::string str = "";
        int i = 0;
        for(char c: lenguaje) {
            
            if(c != '{' && c != ',' && c != ' ') {
                str += c;
                
                if (c == '}'){
                    str = str.substr(0, str.length() - 1);
                    _cadenas.insert(str); 
                    str = "";
                }
            }
            if (c == ',') {
                _cadenas.insert(str); 
                str = "";
            }           
        }
    }    
}

const Lenguaje Lenguaje::inversa() {
    Lenguaje resultado(_id + 1);
    std::string cadena="";

    for(std::string s: _cadenas) {
        std::reverse(s.begin(), s.end());
        resultado.insertar_cadena(s);
    }

    return resultado;
}

const Lenguaje Lenguaje::operator* (const Lenguaje& lenguaje) {
    Lenguaje resultado(lenguaje._id + 1);
    std::string cadena="";
    for(std::string cadena_L1 : _cadenas) {
        for(std::string cadena_L2 : lenguaje._cadenas) {
            if(cadena_L1 == CADENA_VACIA)
                cadena = cadena_L2;
            if(cadena_L2 == CADENA_VACIA)
                cadena = cadena_L1;
            if(cadena_L1 != CADENA_VACIA && cadena_L2 != CADENA_VACIA)
                cadena = cadena_L1 + cadena_L2;
            
            resultado.insertar_cadena(cadena);
        }
    }
    return resultado;
}

const Lenguaje Lenguaje::lunion(const Lenguaje& lenguaje) {
    
    Lenguaje resultado(lenguaje._id + 1);
    std::set<std::string> lunion;
    

    set_union(_cadenas.begin(), _cadenas.end(), 
                    lenguaje._cadenas.begin(), lenguaje._cadenas.end(),
                    std::inserter(lunion, lunion.begin()));
    resultado._cadenas = lunion;

    return resultado;
}

const Lenguaje Lenguaje::interseccion(const Lenguaje& lenguaje) {
    Lenguaje resultado(lenguaje._id + 1);
    std::set<std::string> interseccion;
    
    set_intersection(_cadenas.begin(), _cadenas.end(), 
                    lenguaje._cadenas.begin(), lenguaje._cadenas.end(),
                    std::inserter(interseccion, interseccion.begin()));
    resultado._cadenas = interseccion;
    return resultado;
}

const Lenguaje Lenguaje::operator- (const Lenguaje& lenguaje) {
    Lenguaje resultado(lenguaje._id + 1);
    std::set<std::string> diferencia;
    
    set_difference(_cadenas.begin(), _cadenas.end(), 
                    lenguaje._cadenas.begin(), lenguaje._cadenas.end(),
                    std::inserter(diferencia, diferencia.begin()));
    resultado._cadenas = diferencia;
    return resultado;
}

const bool Lenguaje::sublenguaje(const Lenguaje& lenguaje) {
    Lenguaje resultado(lenguaje._id + 1);
    resultado = *this - lenguaje;
    return (*this - resultado)._cadenas.size() == lenguaje._cadenas.size();
}

const bool Lenguaje::operator == (const Lenguaje& lenguaje) {
    return _cadenas == lenguaje._cadenas;
}

const Lenguaje Lenguaje::potencia(const int& exponente) {
    Lenguaje resultado = *this;
    resultado.set_id(_id + 1);
    
    if (exponente == 0) resultado = Lenguaje("");
    
    if (exponente == 1) resultado = *this;

    if (exponente > 1) {
        for (int i = 2; i <= exponente; i++) {
            resultado = resultado * resultado;
        }
    }    

    return resultado;
}

const Lenguaje Lenguaje::kleene() {
    Lenguaje resultado = *this;
    resultado.set_id(_id + 1);
    resultado.insertar_cadena(CADENA_VACIA);
    
    // CIERRE DE KLEENE INFINITO
    // resultado = resultado.potencia(std::numeric_limits<int>::max());
    
    // CIERRE DE KLEENE LIMITADO
    resultado = resultado.potencia(5);
    resultado.insertar_cadena("...");    

    return resultado;
}

std::ostream& operator << (std::ostream& os, const Lenguaje& lenguaje) {        
    os << "L" << lenguaje._id << " = {";
    if(!lenguaje._vacio) {
        int i = 0;

        for(std::string s: lenguaje._cadenas) {            
            os << s;
            if (i < lenguaje._cadenas.size() - 1)
                os << ", ";
            i++;
        }
    }
    
    os << "}";

    return os;
}