#ifndef GENERAL_H
#define GENERAL_H

#include <exception>
#include <string>
#include <iostream>

//Typedefs des types utilisés

typedef unsigned int gene;
typedef unsigned int note;

// Classe simple pour gérer les différents types de tirage

class Tirage
{
    public :
        enum Mode {Uniforme, Proportionel};
        
        Tirage();
        Tirage (Mode mode) {
            _mode = mode;
        }
        
        std::string tirageToString () const {
            if (_mode == Proportionel) {
                return "Proportionel";
            }
            
            if (_mode == Uniforme) {
                return "Uniforme";
            }
            
            return "Inconnu !";
        }
        
        Mode operator() () const {
            return _mode;
        }
        
        bool operator== (const Tirage& a) {
            return a() == (*this)();
        }
        
    private:
        Mode _mode;
};

/* Classe simple pour gérer les exeptions
 * Hérite de std::exception
 */

class SimplExeption : std::exception
{
    public:
    
        enum Cause {IndividuNonNote, DivisionParZero};
        
        SimplExeption (const std::string& phrase, Cause cause) {
            m_message = phrase;
            m_cause = cause;
        }
        ~SimplExeption () {
            m_message.clear();
        }
        
        const char *what() const noexcept {
            return m_message.c_str();
        }
        
        Cause cause() const noexcept {
            return m_cause;
        }
        
        std::string causetoString() const noexcept {
            switch (m_cause) {
                case IndividuNonNote:
                    return "Individu Non Noté !";
                    
                case DivisionParZero :
                    return "Division Par Zero !";
                    
                default:
                    return "Inconnu !";
            }
            
        }
        
        
    private:
        Cause m_cause;
        std::string m_message;
        
};

#endif // GENERAL_H
