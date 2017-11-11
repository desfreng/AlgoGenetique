#include <noteur.h>

using namespace std;

Noteur::Noteur() : AbstractNoteur (), m_resultat (66), m_coef (2), m_debug (false) {}
Noteur::Noteur (double resultat, int coeficiant, bool debug) : AbstractNoteur (), m_resultat (resultat), m_coef (coeficiant), m_debug (debug) {}
Noteur::Noteur (const Noteur& noteur) : AbstractNoteur (), m_resultat (noteur.m_resultat), m_coef (noteur.m_coef), m_debug (noteur.m_debug) {}

Noteur::~Noteur() {}

note Noteur::operator() (Individu *individu)
{
    if (m_debug) {
        cout << endl << "---------------------------------------------" << endl;
        cout << "Individu : " << *individu << endl;
    }
    
    double laNote = 0;
    double resul = resultat (individu);
    double par1 = parenthese1 (individu);
    double par3 = parenthese3 (individu);
    
    
    if (resul > m_resultat) {
        laNote = resul - m_resultat;
    }
    else {
        laNote = m_resultat - resul;
    }
    
    if (m_debug) {
        cout << "Donc Note = " << laNote << endl << endl;
    }
    
    
    
    double fracPar1 = par1 - floor (par1);
    
    if (m_debug) {
        cout << par1 << " = " << floor (par1) << " (U) + " << fracPar1 << " (D)" << endl;
    }
    
    double fracPar3 = par3 - floor (par3);
    
    if (m_debug) {
        cout << par3 << " = " << floor (par3) << " (U) + " << fracPar3 << " (D)" << endl;
        cout << fracPar1 << " + " << fracPar3 << " = " << fracPar1 + fracPar3 << endl << endl;
    }
    
    double reste =  (fracPar1 + fracPar3) - floor (fracPar1 + fracPar3);
    
    if (reste != 0.0) {
        laNote += reste * m_coef;
    }
    
    if (m_debug) {
        cout << "Donc Note = " << laNote << endl << endl;
    }
    
    
    if (!m_debug) {
        for (auto allele : individu->getPatrimoine()) {
            int nbAllele = 0;
            
            for (auto compare : individu->getPatrimoine()) {
                if (compare == allele) {
                    ++nbAllele;
                }
            }
            
            if (nbAllele > 1) {
            
                laNote += static_cast<double> (m_coef) / static_cast<double> (nbAllele);
            }
        }
    }
    else {
        decltype (individu->getPatrimoine()) doubles;
        
        for (auto allele : individu->getPatrimoine()) {
            int nbAllele = 0;
            
            for (auto compare : individu->getPatrimoine()) {
                if (compare == allele) {
                    ++nbAllele;
                }
            }
            
            if (nbAllele > 1) {
                laNote += static_cast<double> (m_coef) / static_cast<double> (nbAllele);
                
                if (find (doubles.begin(), doubles.end(), allele) == doubles.end()) {
                    doubles.push_back (allele);
                    cout << "Allèle " << allele << " trouvé " << nbAllele << " fois dans le patrimoine" << endl;
                }
            }
        }
        
        cout << "Donc Note = " << laNote << " (" << laNote - doubles.size() << " + " << doubles.size() << ")" << endl << endl;;
    }
    
    
    ++laNote;
    
    if (m_debug) {
        cout << "Note Finale : " << static_cast<int> (ceil (laNote)) << endl << endl;
    }
    
    individu->setNote (static_cast<note> (ceil (laNote)));
    
    if (m_debug) {
        cout << *individu << endl;
        cout << "---------------------------------------------" << endl << endl;
        
    }
    
    m_sommeNotes += static_cast<note> (ceil (laNote));
    
    return static_cast<note> (ceil (laNote));
}

double Noteur::resultat (const Individu *individu)
{
    if (m_debug) {
        cout << "Parenthèse 1 = " << parenthese1 (individu) << endl;
        cout << "Parenthèse 2 = " << (12.0 * individu->getAllele (4)) << endl;
        cout << "Parenthèse 3 = " << parenthese3 (individu) << endl;
        cout << "Résultat = " << static_cast<double> (individu->getAllele (0)) + parenthese1 (individu) + static_cast<double> (individu->getAllele (3)) + \
             (12.0 * static_cast<double> (individu->getAllele (4))) - static_cast<double> (individu->getAllele (5)) - 11.0 + parenthese3 (individu) - 10.0 << endl;
        cout << endl;
    }
    
    return static_cast<double> (individu->getAllele (0)) + parenthese1 (individu) + static_cast<double> (individu->getAllele (3)) + \
           (12.0 * static_cast<double> (individu->getAllele (4))) - static_cast<double> (individu->getAllele (5)) - 11.0 + parenthese3 (individu) - 10.0;
}
double Noteur::parenthese1 (const Individu *individu)
{
    return (13.0 * static_cast<double> (individu->getAllele (1)) / static_cast<double> (individu->getAllele (2)));
}
double Noteur::parenthese3 (const Individu *individu)
{
    return (static_cast<double> (individu->getAllele (6)) * static_cast<double> (individu->getAllele (7)) / static_cast<double> (individu->getAllele (8)));
}
