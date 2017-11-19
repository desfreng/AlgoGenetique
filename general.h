#ifndef GENERAL_H
#define GENERAL_H

#include <exception>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#if defined (WIN32)
    #define Clear() system("cls")
#elif defined (linux)
    #define Clear() system("clear")
#endif

//Typedefs et enums des types utilisés

typedef unsigned int gene;
typedef unsigned int note;

enum Tirage {Uniforme, Proportionel};

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
        
    private:
        Cause m_cause;
        std::string m_message;
        
};

#endif // GENERAL_H
