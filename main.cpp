#include <iostream>
#include <fstream>
#include <vector>

#include "population.h"
#include "noteur.h"
#include "general.h"
#include "guiclass.h"

using namespace std;

const vector<gene> genes = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int main()
{
    //On crée l'interface et on affiche l'interface pour paramétrer
    GuiClass gui;
    gui.init();
    
    //On initialise le Noteur et la Population avec les paramètres désirés
    Noteur foncteur (66, gui.getCoefficient(), gui.debug());
    Population pop (gui.getNbIndividus(), gui.getFracSupr(), gui.getFracMut(), gui.typeTirage(), gui.getObjectif());
    
    //On génère la population
    pop.generation (genes);
    
    try {
        pop.doGenerationCycle (foncteur, gui.getNbReponses());
    }
    catch (const SimplExeption& e) {
        ofstream coucou ("crash.txt");
        
        cout <<  "Erreur (type : " << e.causetoString() << ") : " << e.what() << endl;
        cout << "Nombre d'individus : " << pop.population().size() << endl;
        cout << pop << endl;
        
        coucou <<  "Erreur (type : " << e.causetoString() << ") : " << e.what() << endl;
        coucou << "Nombre d'individus : " << pop.population().size() << endl;
        coucou << pop << endl;
        
        coucou.close();
        
        return -1;
    }
    
    for (auto a : pop.solutions()) {
        cout << a << endl;
    }
    
    return 0;
}
