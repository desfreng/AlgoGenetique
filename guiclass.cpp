#include "guiclass.h"

using namespace std;

GuiClass::GuiClass() : _nbReponses (2), _nbIndividus (7500), _fracSupr (0.25), _fracMut (0.02), _objectif (1), _typeTirage (Proportionel), _coefficient (1), _debug (false) {}

void GuiClass::init()
{
    string temp;
    
    cout << *this << endl;
    cout << "Voulez-vous modifier les paramètres ? (O/N) : ";
    cin >> temp;
    
    cout << endl;
    transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
    
    while (temp == "o" || temp == "oui" || temp == "y" || temp == "yes") {
    
        unsigned int choix = 0;
        
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
            
            if (! (cin >> choix) || (choix < 1) || (choix > 8)) {
                cout << "Veulliez entrer un nombre entre 1 et 9 !" << endl;
            }
        } while (choix < 1 || choix > 9);
        
        Clear();
        
        
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
        cout << *this << endl;
        
        cout << "Voulez-vous continuer de modifier les paramètres ? (O/N) : ";
        cin >> temp;
        
        cout << endl;
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
    do {
        cout << "Entrez un nombre d'individu : ";
        
        if (! (cin >> _nbIndividus)) {
            cout << "Veillez entrer un nombre entier positif !" << endl;
        }
        
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
    } while (_nbIndividus == 0);
    
    Clear();
}
void GuiClass::setReponses()
{
    do {
        cout << "Entrez le nombre de réponses souhaité : ";
        
        if (! (cin >> _nbReponses) || _nbReponses == 0) {
            cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        }
        
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
    } while (_nbReponses == 0);
    
    Clear();
}
void GuiClass::setFracMut()
{
    do {
        cout << "Entrez la proportion d'individu modifiés par mutation à chaque génération : ";
        
        if (! (cin >> _fracMut)) {
            cout << "Veillez entrer un nombre décimal !" << endl;
            _fracMut = -1.0;
            
        }
        else if (_fracMut < 0 || _fracMut > 1) {
            cout << "Veillez entrer un nombre décimal entre 0 et 1 compris !" << endl;
            _fracMut = -1.0;
        }
        
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
    } while (_fracMut < 0.0);
    
    Clear();
}
void GuiClass::setFracSupr()
{
    do {
        cout << "Entrez la proportion d'individu générés par croisement à chaque génération : ";
        
        if (! (cin >> _fracSupr)) {
            cout << "Veillez entrer un nombre décimal !" << endl;
            _fracSupr = -1.0;
        }
        else if (_fracSupr < 0 || _fracSupr > 1) {
            cout << "Veillez entrer un nombre décimal entre 0 et 1 compris !" << endl;
            _fracSupr = -1.0;
        }
        
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
    } while (_fracSupr < 0.0);
    
    Clear();
}
void GuiClass::setObjectif()
{
    do {
        cout << "Entrez l'objectif souhaité [Défaut : 66] : ";
        
        if (! (cin >> _objectif) || _objectif == 0) {
            cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        }
        
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
    } while (_objectif == 0);
    
    Clear();
}
void GuiClass::setTirage()
{
    unsigned int typetirage;
    
    do {
        cout << "Choisisez un type de tirage : " << endl;
        cout << "    1. Tirage Uniforme : tous les individus ont la même chance d'étre selctioné" << endl;
        cout << "    2. Tirage Proportionel à la note : plus la note est élevée, plus la probabilité d'être sélectioné est forte" << endl;
        cout << "Choix : ";
        
        if (! (cin >> typetirage) || typetirage < 1 || typetirage > 2) {
            cout << "Veillez choisir l'option 1 ou 2 !" << endl;
        }
        else {
            if (typetirage == 1) {
                _typeTirage = Uniforme;
            }
            else {
                _typeTirage = Proportionel;
            }
        }
        
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
    } while (typetirage != 1 || typetirage != 2);
    
    Clear();
}
void GuiClass::setCoef()
{
    do {
        cout << "Entrez le coeficiant souhaité [Défaut : 1] : ";
        
        if (! (cin >> _coefficient) || _coefficient == 0) {
            cout << "Veillez entrer un nombre entier strictement positif !" << endl;
        }
        
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
    } while (_coefficient == 0);
    
    Clear();
}
void GuiClass::setDebug()
{
    string temp;
    
    do {
        cout << "Voulez-vous activer la Debug ? [o/n] : ";
        transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
        
        if (! (cin >> temp)) {
            cout << endl;
            cout << "Veillez choisir entre 'o' et 'n' !" << endl;
        }
        else {
            cout << endl;
            
            if (temp == "o" || temp == "oui" || temp == "y" || temp == "yes" ) {
                _debug = true;
            }
            else if (temp == "n" || temp == "non" || temp == "no") {
                _debug = false;
            }
            else {
                cout << "Veillez choisir entre 'o' et 'n' !" << endl;
            }
        }
        
        cin.clear();
        cin.ignore (numeric_limits<streamsize>::max(), '\n' );
        
    } while (! (temp == "o" || temp == "oui" || temp == "y" || temp == "yes" || temp == "n" || temp == "non" || temp == "no"));
    
    Clear();
}

std::ostream& operator<< (std::ostream& os, const GuiClass& gui)
{
    os << "Paramètres Actuels" << endl << endl;
    
    os << "  Population : " << endl;
    os << "Nombre d'Individus : " << gui.getNbIndividus() << endl;
    os << "Probabilté de supression : " << gui.getFracSupr() * 100 << "%" << endl;
    os << "Probabilté de mutation : " << gui.getFracMut() * 100 << "%" << endl;
    os << "Type de Tirage : " << gui.typeTirage() << endl;
    os << "Nombre de réponses souhaité : " << gui.getNbReponses() << endl << endl;
    
    os << "  Noteur : " << endl;
    os << "Coefficient : " << gui.getCoefficient() << endl;
    os << "Debug : " << boolalpha << gui.debug() << endl;
    
    return os;
}

