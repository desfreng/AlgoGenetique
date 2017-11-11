#include "abstractnoteur.h"
AbstractNoteur::AbstractNoteur() : m_sommeNotes (0) {}
AbstractNoteur::~AbstractNoteur() {}

note AbstractNoteur::getSommeNotes() const
{
    return m_sommeNotes;
}
void AbstractNoteur::resetSommeNotes()
{
    m_sommeNotes = 0;
}
