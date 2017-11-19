#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>

#include "population.h"
#include "noteur.h"
#include "general.h"
#include "guiclass.h"

using namespace std;

const vector<gene> genes = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int main()
{
    GuiClass gui;
    
    gui.init();
    
    Noteur foncteur (66, gui.getCoefficient(), gui.debug());
    Population pop (gui.getNbIndividus(), gui.getFracSupr(), gui.getFracMut(), gui.typeTirage(), gui.getObjectif());
    
    pop.generation (genes);
    pop.noteAll (foncteur);
    
    pop.doGenerationCycle (foncteur, gui.getNbReponses());
    
    for (auto a : pop.solutions()) {
        cout << a << endl;
    }
    
    return 0;
}
