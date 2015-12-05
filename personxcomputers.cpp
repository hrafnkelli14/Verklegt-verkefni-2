#include "personxcomputers.h"

PersonXComputers::PersonXComputers()
{
    //Intentionally left empty
}

PersonXComputers::PersonXComputers(Person pers, QVector<Computer> comp)
{
    person = pers;
    computers = comp;
}

void PersonXComputers::setPerson(Person pers)
{
    person = pers;
}

void PersonXComputers::setComputers(QVector<Computer> comp)
{
    computers = comp;
}
