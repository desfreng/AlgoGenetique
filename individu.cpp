#include "individu.h"

//Constructeurs
Individu::Individu (const std::vector<gene>& patrimoine, bool random)
{
    resetNote();
    
    m_pat = patrimoine;
    
    // Mélange du patrimoine SANS doubles si random = true.
    // Exemple :
    //  patrimoine =    {1, 2, 3, 4, 5, 6, 7, 8, 9}
    //  m_pat =         {2, 5, 8, 6, 7, 1, 4, 9, 3}
    
    //  MAIS m_pat ≠    {2, 5, 2, 6, 7, 6, 4, 6, 3}
    //                   ¯     ¯  ¯     ¯     ¯
    
    if (random) {
        std::random_device rd;
        std::shuffle (m_pat.begin(), m_pat.end(), rd);
    }
}
Individu::Individu (const std::vector<gene>& patrimoine, unsigned int number)
{
    resetNote();
    
    std::random_device rd;
    
    // Création d'un patrimoine de number allèles AVEC doubles.
    
    // Exemple :
    //  patrimoine =    {1, 2, 3, 4, 5, 6, 7, 8} et number = 8
    //  m_pat =         {2, 5, 8, 6, 7, 1, 4, 9}
    //  OU
    //  m_pat =         {2, 5, 2, 6, 7, 1, 4, 9}
    //                   ¯     ¯
    
    for (unsigned int i = 0; i < number; ++i) {
    
        if (patrimoine.size() == 0) {
            throw SimplExeption ("Division par 0 à la ligne : " + std::to_string (__LINE__), SimplExeption::DivisionParZero);
        }
        
        m_pat.push_back (patrimoine[rd() % patrimoine.size()]); // Je tire au sort un allèle du tableau 'patrimoine' et je l'ajoute au mien
    }
    
}

//Retourne le patrimoine
const std::vector<gene>& Individu::getPatrimoine() const
{
    return m_pat;
}

//Retourne un allèle du patrimoine
const gene& Individu::getAllele (size_t index) const
{
    return m_pat[index];
}

//Échange 2 allèles du patrimoine (Utilisé pour la mutation)
void Individu::swapAlleles (size_t index1, size_t index2)
{
    std::swap (m_pat[index1], m_pat[index2]);
    resetNote();
}

//Retourne true si l'individu est noté (si sa note est différent de 0)
bool Individu::haveNote() const
{
    return m_note != 0;
}

//Accéseurs de la variable m_note
note Individu::getNote() const
{
    return  m_note;
}
void Individu::setNote (note value)
{
    m_note = value;
}

//Marque l'individu comme non-noté
void Individu::resetNote()
{
    m_note = 0;
}

//Surcharge de l'opérateur '<<' pour afficher facilement un individu (ficher ou cout)
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

//Surcharge de l'opérateur '=='
bool operator== (const Individu& a, const Individu& b)
{
    return (a.getPatrimoine() == b.getPatrimoine());
    
}
