#include "population.h"

Population::Population (size_t size, double fracSupr, double fracMut, note objectif) : isNoted (false),  m_objectif (objectif), m_popSize (size), m_fracSupr (fracSupr), m_fracMut (fracMut) {}
Population::~Population()
{
    for (Individu *a : m_pop) {
        delete a;
        a = 0;
    }
}

void Population::generate (const std::vector<gene>& genes, unsigned int nbgenes)
{
    m_pop.clear();
    
    for (size_t i = 0; i < m_popSize; ++i) {
        m_pop.push_back (new Individu (genes, nbgenes));
    }
    
    isNoted = false;
}
void Population::generate (const std::vector<gene>& genes, bool ramdom)
{
    m_pop.clear();
    
    for (size_t i = 0; i < m_popSize; ++i) {
        m_pop.push_back (new Individu (genes, ramdom));
    }
    
    isNoted = false;
    
}

void Population::doGenerationCycle (AbstractNoteur& comp, size_t nbSolutions)
{
    unsigned int i = 1;
    
    while (m_solutions.size() <= nbSolutions - 1) {
        std::cout << "Generation n° " << i << std::endl;
        noteAll (comp);
        select();
        noteAll (comp);
        mating();
        noteAll (comp);
        mutation();
        ++i;
    }
}
void Population::doGenerations (unsigned int nbGeneration, AbstractNoteur& comp)
{

    for (unsigned int i = 0; i < nbGeneration; ++i) {
        std::cout << "Generation n° " << i + 1 << std::endl;
        select();
        noteAll (comp);
        mating();
        noteAll (comp);
        mutation();
        noteAll (comp);
    }
}

void Population::noteAll (AbstractNoteur& comp)
{

    comp.resetSommeNotes();
    
    for (auto a : m_pop) {
        a->setNote (comp (a));
        
        if (a->getNote() == m_objectif) {
            if (std::find (m_solutions.begin(), m_solutions.end(), *a) == m_solutions.end()) {
                m_solutions.push_back (*a);
            }
        }
    }
    
    isNoted = true;
    m_sommeNotes = comp.getSommeNotes();
}

size_t Population::size() const
{
    return m_popSize;
}

Population::it Population::begin()
{
    return m_pop.begin();
}
Population::it Population::end()
{
    return m_pop.end();
}

const std::vector<Individu> Population::getSolutions() const
{
    return m_solutions;
}
const std::vector<Individu *> Population::getPopulation() const
{
    return m_pop;
}

void Population::select()
{

    std::random_device rd;
    unsigned int sommeNotesTemp = 0;
    
    unsigned int range = m_sommeNotes;
    
    for (int i = 0; i < std::ceil (static_cast<double> (m_popSize) * m_fracSupr); ++i) {
        if (range == 0) {
            std::cerr << "Division par 0 à la ligne : " << __LINE__ << std::endl;
        }
        
        unsigned int n = rd() % range;
        
        for (it it = m_pop.begin(); it != m_pop.end(); ++it) {
        
        
            if (n < sommeNotesTemp +  (*it)->getNote() && sommeNotesTemp <= n) {
                range -= (*it)->getNote();
                delete *it;
                m_pop.erase (it);
                sommeNotesTemp = 0;
                break;
            }
            
            sommeNotesTemp += (*it)->getNote();
        }
    }
    
}
void Population::mating ()
{
    std::random_device rd;
    
    size_t actualPopSize = m_pop.size();
    
    for (unsigned int i = 0; i < m_popSize - actualPopSize; i++) {
    
        int crossPoint;
        
        do {
            crossPoint = rd() % 8;
        } while (crossPoint <= 0 || crossPoint >= 7);
        
        if (actualPopSize == 0) {
            std::cerr << "Division par 0 à la ligne : " << __LINE__ << std::endl;
        }
        
        it ita = m_pop.begin() + rd() % actualPopSize;
        it itb = m_pop.begin() + rd() % actualPopSize;
        
        auto pat1 = (*ita)->getPatrimoine();
        pat1.erase (pat1.begin() + crossPoint, pat1.end());
        
        auto pat2 = (*itb)->getPatrimoine();
        pat2.erase (pat2.begin(), pat2.begin() + crossPoint);
        
        decltype (pat2) pat;
        pat.insert (pat.begin(), pat2.begin(), pat2.end());
        pat.insert (pat.begin(), pat1.begin(), pat1.end());
        
        m_pop.push_back (new Individu (pat, false));
    }
}
void Population::mutation()
{
    std::random_device rd;
    unsigned int sommeNotesTemp = 0;
    
    for (int i = 0; i < std::ceil (static_cast<double> (m_popSize) * m_fracMut); ++i) {
        if (m_sommeNotes == 0) {
            std::cerr << "Division par 0 à la ligne : " << __LINE__ << std::endl;
        }
        
        unsigned int n = rd() % m_sommeNotes;
        
        for (auto a : m_pop) {
        
            if (n < sommeNotesTemp +  a->getNote() && sommeNotesTemp <= n) {
                a->swapAlleles (rd() % 9, rd() % 9);
                sommeNotesTemp = 0;
                break;
            }
            
            sommeNotesTemp += a->getNote();
        }
    }
}

std::ostream& operator<< (std::ostream& os, const Population& pop)
{
    std::multimap<gene, Individu *> map;
    
    for (Individu *a : pop.getPopulation()) {
        map.insert (std::pair<gene, Individu *> (a->getNote(), a));
    }
    
    for (auto a : map) {
        os << *a.second << std::endl;
    }
    
    return os;
}
