#include "individu.h"

Individu::Individu (const std::vector<gene>& patrimoine, bool random)
{
    resetNote();
    
    m_pat = patrimoine;
    
    if (random) {
        std::random_device rd;
        std::shuffle (m_pat.begin(), m_pat.end(), rd);
    }
}
Individu::Individu (const std::vector<gene>& patrimoine, unsigned int number)
{
    resetNote();
    
    std::random_device rd;
    std::shuffle (m_pat.begin(), m_pat.end(), rd);
    
    for (unsigned int i = 0; i < number; ++i) {
        if (patrimoine.size() == 0) {
            std::cerr << "Division par 0 à la ligne : " << __LINE__ << std::endl;
        }
        
        m_pat.push_back (patrimoine[rd() % patrimoine.size()]);
    }
    
}

void Individu::resetPatrimoine (const std::vector<gene>& patrimoine)
{
    m_pat.clear();
    m_pat = patrimoine;
    
    resetNote();
}

std::vector<gene> Individu::getPatrimoine() const
{
    return m_pat;
}
gene Individu::getAllele (size_t index) const
{
    return m_pat[index];
}

void Individu::swapAlleles (size_t index1, size_t index2)
{
    std::swap (m_pat[index1], m_pat[index2]);
    resetNote();
}

bool Individu::haveNote() const
{
    return m_note != 0;
}

note Individu::getNote() const
{
    return  m_note;
}
void Individu::setNote (note value)
{
    m_note = value;
}

void Individu::resetNote()
{
    m_note = 0;
}

std::ostream& operator<< (std::ostream& os, const Individu& individu)
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
    
    if (individu.haveNote()) {
        os << " -> " << individu.getNote();
    }
    else {
        os << " -> Non noté";
    }
    
    return os;
}

bool operator== (const Individu& a, const Individu& b)
{
    return (a.getPatrimoine() == b.getPatrimoine());
    
}
