#ifndef SIMPLEXEPTION_H
#define SIMPLEXEPTION_H

#include <exception>
#include <string>

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

#endif // SIMPLEXEPTION_H