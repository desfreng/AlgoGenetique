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
    gui.configurer();
    
    //On initialise le Noteur et la Population avec les paramètres désirés via le gui
    Noteur foncteur (gui);
    Population pop (gui.getNbIndividus(), gui.getFracSupr(), gui.getFracMut(), gui.typeTirage(), gui.getObjectif());
    
    //On génère la population
    pop.generation (genes);
    
    //On donne à l'interface le noteur et la population
    gui.setNoteur (&foncteur);
    gui.setPopulation (&pop);
    
    //On affiche le menu principal
    gui.menu();
    
    return 0;
}
