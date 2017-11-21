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
    ofstream coucou ("log.txt");
    
    //On initialise le Noteur et la Population avec les paramètres désirés
    Noteur foncteur (66, gui.getCoefficient(), false); //gui.debug());
    Population pop (gui.getNbIndividus(), gui.getFracSupr(), gui.getFracMut(), gui.typeTirage(), gui.getObjectif());
    
    //On génère la population
    pop.generation (genes);
    
    foncteur.setOstream (coucou, true);
    
    try {
        pop.doGenerationCycle (foncteur, gui.getNbReponses());
    }
    catch (const SimplExeption& e) {
    
        cout <<  "Erreur (type : " << e.causetoString() << ") : " << e.what() << endl;
        cout << "Nombre d'individus : " << pop.population().size() << endl;
        cout << "Somme Note Noteur : " << foncteur.getSommeNotes() << endl;
        coucou << endl << endl << endl << "ERREUR !!!" << endl;
        
        coucou <<  "Erreur (type : " << e.causetoString() << ") : " << e.what() << endl;
        coucou << "Nombre d'individus : " << pop.population().size() << endl;
        coucou << "Somme Note Noteur : " << foncteur.getSommeNotes() << endl;
        coucou << pop << endl;
        coucou.close();
        
        return -1;
    }
    
    for (auto a : pop.solutions()) {
        cout << a << endl;
    }
    
    return 0;
}
