#include <QVector>
#include <QString>
#include "person.h"
#include "computer.h"

#ifndef RELATION_H
#define RELATION_H


class Relation
{
public:
    Relation();
protected:
    QVector<Person> persons;
    QVector<Computer> computers;
    Person person;
    Computer computers;
};

#endif // RELATION_H
