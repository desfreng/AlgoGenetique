#include "guiclass.h"
#include "population.h" // J'include aussi Population.h pour avoir les 'vraies' méthodes de la classe et non celles de la classe temporaire

using namespace std;

// Constructeur
GuiClass::GuiClass()
{
    _nbReponses  = 2;
    _nbIndividus  = 7500;
    _fracSupr = 0.25;
    _fracMut  = 0.02;
    _objectif  = 1;
    _typeTirage = new Tirage (Tirage::Proportionel);
    _coefficient  = 1;
    _debug  = false;
    _pop = nullptr;
    _noteur = nullptr;
}
GuiClass::~GuiClass()
{
    //On suprime ce que l'on a dynamiquement instancié.
    delete  _typeTirage;
}
void GuiClass::setPopulation (Population *pop)
{
    _pop = pop;
}
void GuiClass::setNoteur (AbstractNoteur *noteur)
{
    _noteur = noteur;
}

//Menu des paramètres
void GuiClass::configurer()
{
    clear();
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
        clear();
        
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
                
                clear();
                cout << "Veulliez entrer un nombre entre 1 et 8 !" << endl;
            }
            
            
        } while (choix < 1 || choix > 8);
        
        clear();
        
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
        
        clear();
        
        //On affiche les paramètres et on redemande à l'utilisateur s'il veut les remodifier
        cout << *this << endl;
        
        cout << "Voulez-vous continuer de modifier les paramètres ? (O/N) : ";
        cin >> temp;
        cout << endl;
        
        //On tranforme la chaine en minuscule pour éviter de gérer encore plus de cas ("Yes", "YEs", "YES", "yes")
        transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
    }
    
}
void GuiClass::menu()
{
    unsigned int choix;
    bool quitter = false;
    string buffer; // Buffer des Réponses Texte
    
    //Tant que l'utilisateur ne veut pas quitter
    while (!quitter) {
        //On affiche le menu
        
        
        //Tant que le choix n'est pas vailde (entier positif entre 1 et 11)
        //On continue de le demander
        do {
            cout << endl;
            clear();
            
            // On efface les erreurs
            cin.clear();
            cin.ignore (numeric_limits<streamsize>::max(), '\n' );
            
            cout << "       --- Menu Principal ---" << endl << endl;
            cout << " 1.  Afficher la Population dans un fichier"  << endl;
            cout << " 2.  Afficher les Réponses trouvés" << endl;
            cout << " 3.  Effectuer n génération(s)" << endl;
            cout << " 4.  Tenter de trouver n réponse(s)" << endl;
            cout << " 5.  Selectionner les individus" << endl;
            cout << " 6.  Croiser les individus" << endl;
            cout << " 7.  Muter les individus" << endl;
            cout << " 8.  Noter les individus" << endl;
            cout << " 9.  Modifier les paramètres" << endl;
            cout << " 10. Regérérer la population" << endl;
            cout << " 11. Quitter" << endl;
            
            cout << "Choix : ";
        } while (! (cin >> choix) || choix < 1 || choix > 11);
        
        cout << endl;
        
        if (choix == 1) {
            cout << endl;
            cout << "Entrer le nom de fichier : ";
            cin >> buffer;
            cout << endl;
            
            //On ouvre un fichier à la fin de celui-ci
            ofstream out (buffer, ofstream::ate);
            
            //Puis on écrit dedans
            out << "    --- Population ---" << endl;
            out << "Nombre d'individus : " << _pop->population().size() << endl;
            out << endl << *_pop << endl;
            
            //On enregistre
            out.close();
            
            cout << "Population enregistrée !" << endl;
            pause();
        }
        else if (choix == 2) {
            do {
                cout << endl;
                clear();
                // On efface les erreurs
                cin.clear();
                cin.ignore (numeric_limits<streamsize>::max(), '\n' );
                
                cout << "Afficher les réponses dans : " << endl;
                cout << "    1. la Console" << endl;
                cout << "    2. un Fichier" << endl;
                
                cout << "Choix : ";
            } while (! (cin >> choix) || choix < 1 || choix > 2);
            
            cout << endl;
            
            if (choix == 1) {
                clear();
                
                cout << "    --- Solutions ---" << endl;
                cout << "Nombre de Solution : " << _pop->solutions().size() << endl;
                cout << endl;
                
                for (auto a : _pop->solutions()) {
                    cout << a << endl;
                }
                
                pause();
            }
            else if (choix == 2) {
                cout << endl << "Entrer le nom de fichier : ";
                cin >> buffer;
                cout << endl;
                
                //On ouvre un fichier à la fin de celui-ci
                ofstream out (buffer, ofstream::ate);
                
                out << "    --- Solutions ---" << endl;
                out << "Nombre de Solution : " << _pop->solutions().size() << endl;
                out << endl;
                
                //Puis on écrit dedans
                for (auto a : _pop->solutions()) {
                    out << a << endl;
                }
                
                //On enregistre
                out.close();
                
                cout << "Solutions enregistrées !" << endl;
                pause();
            }
            
        }
        else if (choix == 3) {
            do {
                cout << endl;
                clear();
                
                // On efface les erreurs
                cin.clear();
                cin.ignore (numeric_limits<streamsize>::max(), '\n' );
                
                cout << "Combien de générations voulez-vous effectuer ? : ";
            } while (! (cin >> choix)); // On utilise la variable choix pour stoquer le nombre de génération à effectuer
            
            _pop->doGenerations (choix, *_noteur);
            
            cout << "Génération(s) effectuées !" << endl;
            pause();
            
        }
        else if (choix == 4) {
            do {
                cout << endl;
                clear();
                
                // On efface les erreurs
                cin.clear();
                cin.ignore (numeric_limits<streamsize>::max(), '\n' );
                
                cout << "Combien de réponses espérez-vous obtenir ? : ";
            } while (! (cin >> choix) || choix < 1); // On utilise la variable choix pour stoquer le nombre de réponses supérieur à 1
            
            _pop->doGenerationCycle (*_noteur, choix);
            
            cout << "Génération(s) effectuées !" << endl;
            pause();
            
        }
        else if (choix == 5) {
            if (_pop->estPrete()) {
                _pop->selection();
                cout << "Selection effectué !" << endl;
            }
            else {
                cout << "Erreur !" << endl;
                cout << "Vous devez noter la population avant !" << endl;
            }
            
            pause();
        }
        else if (choix == 6) {
            if (_pop->estPrete()) {
                _pop->croisement();
                cout << "Croisement effectué !" << endl;
            }
            else {
                cout << "Erreur !" << endl;
                cout << "Vous devez noter la population avant !" << endl;
            }
            
            pause();
            
        }
        else if (choix == 7) {
            if (_pop->estPrete()) {
                _pop->mutation();
                
                
                cout << "Mutation effectuée !" << endl;
            }
            else {
                cout << "Erreur !" << endl;
                cout << "Vous devez noter la population avant !" << endl;
            }
            
            pause();
        }
        else if (choix == 8) {
            _pop->noteAll (*_noteur);
            cout << "Population notée !" << endl;
            pause();
        }
        else if (choix == 9) {
            configurer(); // On appelle 'configurer' une 2eme fois, elle s'occupe de la gestion des paramètres
        }
        else if (choix == 10) {
            _pop->generation ({1, 2, 3, 4, 5, 6, 7, 8, 9});
            cout << "Population regénérée !" << endl;
            pause();
        }
        else if (choix == 11) {
            cout << "Etes-vous sur de vouloir quitter ? [O/N] : ";
            cin >> buffer;
            cout << endl;
            
            //On tranforme la chaine en minuscule pour éviter de gérer encore plus de cas ("Yes", "YEs", "YES", "yes")
            transform (buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
            
            if (buffer == "o" || buffer == "oui" || buffer == "y" || buffer == "yes") {
                quitter = true;
            }
        }
    }
}

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
    return *_typeTirage;
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
        clear();
        cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        cout << "Entrez un nombre d'individu : ";
    }
    
    clear();
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
        clear();
        cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        cout << "Entrez le nombre de réponses souhaité : ";
    }
    
    clear();
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
        clear();
        cout << "Veillez entrer un nombre décimal entre 0 et 1 compris !" << endl;
        cout << "Entrez la proportion d'individu modifiés par mutation à chaque génération : ";
    }
    
    clear();
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
        clear();
        cout << "Veillez entrer un nombre décimal entre 0 et 1 compris !" << endl;
        cout << "Entrez la proportion d'individu générés par croisement à chaque génération : ";
    }
    
    clear();
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
        clear();
        cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        cout << "Entrez l'objectif souhaité [Défaut : 66] : ";
    }
    
    clear();
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
        clear();
        cout << "Veillez choisir l'option 1 ou 2 !" << endl;
        cout << "Choisisez un type de tirage : " << endl;
        cout << "    1. Tirage Uniforme : tous les individus ont la même chance d'étre selctioné" << endl;
        cout << "    2. Tirage Proportionel à la note : plus la note est élevée, plus la probabilité d'être sélectioné est forte" << endl;
        cout << "Choix : ";
    }
    
    if (typetirage == 1) {
        *_typeTirage = Tirage::Uniforme;
    }
    else {
        *_typeTirage = Tirage::Proportionel;
    }
    
    clear();
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
        clear();
        cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        cout << "Entrez le coeficiant souhaité [Défaut : 1] : ";
    }
    
    clear();
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
        clear();
        cout << "Veillez choisir entre 'o' et 'n' !" << endl;
        cout << "Voulez-vous activer la Debug ? [o/n] : ";
        cin >> temp;
        cout << endl;
        
        //On tranforme la chaine en minuscule pour éviter de gérer encore plus de cas ("Yes", "YEs", "YES", "yes")
        transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
    }
    
    clear();
    
    if (temp == "o" || temp == "oui" || temp == "y" || temp == "yes" ) {
        _debug = true;
    }
    else if (temp == "n" || temp == "non" || temp == "no") {
        _debug = false;
    }
}

void GuiClass::clear()
{
#if defined (WIN32)
    system ("cls");
#elif defined (linux)
    system ("clear");
#endif
}
void GuiClass::pause()
{
    cout << "Appuyer sur Entrer pour continuer..." << endl;
    
#if defined (WIN32)
    system ("PAUSE >nul");
#elif defined (linux)
    system ("read continue");
#endif
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
