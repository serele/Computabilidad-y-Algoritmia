#pragma once

#include <iostream>

using namespace std;

/**
 * @brief Representa una transición de un NFA
 * 
 */
class Transition {

    private:
        char symbol_;           //símbolo entrante
        unsigned int toState_;  //estado al que se transita
        bool visited_;  

    public:
        Transition();                       // constructor por defecto
        Transition(char, unsigned int);     // constructor por parámetros
        Transition(const Transition &t);    // constructor de copia
        ~Transition();                      // destructor

        // getters y setters
        const char& getsymbol();
        const unsigned int& gettoState();
        const bool& getvisited();

        void setsymbol(char &);
        void settoState(int &);
        void setvisited(bool);

        bool is_epsilon() const; // epsilon-transición

        Transition& operator=(const Transition &t); // sobrecarga del operador =
        int operator==(const Transition &t) const;  // sobrecarga del operador ==
        int operator<(const Transition &t) const;   // sobrecarga del operador <

    // sobrecarga del operador de salida
    friend ostream& operator << (ostream &, const Transition &);
};
