#ifndef SIMPLEXEPTION_H
#define SIMPLEXEPTION_H

#include <exception>
#include <string>

class SimplExeption : std::exception
{
    public:
    
        enum Cause {IndividuNonNote, DivisionParZero};
        
        SimplExeption (const std::string& phrase, Cause cause) {
            m_message = phrase;
            m_cause = cause;
        }
        
        const char *what() const noexcept {
            return m_message.c_str();
        }
        
        Cause cause() const noexcept {
            return m_cause;
        }
        
        ~SimplExeption () {
            m_message.clear();
        }
        
    private:
        Cause m_cause;
        std::string m_message;
        
};

#endif // SIMPLEXEPTION_H