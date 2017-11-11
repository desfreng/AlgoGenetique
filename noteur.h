#ifndef NOTEINDIVIDU_H
#define NOTEINDIVIDU_H

#include <cmath>
#include <iostream>

#include "abstractnoteur.h"

class Noteur : public AbstractNoteur
{
    public:
        Noteur();
        Noteur (double resultat, int coeficiant = 1, bool debug = false);
        Noteur (const Noteur& noteur);
        
        ~Noteur();
        
        note operator() (Individu *individu);
        
        note getSommeNotes() const;
        void resetSommeNotes();
        
    private :
    
        double resultat (const Individu *individu);
        double parenthese1 (const Individu *individu);
        double parenthese3 (const Individu  *individu);
        
        double m_resultat;
        int m_coef;
        bool m_debug;
};

#endif // NOTEINDIVIDU_H
