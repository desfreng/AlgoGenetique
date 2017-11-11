#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <algorithm>

#include "general.h"

template<typename T>
class Individu
{
    public:
        Individu (const std::vector<T>& patrimoine, bool random = true) {
            m_note = 0;
            
            m_pat = patrimoine;
            
            if (random) {
                std::random_device rd;
                std::shuffle (m_pat.begin(), m_pat.end(), rd);
            }
        }
        Individu (const std::vector<T>& patrimoine, unsigned int number) {
            m_note = 0;
            
            std::random_device rd;
            std::shuffle (m_pat.begin(), m_pat.end(), rd);
            
            for (unsigned int i = 0; i < number; ++i) {
                if (patrimoine.size() == 0) {
                    std::cerr << "Division par 0 à la ligne : " << __LINE__ << std::endl;
                }
                
                m_pat.push_back (patrimoine[rd() % patrimoine.size()]);
            }
            
        }
        
        std::vector<T> getPatrimoine() const {
            return m_pat;
        }
        T getAllele (size_t index) const {
            return m_pat[index];
        }
        
        void swapAlleles (size_t index1, size_t index2) {
            std::swap (m_pat[index1], m_pat[index2]);
            m_note = 0;
        }
        
        template<class Function>
        void apply (Function fonction) {
            m_note = static_cast<int> (fonction (this));
        }
        
        note getNote() const {
            return  m_note;
        }
        void setNote (note value) {
            m_note = value;
        }
        
    private:
        std::vector<T> m_pat;
        note m_note;
};


typedef Individu<unsigned int> UIndividu;

template<typename T>
std::ostream& operator<< (std::ostream& os, const Individu<T>& individu)
{
    os << "{";
    
    for (size_t i = 0; i < individu.getPatrimoine().size(); ++i) {
        if (i + 1 == individu.getPatrimoine().size()) {
            os << individu.getAllele (i) << "}";
        }
        else {
            os << individu.getAllele (i) << " ";
        }
    }
    
    os << " -> " << individu.getNote();
    
    return os;
}

template<typename T>
bool operator== (const Individu<T>& a, const Individu<T>& b)
{
    return (a.getPatrimoine() == b.getPatrimoine());
    
}

#endif // INDIVIDU_H
