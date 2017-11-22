#include <noteur.h>
#include <fstream>

//Constructeurs
Noteur::Noteur()
{
    m_resultat = 66;
    m_coef = 2;
    m_debug  = false;
    m_os = &std::cout;
}
Noteur::Noteur (double resultat, double coefficient, bool debug)
{
    m_resultat = resultat;
    m_coef = coefficient;
    m_debug  = debug;
    m_os = &std::cout;
}
Noteur::Noteur (const GuiClass& gui)
{
    m_resultat = 66;
    m_coef = gui.getCoefficient();
    m_debug  = gui.debug();
    m_os = &std::cout;
    
}
//Destructeur
Noteur::~Noteur()
{
    m_os = nullptr;
}

//Met à jour le flux utilisé pour la debug
void Noteur::setOstream (std::ostream& os, bool force)
{
    if (m_debug || force) {
        m_os = &os;
    }
}

//Surcharge de ()
note Noteur::operator() (Individu *individu)
{
    //Partie de Debug (instancier Noteur avec debug = true pour voir)
    if (m_debug && (m_os != nullptr)) {
        *m_os << std::endl << "---------------------------------------------" << std::endl;
        *m_os << "Individu : " << *individu << std::endl << std::endl;
    }
    
    
    //Si l'individu est déjà noté
    if (individu->haveNote()) {
        //On l'ajoute à la somme des notes
        m_sommeNotes += individu->getNote();
        //Et on retourne sa note
        return individu->getNote();
    }
    
    
    
    /*          PREMIÈRE PARTIE
     *
     * Vérification du résultat du Serpent
     * Plus le résultat est près du résultat attendu, plus la note est basse
     */
    
    //Note de l'individu passé en paramètre
    double laNote = 1;      // Initialisation à 1 pour éviter que la note soit nulle car sinon Individu::haveNote() est faux
    
    
    // Calcul de la 'Première Parenthèse'
    double par1 = 13.0 * static_cast<double> (individu->getAllele (1)) / static_cast<double> (individu->getAllele (2));
    
    // Calcul de la 'Troisième Parenthèse'
    double par3 = static_cast<double> (individu->getAllele (6)) * static_cast<double> (individu->getAllele (7)) / static_cast<double> (individu->getAllele (8));
    
    // Calcul du 'Sepent'
    double resul = static_cast<double> (individu->getAllele (0)) + par1 + static_cast<double> (individu->getAllele (3)) +
                   (12.0 * static_cast<double> (individu->getAllele (4))) - static_cast<double> (individu->getAllele (5)) - 11.0 + par3 - 10.0;
                   
    laNote += std::abs (resul - m_resultat);
    
    //Partie de Debug (instancier Noteur avec debug = true pour voir)
    if (m_debug && (m_os != nullptr)) {
        *m_os << "Parenthèse 1 = " << par1 << std::endl;
        *m_os << "Parenthèse 2 = " << (12.0 * individu->getAllele (4)) << std::endl;
        *m_os << "Parenthèse 3 = " << par3 << std::endl;
        *m_os << "Résultat = " << resul << std::endl;
        *m_os << "Donc Note = " << laNote << std::endl << std::endl;
    }
    
    
    
    
    /*          DEUXIÈME PARTIE
     *
     * Si le résulat n'est pas un entier
     * On ajoute à la note la partie décimale multipliée par un coefficient (m_coef)
     */
    
    //Partie décimale de chaque 'parenthèses'
    double fracPar1 = par1 - floor (par1);      //Résultat avec décimales - Résultat tronqué à l'unité = Partie Décimale
    double fracPar3 = par3 - floor (par3);
    
    //Partie décimale de somme des 'parenthèses'
    double reste =  (fracPar1 + fracPar3) - floor (fracPar1 + fracPar3);
    
    laNote += reste * m_coef;
    
    //Partie de Debug (instancier Noteur avec debug = true pour voir)
    if (m_debug && (m_os != nullptr)) {
        *m_os << par1 << " = " << floor (par1) << " (U) + " << fracPar1 << " (D)" << std::endl;
        *m_os << par3 << " = " << floor (par3) << " (U) + " << fracPar3 << " (D)" << std::endl;
        *m_os << fracPar1 << " + " << fracPar3 << " = " << fracPar1 + fracPar3 << std::endl << std::endl;
        *m_os << "Donc Note = " << laNote  << " (" << laNote - reste *m_coef << " + " << reste *m_coef << ")" << std::endl << std::endl;
    }
    
    
    
    
    
    /*          TROISIÈME PARTIE
     *
     * On vérifie que le patrimoine de l'individu contient bien que des nombres différents
     * Sinon, on ajoute à la note le nombre de nombres idebtiques multiplié par le même coefficient (m_coef)
     */
    
    std::vector<gene> doubles;
    
    for (auto allele : individu->getPatrimoine()) {
    
        //Je compte ne nombre de chaque allèle dans le patrimoine si elle n'est déja pas compté
        
        if (std::find (doubles.begin(), doubles.end(), allele) == doubles.end()) {
            if (std::count (individu->getPatrimoine().begin(), individu->getPatrimoine().end(), allele) > 1) {
                doubles.push_back (allele);
            }
        }
    }
    
    laNote += doubles.size() * m_coef;
    
    //Partie de Debug (instancier Noteur avec debug = true pour voir)
    if (m_debug && (m_os != nullptr)) {
        for (auto a : doubles) {
            *m_os << "Allèle " << a << " trouvé plusieurs fois dans le patrimoine" << std::endl;
        }
        
        *m_os << "Donc Note = " << laNote << " (" << laNote - doubles.size() << " + " << doubles.size() << ")" << std::endl << std::endl;
        
        *m_os << "Note Finale : " << static_cast<int> (ceil (laNote)) << std::endl;
        *m_os << "---------------------------------------------" << std::endl << std::endl;
        
    }
    
    // On retourne la note
    m_sommeNotes += static_cast<note> (ceil (laNote));
    return static_cast<note> (ceil (laNote));
}
