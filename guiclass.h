#ifndef GUICLASS_H
#define GUICLASS_H

#include <iostream>
#include <fstream>
#include <locale>
#include <limits>
#include <string>
#include <algorithm>

#include <cstdio>
#include <cstdlib>

#if defined (WIN32)
    #define Clear() system("cls")
#elif defined (linux)
    #define Clear() system("clear")
#endif

#include "general.h"

class GuiClass
{
    public:
        GuiClass();
        
        void init();
        void menu();
        
        unsigned int getNbReponses() const;
        unsigned int getNbIndividus() const;
        
        double getFracSupr() const;
        double getFracMut() const;
        
        note getObjectif() const;
        Tirage typeTirage() const;
        
        unsigned int getCoefficient() const;
        bool debug() const;
        
    private:
    
        unsigned int _nbReponses;   //
        unsigned int _nbIndividus;  //
        double _fracSupr;           // Variables pour la population
        double _fracMut;            //
        note _objectif;             //
        Tirage _typeTirage;         //
        
        unsigned int _coefficient ;  //
        bool _debug;                // Variables pour le Noteur
        
        void setIndividu();
        void setReponses();
        void setFracMut();
        void setFracSupr();
        void setObjectif();
        void setTirage();
        void setCoef();
        void setDebug();
};

std::ostream& operator<< (std::ostream& os, const GuiClass& gui);

#endif // GUICLASS_H