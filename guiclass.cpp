#include "guiclass.h"

using namespace std;

// Constructeur
GuiClass::GuiClass() : _nbReponses (2), _nbIndividus (7500), _fracSupr (0.25), _fracMut (0.02), _objectif (1), _typeTirage (Tirage::Proportionel), _coefficient (1), _debug (false) {}

//Menu des paramètres
void GuiClass::init()
{
    string temp;
    
    //On affiche les paramètres
    cout << *this << endl;
    
    cout << "Voulez-vous modifier les paramètres ? (O/N) : ";
    cin >> temp;
    cout << endl;
    
    //On tranforme la chaine en minuscule pour éviter de gérer encore plus de cas ("Yes", "YEs", "YES", "yes")
    transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
    
    //Tant que l'utilisateur veut modifier les paramètres
    while (temp == "o" || temp == "oui" || temp == "y" || temp == "yes") {
        Clear();
        
        unsigned int choix = 0;
        
        //Tant que l'utilisateur n'a pas choisi un menu valide on continue de lui en proposer un
        do {
            cout << "Entrer le numéro du paramètre correspondant : " << endl;
            cout << "    1. Nombre d'Individus" << endl;
            cout << "    2. Probabilté de Supression" << endl;
            cout << "    3. Probabilté de Mutation" << endl;
            cout << "    4. Type de Tirage" << endl;
            cout << "    5. Nombre de Réponses" << endl;
            cout << "    6. Coefficient" << endl;
            cout << "    7. Debug" << endl;
            cout << "    8. Quitter le menu" << endl;
            cout << "Choix (1~8) : ";
            
            //On efface la console entre-deux
            
            //Si l'opérateur n'a pas rentré un nombre entier positif entre 1 et 8
            if (! (cin >> choix) || (choix < 1) || (choix > 8)) {
                //On l'informe de son choix incorect
                //On ignore les erreurs
                cin.clear();
                cin.ignore (numeric_limits<streamsize>::max(), '\n' );
                
                Clear();
                cout << "Veulliez entrer un nombre entre 1 et 8 !" << endl;
            }
            
            
        } while (choix < 1 || choix > 8);
        
        Clear();
        
        //On appelle la fonction correspondante au choix sauf
        //le cas n°8 ('Quitter le menu') car il fonctionne sans traitement
        
        if (choix == 1) {
            setIndividu();
        }
        else if ( choix == 2) {
            setFracSupr();
        }
        else if ( choix == 3) {
            setFracMut();
        }
        else if ( choix == 4) {
            setTirage();
        }
        else if ( choix == 5) {
            setReponses();
        }
        else if ( choix == 6) {
            setCoef();
        }
        else if ( choix == 7) {
            setDebug();
        }
        
        Clear();
        
        //On affiche les paramètres et on redemande à l'utilisateur s'il veut les remodifier
        cout << *this << endl;
        
        cout << "Voulez-vous continuer de modifier les paramètres ? (O/N) : ";
        cin >> temp;
        cout << endl;
        
        //On tranforme la chaine en minuscule pour éviter de gérer encore plus de cas ("Yes", "YEs", "YES", "yes")
        transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
    }
    
}

void GuiClass::menu() {}

// Accesseurs des variables
unsigned int GuiClass::getNbReponses() const
{
    return _nbReponses;
}
unsigned int GuiClass::getNbIndividus() const
{
    return _nbIndividus;
}
double GuiClass::getFracSupr() const
{
    return _fracSupr;
}
double GuiClass::getFracMut() const
{
    return _fracMut;
}
note GuiClass::getObjectif() const
{
    return _objectif;
}
Tirage GuiClass::typeTirage() const
{
    return _typeTirage;
}
unsigned int GuiClass::getCoefficient() const
{
    return _coefficient;
}
bool GuiClass::debug() const
{
    return _debug;
}

// Demandes des valeurs des variables
void GuiClass::setIndividu()
{
    cout << "Entrez un nombre d'individu : ";
    
    //Tant que l'entrée de l'utilisateur n'est pas valide
    while (! (cin >> _nbIndividus) || _nbIndividus == 0) {
        cout << endl;
        
        //On éfface les erreurs
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
        //et on lui redemande
        Clear();
        cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        cout << "Entrez un nombre d'individu : ";
    }
    
    Clear();
}
void GuiClass::setReponses()
{
    cout << "Entrez le nombre de réponses souhaité : ";
    
    //Tant que l'entrée de l'utilisateur n'est pas valide
    while (! (cin >> _nbReponses) || _nbReponses == 0) {
        cout << endl;
        
        //On éfface les erreurs
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
        //et on lui redemande
        Clear();
        cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        cout << "Entrez le nombre de réponses souhaité : ";
    }
    
    Clear();
}
void GuiClass::setFracMut()
{
    cout << "Entrez la proportion d'individu modifiés par mutation à chaque génération : ";
    
    //Tant que l'entrée de l'utilisateur n'est pas valide
    while (! (cin >> _fracMut) || _fracMut < 0 || _fracMut > 1) {
        cout << endl;
        
        //On éfface les erreurs
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
        //et on lui redemande
        Clear();
        cout << "Veillez entrer un nombre décimal entre 0 et 1 compris !" << endl;
        cout << "Entrez la proportion d'individu modifiés par mutation à chaque génération : ";
    }
    
    Clear();
}
void GuiClass::setFracSupr()
{
    cout << "Entrez la proportion d'individu générés par croisement à chaque génération : ";
    
    //Tant que l'entrée de l'utilisateur n'est pas valide
    while (! (cin >> _fracSupr) || _fracSupr < 0 || _fracSupr > 1) {
        cout << endl;
        
        //On éfface les erreurs
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
        //et on lui redemande
        Clear();
        cout << "Veillez entrer un nombre décimal entre 0 et 1 compris !" << endl;
        cout << "Entrez la proportion d'individu générés par croisement à chaque génération : ";
    }
    
    Clear();
}
void GuiClass::setObjectif()
{
    cout << "Entrez l'objectif souhaité [Défaut : 66] : ";
    
    //Tant que l'entrée de l'utilisateur n'est pas valide
    while (! (cin >> _objectif) || _objectif == 0) {
        cout << endl;
        
        //On éfface les erreurs
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
        //et on lui redemande
        Clear();
        cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        cout << "Entrez l'objectif souhaité [Défaut : 66] : ";
    }
    
    Clear();
}
void GuiClass::setTirage()
{
    unsigned int typetirage;
    
    cout << "Choisisez un type de tirage : " << endl;
    cout << "    1. Tirage Uniforme : tous les individus ont la même chance d'étre selctioné" << endl;
    cout << "    2. Tirage Proportionel à la note : plus la note est élevée, plus la probabilité d'être sélectioné est forte" << endl;
    cout << "Choix : ";
    
    
    while (! (cin >> typetirage) || typetirage < 1 || typetirage > 2) {
        cout << endl;
        
        //On éfface les erreurs
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
        //et on lui redemande
        Clear();
        cout << "Veillez choisir l'option 1 ou 2 !" << endl;
        cout << "Choisisez un type de tirage : " << endl;
        cout << "    1. Tirage Uniforme : tous les individus ont la même chance d'étre selctioné" << endl;
        cout << "    2. Tirage Proportionel à la note : plus la note est élevée, plus la probabilité d'être sélectioné est forte" << endl;
        cout << "Choix : ";
    }
    
    if (typetirage == 1) {
        _typeTirage = Tirage::Uniforme;
    }
    else {
        _typeTirage = Tirage::Proportionel;
    }
    
    Clear();
}
void GuiClass::setCoef()
{
    cout << "Entrez le coeficiant souhaité [Défaut : 1] : ";
    
    //Tant que l'entrée de l'utilisateur n'est pas valide
    while (! (cin >> _coefficient) || _coefficient == 0) {
        cout << endl;
        
        //On éfface les erreurs
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
        //et on lui redemande
        Clear();
        cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        cout << "Entrez le coeficiant souhaité [Défaut : 1] : ";
    }
    
    Clear();
}
void GuiClass::setDebug()
{
    string temp;
    
    cout << "Voulez-vous activer la Debug ? [o/n] : ";
    cin >> temp;
    cout << endl;
    
    //On tranforme la chaine en minuscule pour éviter de gérer encore plus de cas ("Yes", "YEs", "YES", "yes")
    transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
    
    //Tant que l'entrée de l'utilisateur n'est pas valide
    while (! (temp == "o" || temp == "oui" || temp == "y" || temp == "yes" || temp == "n" || temp == "non" || temp == "no")) {
        //On lui redemande
        Clear();
        cout << "Veillez choisir entre 'o' et 'n' !" << endl;
        cout << "Voulez-vous activer la Debug ? [o/n] : ";
        cin >> temp;
        cout << endl;
        
        //On tranforme la chaine en minuscule pour éviter de gérer encore plus de cas ("Yes", "YEs", "YES", "yes")
        transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
    }
    
    Clear();
    
    if (temp == "o" || temp == "oui" || temp == "y" || temp == "yes" ) {
        _debug = true;
    }
    else if (temp == "n" || temp == "non" || temp == "no") {
        _debug = false;
    }
}

//Surcharge de l'opérateur '<<' pour afficher les paramètres
std::ostream& operator<< (std::ostream& os, const GuiClass& gui)
{
    //On affiche les paramètres
    os << "Paramètres Actuels" << endl << endl;
    
    os << "  Population : " << endl;
    os << "Nombre d'Individus : " << gui.getNbIndividus() << endl;
    os << "Probabilté de supression : " << gui.getFracSupr() * 100 << "%" << endl;
    os << "Probabilté de mutation : " << gui.getFracMut() * 100 << "%" << endl;
    os << "Type de Tirage : " << gui.typeTirage().tirageToString() << endl;
    os << "Nombre de réponses souhaité : " << gui.getNbReponses() << endl << endl;
    
    os << "  Noteur : " << endl;
    os << "Coefficient : " << gui.getCoefficient() << endl;
    os << "Debug : " << boolalpha << gui.debug() << endl;
    
    return os;
}
