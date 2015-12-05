#include "relation.h"

#ifndef PERSONXCOMPUTERS_H
#define PERSONXCOMPUTERS_H


class PersonXComputers : public Relation
{
public:
    PersonXComputers();
    PersonXComputers(Person pers, QVector<Computer> comp);
    void setPerson(Person pers);
    void setComputers(QVector<Computer> comp);
    //TODO OVERLOAD COUT
};

#endif // PERSONXCOMPUTERS_H
