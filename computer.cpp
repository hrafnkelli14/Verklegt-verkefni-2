#include "computer.h"
#include <iostream>

//========CONSTRUCTOR==========
Computer::Computer()
{
    name = "";
    year_of_build = "";
    type = "";
    was_built = false;
}

//========PUBLIC FUNCTIONS==========
QString Computer::getName()
{
    return QString::fromStdString(name);
}

QString Computer::getYear()
{
    return QString::fromStdString(year_of_build);
}

QString Computer::getType()
{
    return QString::fromStdString(type);
}

bool Computer::getBuilt()
{
    return was_built;
}

void Computer::setName(string _name)
{
    name = _name;
}

void Computer::setYear(string _year_of_build)
{
    year_of_build = _year_of_build;
}

void Computer::setType(string _type)
{
    type = _type;
}

void Computer::setBuilt(bool _was_built)
{
    was_built = _was_built;
}

//========PRIVATE FUNCTIONS==========

//NO PRIVATE FUNCTIONS YET

//========FRIEND FUNCTIONS==========
istream& operator >>(std::istream& ins, Computer& comp)
{
    char built;

    std::cout << "Enter the name of a computer: ";
    ins >> comp.name;
    std::cout << "Enter the computer type: ";
    ins >> comp.type;
    while(1)
    {
        std::cout << "Was the computer built(y for yes, n for no): ";
        ins >> built;

        if(built == 'Y' || built == 'y')
        {
            comp.was_built = true;
            break;
        }
        else if(built == 'N' || built == 'n')
        {
            comp.was_built = false;
            break;
        }
        else
        {
            cout << "Illegal character!" << endl;
            break;
        }
    }
    if(comp.was_built == true)
    {
        std::cout << "Enter the year it was built: ";
        ins >> comp.year_of_build;
    }
    else
    {
        comp.year_of_build = "NULL";
    }
    return ins;
}

ostream& operator <<(std::ostream& os, Computer comp)
{
    os << "Name: " << comp.name << ", ";
    os << "Computer type: " << comp.type << ", ";
    if(comp.was_built)
    {
        os << "Build year: " << comp.year_of_build;
    }
    return os;
}