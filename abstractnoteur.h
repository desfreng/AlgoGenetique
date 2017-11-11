#ifndef ABSTRACTNOTEUR_H
#define ABSTRACTNOTEUR_H

#include "individu.h"
#include "general.h"

class AbstractNoteur
{
    public:
        AbstractNoteur();
        virtual ~AbstractNoteur();
        
        virtual note operator() (Individu *individu) = 0;
        
        virtual note getSommeNotes() const;
        virtual void resetSommeNotes();
        
    protected:
        note m_sommeNotes;
};

#endif // ABSTRACTNOTEUR_H