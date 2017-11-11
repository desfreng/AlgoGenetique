#ifndef ABSTRACTNOTEUR_H
#define ABSTRACTNOTEUR_H

#include "individu.h"
#include "general.h"

//Le Foncteur utilisé pour noter les individus doit hériter de la classe abstraite AbstractNoteur
class AbstractNoteur
{
    public:
        AbstractNoteur() : m_sommeNotes (0) {}
        virtual ~AbstractNoteur() {}
        
        virtual note operator() (Individu *individu) = 0;
        
        note getSommeNotes() const {
            return m_sommeNotes;
        }
        void resetSommeNotes() {
            m_sommeNotes = 0;
        }
        
    protected:
        note m_sommeNotes;
};

#endif // ABSTRACTNOTEUR_H