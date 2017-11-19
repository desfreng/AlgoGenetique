#include "population.h"

Population::Population (size_t size, double fracSupr, double fracMut, Tirage tirageUniforme, note objectif) :  _isNoted (false), _nbGeneration (0), _typeSelection (tirageUniforme),  _objectif (objectif), _popSize (size), _fracSupr (fracSupr), _fracMut (fracMut) {}
Population::~Population()
{
    // Je suprime tous mes individus
    
    for (Individu *a : _pop) {
        delete a;
        a = 0;
    }
}

void Population::generation (const std::vector<gene>& genes, unsigned int nbgenes)
{
    _pop.clear();
    
    // Je remplis ma population avec des nouveaux individus
    // qui ont un patrimoine mélangé avec doubles
    
    for (size_t i = 0; i < _popSize; ++i) {
        _pop.push_back (new Individu (genes, nbgenes));
    }
    
    _isNoted = false;
}
void Population::generation (const std::vector<gene>& genes, bool ramdom)
{
    _pop.clear();
    
    // Je remplis ma population avec des nouveaux individus
    // qui ont un patrimoine mélangé sans doubles (si ramdom = true)
    // sinon je créé une population d'individus indentiques de patrimoine 'genes' (tableau)
    
    for (size_t i = 0; i < _popSize; ++i) {
        _pop.push_back (new Individu (genes, ramdom));
    }
    
    _isNoted = false;
    
}

void Population::doGenerationCycle (AbstractNoteur& noteur, unsigned int nbSolutions)
{
    if (!_isNoted) {
        noteAll (noteur);
    }
    
    // J'effectue les cycles des gérations tant que
    // Je n'ai pas le nombre de réponses demandées
    
    // 1 génération : Sélection, Croisement, Mutation
    
    while (_solutions.size() <= nbSolutions - 1) {
        std::cout << "Generation n° " << _nbGeneration << std::endl;
        selection();
        noteAll (noteur);
        croisement();
        noteAll (noteur);
        mutation();
        noteAll (noteur);
        ++_nbGeneration;
    }
}
void Population::doGenerations (unsigned int nbGeneration, AbstractNoteur& noteur)
{
    if (!_isNoted) {
        noteAll (noteur);
    }
    
    // J'effectue x cycles de gération
    
    // 1 génération : Sélection, Croisement, Mutation
    
    unsigned int nbGenerationAFaire = _nbGeneration + nbGeneration;
    
    for (; _nbGeneration < nbGenerationAFaire; ++_nbGeneration) {
        std::cout << "Generation n° " << _nbGeneration << std::endl;
        selection();
        noteAll (noteur);
        croisement();
        noteAll (noteur);
        mutation();
        noteAll (noteur);
    }
}

void Population::selection()
{
    for (int i = 0; i < std::ceil (static_cast<double> (_popSize) * _fracSupr); ++i) {
    
        // Je tire un individu au sort
        it individu = selectRandomIndividu();
        
        //Je retire sa 'part de note' de la somme des notes.
        _sommeNotes -= (*individu)->getNote();
        
        // Je le suprime
        delete (*individu);
        _pop.erase (individu);
    }
    
}

void Population::croisement ()
{
    std::random_device rd;
    
    size_t actualPopSize = _pop.size();
    
    for (unsigned int i = 0; i < _popSize - actualPopSize; i++) {
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
        
        _pop.push_back (new Individu (pat, false));
    }
}

void Population::mutation()
{
    std::random_device rd;
    
    for (int i = 0; i < std::ceil (static_cast<double> (_popSize) * _fracMut); ++i) {
    
        (*selectRandomIndividu())->swapAlleles (rd() % 9, rd() % 9);
    }
}

void Population::noteAll (AbstractNoteur& noteur)
{
    // On reset la somme des notes du noteur
    noteur.resetSommeNotes();
    
    // On applique le noteur sur chaque individu
    for (auto a : _pop) {
    
        // On appelle le foncteur 'noteur' avec comme parametre 'a' (l'individu actuel)
        a->setNote (noteur (a));
        
        // Si la note de l'individu noté est égale à l'obectif
        // Et que l'individu n'est pas déjà dans notre liste de réponses
        if (a->getNote() == _objectif && std::find (_solutions.begin(), _solutions.end(), *a) == _solutions.end()) {
            // On l'ajoute
            _solutions.push_back (*a);
        }
    }
    
    _isNoted = true;
    _sommeNotes = noteur.getSommeNotes();
}

size_t Population::size() const
{
    return _popSize;
}

Population::it Population::begin()
{
    return _pop.begin();
}
Population::it Population::end()
{
    return _pop.end();
}

bool Population::typeSelection() const
{
    return _typeSelection;
}

unsigned int Population::generation() const
{
    return _nbGeneration;
}

const std::vector<Individu> Population::solutions() const
{
    return _solutions;
}

const std::vector<Individu *> Population::population() const
{
    return _pop;
}

Population::it Population::selectRandomIndividu ()
{
    std::random_device rd;
    
    if (_typeSelection == Uniforme) {
    
        // Je tire au sort un individu
        
        return _pop.begin() + (rd() % _pop.size());
        
        // Tous les individus ont la même probabilité d'être sélectioné.
        
    }
    else {
    
        // Si mes Individus ne sont pas notés
        // Impossible d'en tirer 1 au sort
        // donc je jette une exeption
        
        if (!_isNoted) {
            throw SimplExeption ("Individus non notés !", SimplExeption::IndividuNonNote);
        }
        
        unsigned int sommeNotesTemp = 0;
        
        if (_sommeNotes == 0) {
            throw SimplExeption ("Division par 0 à la ligne : " + std::to_string (__LINE__), SimplExeption::DivisionParZero);
        }
        
        // Je tire au sort un nombre entre 0 et la somme des notes
        unsigned int n = rd() % _sommeNotes;
        
        // Je parcours tous mes individus afin de trouver
        // l'individu qui encadre ma note tirée
        
        for (it it = _pop.begin(); it != _pop.end(); ++it) {
        
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
    
    for (Individu *a : pop.population()) {
        map.insert (std::pair<gene, Individu *> (a->getNote(), a));
    }
    
    //je les 'affiche' dans mon flux via la surchage de l'opérateur '<<' de la classe Individu
    
    for (auto a : map) {
        os << *a.second << std::endl;
    }
    
    return os;
}
