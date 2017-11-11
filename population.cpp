#include "population.h"

Population::Population (size_t size, double fracSupr, double fracMut, note objectif, bool tirageUniforme) : m_nbGeneration (0), m_isNoted (false), m_tirageUniforme (tirageUniforme),  m_objectif (objectif), m_popSize (size), m_fracSupr (fracSupr), m_fracMut (fracMut) {}
Population::~Population()
{
    // Je suprime tous mes individus
    
    for (Individu *a : m_pop) {
        delete a;
        a = 0;
    }
}

void Population::generate (const std::vector<gene>& genes, unsigned int nbgenes)
{
    m_pop.clear();
    
    // Je remplis ma population avec des nouveaux individus
    // qui ont un patrimoine mélangé sans doubles
    
    for (size_t i = 0; i < m_popSize; ++i) {
        m_pop.push_back (new Individu (genes, nbgenes));
    }
    
    m_isNoted = false;
}
void Population::generate (const std::vector<gene>& genes, bool ramdom)
{
    m_pop.clear();
    
    // Je remplis ma population avec des nouveaux individus
    // qui ont un patrimoine mélangé avec doubles (si ramdom = true)
    // sinon je créé une population d'individus indentiques (pour ramdom = false)
    
    for (size_t i = 0; i < m_popSize; ++i) {
        m_pop.push_back (new Individu (genes, ramdom));
    }
    
    m_isNoted = false;
    
}

void Population::doGenerationCycle (AbstractNoteur& noteur, size_t nbSolutions)
{
    if (!m_isNoted) {
        noteAll (noteur);
    }
    
    // J'effectue les cycles des gérations tant que
    // Je n'ai pas le nombre de réponses demandées
    
    // 1 génération : Sélection, Croisement, Mutation
    
    while (m_solutions.size() <= nbSolutions - 1) {
        std::cout << "Generation n° " << m_nbGeneration << std::endl;
        select();
        noteAll (noteur);
        mating();
        noteAll (noteur);
        mutation();
        noteAll (noteur);
        ++m_nbGeneration;
    }
}
void Population::doGenerations (unsigned int nbGeneration, AbstractNoteur& noteur)
{
    if (!m_isNoted) {
        noteAll (noteur);
    }
    
    // J'effectue x cycles de gération
    
    // 1 génération : Sélection, Croisement, Mutation
    
    unsigned int nbGenerationAFaire = m_nbGeneration + nbGeneration;
    
    for (; m_nbGeneration < nbGenerationAFaire; ++m_nbGeneration) {
        std::cout << "Generation n° " << m_nbGeneration << std::endl;
        select();
        noteAll (noteur);
        mating();
        noteAll (noteur);
        mutation();
        noteAll (noteur);
    }
}

void Population::noteAll (AbstractNoteur& noteur)
{
    // On reset la somme des notes du noteur
    noteur.resetSommeNotes();
    
    // On applique le noteur sur chaque individu
    for (auto a : m_pop) {
        a->setNote (noteur (a));
        
        // Si la note de l'individu noté est égale à l'obectif
        // Et que l'individu n'est pas déjà dans notre liste de réponses
        if (a->getNote() == m_objectif && std::find (m_solutions.begin(), m_solutions.end(), *a) == m_solutions.end()) {
            // On l'ajoute
            m_solutions.push_back (*a);
        }
    }
    
    m_isNoted = true;
    m_sommeNotes = noteur.getSommeNotes();
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
    for (int i = 0; i < std::ceil (static_cast<double> (m_popSize) * m_fracSupr); ++i) {
    
        // Je tire un individu au sort
        it individu = selectRandomIndividu();
        
        //Je retire sa 'part de note' de la somme des notes.
        m_sommeNotes -= (*individu)->getNote();
        
        // Je le suprime
        delete (*individu);
        m_pop.erase (individu);
    }
    
}
void Population::mating ()
{
    std::random_device rd;
    
    size_t actualPopSize = m_pop.size();
    
    for (unsigned int i = 0; i < m_popSize - actualPopSize; i++) {
        // Definition du point de croisement
        int crossPoint = rd() % 9;
        
        // Exemple :
        // CrossPoint = 4;
        
        // On tire au sort 2 individus
        // On sélectione une partie du patrimoine des individus
        // Puis on les rassemblent
        
        auto pat1 = (*selectRandomIndividu ())->getPatrimoine();   // pat1 = {1, 2, 3, 4, 5, 6, 7, 8, 9}
        pat1.erase (pat1.begin() + crossPoint, pat1.end());         // pat1 = {1, 2, 3, 4, 5}
        
        auto pat2 = (*selectRandomIndividu ())->getPatrimoine();   // pat2 = {9, 8, 7, 6, 5, 4, 3, 2, 1}
        pat2.erase (pat2.begin(), pat2.begin() + crossPoint);       // pat2 = {4, 3, 2, 1}
        
        decltype (pat2) pat;
        pat.insert (pat.begin(), pat2.begin(), pat2.end());         // pat = {1, 2, 3, 4, 5}
        pat.insert (pat.begin(), pat1.begin(), pat1.end());         // pat = {1, 2, 3, 4, 5, 4, 3, 2, 1}
        
        m_pop.push_back (new Individu (pat, false));
    }
}
void Population::mutation()
{
    std::random_device rd;
    
    for (int i = 0; i < std::ceil (static_cast<double> (m_popSize) * m_fracMut); ++i) {
    
        (*selectRandomIndividu())->swapAlleles (rd() % 9, rd() % 9);
    }
}

Population::it Population::selectRandomIndividu ()
{
    std::random_device rd;
    
    if (m_tirageUniforme) {
    
        // Je tire au sort un individu
        
        return m_pop.begin() + (rd() % m_pop.size());
        
        // Tous les individus ont la même probabilité d'être sélectioné.
        
    }
    else {
    
        // Si mes Individus ne sont pas notés
        // Impossible d'en tirer 1 au sort
        // donc je jette une exeption
        
        if (!m_isNoted) {
            throw SimplExeption ("Individus non notés !", SimplExeption::IndividuNonNote);
        }
        
        unsigned int sommeNotesTemp = 0;
        
        if (m_sommeNotes == 0) {
            throw SimplExeption ("Division par 0 à la ligne : " + std::to_string (__LINE__), SimplExeption::DivisionParZero);
        }
        
        // Je tire au sort un nombre entre 0 et la somme des notes
        unsigned int n = rd() % m_sommeNotes;
        
        // Je parcours tous mes individus afin de trouver
        // l'individu qui encadre ma note tirée
        
        for (it it = m_pop.begin(); it != m_pop.end(); ++it) {
        
            if (n < sommeNotesTemp +  (*it)->getNote() && sommeNotesTemp <= n) {
                return it;
                
                // Tous les individus n'ont la même probabilité d'être sélectioné.
                // Donc plus l'individu a une note élevée, plus il a de chance de se faire séléctionner
                
            }
            
            sommeNotesTemp += (*it)->getNote();
        }
        
        return begin();
    }
}

std::ostream& operator<< (std::ostream& os, const Population& pop)
{
    std::multimap<gene, Individu *> map;
    
    // Je trie mes individus avec une multimap par note (de la note la plus faible à la plus élevée)
    
    for (Individu *a : pop.getPopulation()) {
        map.insert (std::pair<gene, Individu *> (a->getNote(), a));
    }
    
    //je les 'affiche' dans mon flux
    
    for (auto a : map) {
        os << *a.second << std::endl;
    }
    
    return os;
}
