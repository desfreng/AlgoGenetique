#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>

#include "individu.h"
#include "general.h"
#include "abstractnoteur.h"

/* Classe qui s'occupe de la gestion des individus.
 * Elle permet de réaliser des générations avec les fonctions :
 *      - select() (Sélection des individus)
 *      - mating() (Croisement des individus)
 *      - mutation() (Mutation des individus)
 * Un foncteur afin de noter les individus est néccesaire.
 * Il doit absolument hériter de la classe AbstractNoteur, et réimplémenter la surchage de 'l'opérateur ()'
 */

class Population
{
    public:
        typedef typename std::vector<Individu *>::iterator it;
        
        // Constructeur et Destructeur
        Population (size_t size, double fracSupr, double fracMut, Tirage tirageUniforme = Tirage::Proportionel, note objectif = 1);
        ~Population();
        
        // Fonctions utilisées pour générer une population
        void generation (const std::vector<gene>& genes, unsigned int nbgenes);
        void generation (const std::vector<gene>& genes, bool ramdom = true);
        
        // Fonctions utilisées pour réaliser des générations
        void doGenerationCycle (AbstractNoteur& comp, unsigned int nbSolutions);
        void doGenerations (unsigned int nbGeneration, AbstractNoteur& comp);
        
        // Fonction qui s'occupe de la sélection des individus
        void selection();
        
        // Fonction qui s'occupe du croisement des individus
        void croisement ();
        
        // Fonction qui s'occupe de la mutation des individus
        void mutation();
        
        // Aplique le foncteur 'noteur' à chaque individu de la population pour les noter
        void noteAll (AbstractNoteur& noteur);
        
        // Renvoi la taille théorique (elle varie lors de la selection avec la fonction Population::select() )
        size_t size() const;
        
        // Renvoi les itérateurs de début et de fin (pour itérer)
        it begin();
        it end();
        
        // Renvoi le type du tirage (Uniforme ou Proprtionel)
        Tirage typeSelection() const;
        
        unsigned int generation() const;
        
        // Renvoi les solutions trouvés
        const std::vector<Individu> solutions() const;
        
        // Renvoi la population
        const std::vector<Individu *> population() const;
        
    private:
    
        /* Fonction qui séléctione un individu aléatoirement
         * Elle sélectione uniformément lorsque Population::tirageUniforme est vrai
         * Sinon c'est une séléction aléatoire réalisé à partir des notes.
         * Plus l'individu à une note élevé plus il a une probabilité inportante d'être sélectioné (pour un croisement, une mutation, une supression)
         */
        it selectRandomIndividu();
        
        unsigned int _sommeNotes;
        
        bool _isNoted;
        
        unsigned int _nbGeneration;    //
        Tirage _typeSelection;          //
        note _objectif;                //
        size_t _popSize;               // Paramètres de la classe
        double _fracSupr;              //
        double _fracMut;               //
        
        std::vector<Individu *> _pop;      // Conteneur des Individus
        
        std::vector<Individu> _solutions;  // Conteneur des Solutions
};

// Surchage de l'opếrateur '<<' pour afficher facilement la population dans un flux (fichier ou cout)
std::ostream& operator<< (std::ostream& os, const Population& pop);


#endif // POPULATION_H
