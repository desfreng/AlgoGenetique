#ifndef NOTEINDIVIDU_H
#define NOTEINDIVIDU_H

#include <cmath>
#include <iostream>

#include "abstractnoteur.h"
#include "guiclass.h"

// Foncteur qui note les individus.
// Il hérite de AbstractNoteur

class Noteur : public AbstractNoteur
{
    public:
        //Constructeurs
        Noteur();
        Noteur (const GuiClass& gui);
        Noteur (double resultat, double coefficient = 1, bool debug = false);
        
        //Destructeur
        ~Noteur();
        
        //Met à jour le flux utilisé pour la debug
        void setOstream (std::ostream& os, bool force = false);
        
        //surcharge de "l'operateur ()", qui note l'individu passé en paramètre.
        note operator() (Individu *individu);
        
    private :
    
        double m_resultat;      //
        double m_coef;          // Paramètres Constant de la Classe
        bool m_debug;           //
        std::ostream *m_os;     //
};

#endif // NOTEINDIVIDU_H
