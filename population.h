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

class Population
{

    public:
        typedef typename std::vector<Individu *>::iterator it;
        
        Population (size_t size, double fracSupr, double fracMut, note objectif = 1);
        ~Population();
        
        void select();
        void mating ();
        void mutation();
        
        void generate (const std::vector<gene>& genes, unsigned int nbgenes);
        void generate (const std::vector<gene>& genes, bool ramdom = true);
        
        void doGenerationCycle (AbstractNoteur& comp, size_t nbSolutions);
        void doGenerations (unsigned int nbGeneration, AbstractNoteur& comp);
        void noteAll (AbstractNoteur& comp);
        
        size_t size() const;
        
        it begin();
        it end();
        
        const std::vector<Individu> getSolutions() const;
        const std::vector<Individu *> getPopulation() const;
        
    private:
        note m_sommeNotes;
        
        
        note m_objectif;
        size_t m_popSize;
        double m_fracSupr;
        double m_fracMut;
        std::vector<Individu *> m_pop;
        std::vector<Individu> m_solutions;
};

std::ostream& operator<< (std::ostream& os, const Population& pop);

#endif // POPULATION_H
