#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <algorithm>

#include "general.h"
//#include "abstractnoteur.h"

class Individu
{
    public:
        Individu (const std::vector<gene>& patrimoine, bool random = true);
        Individu (const std::vector<gene>& patrimoine, unsigned int number);
        
        void resetPatrimoine (const std::vector<gene>& patrimoine);
        
        std::vector<gene> getPatrimoine() const;
        gene getAllele (size_t index) const;
        
        void swapAlleles (size_t index1, size_t index2);
        
        //void apply (AbstractNoteur& fonction);
        
        note getNote() const;
        void setNote (note value);
        
    private:
    
        void resetNote();
        
        std::vector<gene> m_pat;
        note m_note;
};


std::ostream& operator<< (std::ostream& os, const Individu& individu);
bool operator== (const Individu& a, const Individu& b);

#endif // INDIVIDU_H
