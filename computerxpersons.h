#include "relation.h"

#ifndef COMPUTERXPERSONS_H
#define COMPUTERXPERSONS_H


class ComputerXPersons : public Relation
{
public:
    ComputerXPersons();
    ComputerXPersons(Computer comp, QVector<Person> pers);
    void setComputer(Computer comp);
    void setPersons(QVector<Person> pers);
    //TODO OVERLOAD COUT
};

#endif // COMPUTERXPERSONS_H
