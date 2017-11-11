#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>

#include <population.h>
#include <noteur.h>
#include <general.h>

using namespace std;

const vector<gene> genes = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int main()
{
    string buffer;
    unsigned int nbReponses = 2, nbIndividus = 7500;
    double fracSupr = 1.0 / 4.0, fracMut = 1.0 / 50.0;
    bool isOk;
    
    do {
        cout << "Entrez le nombre d'individu [" << nbIndividus << "] : ";
        cin >> buffer;
        
        if (buffer != "") {
            int stoir = stoi (buffer);
            
            
            if (stoir < 0) {
                nbIndividus = static_cast<unsigned int> (stoir * -1);
            }
            else if (stoir > 0) {
                nbIndividus = static_cast<unsigned int> (stoir);
            }
        }
        
        
        cout << "Entrez la proportion d'individu générés par croisement à chaque génération [" << fracSupr << "] (0~1) : ";
        cin >> buffer;
        
        if (buffer != "") {
            double stoir = stod (buffer);
            
            if (stoir >= 0 && stoir <= 1) {
            
                if (stoir < 0) {
                    fracSupr = stoir * -1;
                }
                else if (stoir > 0) {
                    fracSupr = stoir;
                }
            }
        }
        
        
        
        cout << "Entrez la proportion d'individu qui mute à chaque génération [" << fracMut << "] (0~1) : ";
        cin >> buffer;
        
        if (buffer != "") {
            double stoir = stod (buffer);
            
            if (stoir >= 0 && stoir <= 1) {
                if (stoir < 0) {
                    fracMut = stoir * -1;
                }
                else if (stoir > 0) {
                    fracMut = stoir;
                }
            }
        }
        
        
        cout << "Entrez le nombre de réponses [" << nbReponses << "] : ";
        cin >> buffer;
        
        if (buffer == "") {
            int stoir = stoi (buffer);
            
            
            if (stoir < 0) {
                nbReponses = static_cast<unsigned int> (stoir * -1);
            }
            else if (stoir > 0) {
                nbReponses = static_cast<unsigned int> (stoir);
            }
            
        }
        
        cout << "Nombre d'individus fixé à " << nbIndividus << endl;
        cout << "Proportion d'individu générés par croisement à chaque génération fixé à " << fracSupr << endl;
        cout << "Proportion d'individu qui mute à chaque génération fixé à " << fracMut << endl;
        cout << "Nombre de réponses fixé à " << nbReponses << endl;
        
        cout << "Valider les choix ? (O/N) : ";
        cin >> buffer;
        isOk = (buffer == "y" || buffer == "Y" || buffer == "O" || buffer == "o");
        
    }
    
    while (!isOk);
    
    Noteur foncteur (66, 1, false);
    Population pop (nbIndividus, fracSupr, fracMut);
    
    pop.generate (genes);
    pop.noteAll (foncteur);
    
    
    pop.doGenerationCycle (foncteur, nbReponses);
    
    for (auto a : pop.solutions()) {
        cout << a << endl;
    }
    
    return 0;
}
