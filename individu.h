#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <algorithm>

#include "general.h"

// Classe qui s'occupe de la gestion d'un patrimoine

class Individu
{
    public:
        //Constructeurs
        Individu (const std::vector<gene>& patrimoine, bool random = true);
        Individu (const std::vector<gene>& patrimoine, unsigned int number);
        
        //Retourne le patrimoine
        const std::vector<gene>& getPatrimoine() const;
        
        //Retourne un allèle du patrimoine
        const gene& getAllele (size_t index) const;
        
        //Échange 2 allèles du patrimoine (Utilisé pour la mutation)
        void swapAlleles (size_t index1, size_t index2);
        
        //Retourne true si l'individu est noté (si sa note est différent de 0)
        bool haveNote() const;
        
        //Accéseurs de la variable m_note
        note getNote() const;
        void setNote (note value);
        
    private:
    
        //Marque l'individu comme non-noté
        void resetNote();
        
        std::vector<gene> m_pat;    //
        note m_note;                // Paramètres de la Classe
};

//Surcharge de l'opérateur '<<' pour afficher facilement un individu (ficher ou cout)
std::ostream& operator<< (std::ostream& os, const Individu& individu);

//Surcharge de l'opérateur '=='
bool operator== (const Individu& a, const Individu& b);

#endif // INDIVIDU_H
