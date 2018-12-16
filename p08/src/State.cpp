#include "../include/State.hpp"

/**
 * @brief Construct a new State:: State object
 * Constructor por defecto
 * 
 */
State::State() {}

/**
 * @brief Construct a new State:: State object
 * Constructor de copia
 * 
 * @param state 
 */
State::State(const State& state) {
    *this = state;
}

/**
 * @brief Destroy the State:: State object
 * Destructor
 */
State::~State() {
    transitions_.clear();
}

/**
 * @brief Obtener el identificador del estado
 * 
 * @return const unsigned& State::getn 
 */
const unsigned int& State::getid() {
    return id_;
}

/**
 * @brief Obtener tipo de estado, 
 * si es 1 es de aceptación
 * 
 * @return const unsigned& State::gettype 
 */
const unsigned int& State::gettype()  {
    return type_;
}

/**
 * @brief Obtener nº de transiciones del estado
 * 
 * @return const unsigned& State::getntransitions 
 */
const unsigned int& State::getntransitions() {
    return ntransitions_;
}

/**
 * @brief Obtener el conjunto de transiciones del estado
 * 
 * @return const set<Transition>& 
 */
const set<Transition>& State::gettransitions() {
    return transitions_;
}

/**
 * @brief Obtener siguiente estado transitando con un símbolo dado
 * 
 * @return const unsigned& State::next símbolo con que se transita
 */
const unsigned int& State::next(const char& symbol) {
    
    for(Transition t: transitions_) {
        if(t.getsymbol() == symbol)
            return t.gettostate();
    }
    
}

/**
 * @brief Establecer identificador del estado
 * 
 * @param int 
 */
void State::setid(unsigned int& id) {
    id_ = id;
}

/**
 * @brief Establecer tipo de estado
 * 
 * @param int 1 aceptación, 0 no aceptación
 */
void State::settype(unsigned int& type) {
    type_ = type;
}

/**
 * @brief Establecer nº de transiciones
 * 
 * @param int nº de transiciones
 */
void State::setntransitions(unsigned int& ntransitions) {
    ntransitions_ = ntransitions;
}

/**
 * @brief Insertar transición
 * 
 * @param t transición
 */
void State::inserttransitions(Transition& t) {
    transitions_.insert(t);
}

/**
 * @brief Comprobar si es un estado de muerte
 * 
 * @return true 
 * @return false 
 */
bool State::deadstate() {
    if (type_ == 1)
        return false;

    if (transitions_.size() == 0)
      return true;

    for(int i = 0; i < this->transitions_.size(); i++) {

        set<Transition>::iterator it = transitions_.begin();
        advance(it, i);
        Transition x = *it;

        if(x.gettostate() != id_) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Sobrecarga del operador ==
 * 
 * @param state 
 * @return int 
 */
int State::operator==(const State &state) const
{
   if( id_ != state.id_) return 0;
   
   return 1;
}

/**
 * @brief Sobrecargar del operador <
 * 
 * @param state 
 * @return int 
 */
int State::operator<(const State &state) const
{
   if(id_ == state.id_) return 1;
   if(id_ < state.id_) return 1;
   return 0;
}

/**
 * @brief Sobrecarga del operador de salida
 * 
 * @param os cadena resultante
 * @param state 
 * @return ostream& 
 */
ostream& operator << (ostream& os, const State& state) {

    os << state.id_ << " " << state.type_ << " " << state.transitions_.size() << " ";

    for(auto t: state.transitions_) {
        os << t;
    }

    return os;
}
