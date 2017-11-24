#ifndef GUICLASS_H
#define GUICLASS_H

#include <iostream>
#include <fstream>
#include <locale>
#include <limits>
#include <string>
#include <algorithm>
#include <thread>
#include <cstdlib> // Pour system()

#include "general.h"
#include "abstractnoteur.h"

class Population; // Je définit Temporairement la Classe Population pour l'utiliser
//Elle sera remplacée lors de la compilation par la 'vraie'

class GuiClass
{
    public:
        GuiClass();
        ~GuiClass();
        
        void configurer ();    //Menu de début (initialisation des paramètres
        void menu();    //Menu Principal
        
        void setPopulation (Population *pop);
        void setNoteur (AbstractNoteur *noteur);
        
        // Accesseurs des variables
        unsigned int getNbReponses() const;
        unsigned int getNbIndividus() const;
        double getFracSupr() const;
        double getFracMut() const;
        note getObjectif() const;
        Tirage typeTirage() const;
        unsigned int getCoefficient() const;
        bool debug() const;
        
    private:
        void pause();
        void clear();
        
        unsigned int _nbReponses;       //
        unsigned int _nbIndividus;      //
        double _fracSupr;               // Variables pour la population
        double _fracMut;                //
        note _objectif;                 //
        Tirage *_typeTirage;             //
        
        unsigned int _coefficient ;     //
        bool _debug;                    // Variables pour le Noteur
        
        Population *_pop;               //
        AbstractNoteur *_noteur;        // Pour accéder à leurs variables publiques et pour les afficher
        
        void setIndividu();             //
        void setReponses();             //
        void setFracMut();              //
        void setFracSupr();             // Fonctions pour que l'utilisateur puisse modifier
        void setObjectif();             // les paramètres via la console
        void setTirage();               //
        void setCoef();                 //
        void setDebug();                //
};

std::ostream& operator<< (std::ostream& os, const GuiClass& gui);

#endif // GUICLASS_H