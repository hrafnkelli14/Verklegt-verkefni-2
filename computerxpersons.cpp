#include "computerxpersons.h"

ComputerXPersons::ComputerXPersons()
{
    //Intentionally left empty
}

ComputerXPersons::ComputerXPersons(Computer comp, QVector<Person> pers)
{
    computer = comp;
    persons = pers;
}

void ComputerXPersons::setComputer(Computer comp)
{
    computer = comp;
}

void ComputerXPersons::setPersons(QVector<Person> pers)
{
    persons = pers;
}
