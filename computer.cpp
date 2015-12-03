#include "computer.h"

//========CONSTRUCTOR==========
Computer::Computer()
{
    //TODO implement
}

//========PUBLIC FUNCTIONS==========
QString Computer::getName()
{
    //TODO implement

    return "";
}

QString Computer::getYear()
{
    //TODO implement

    return "";
}

QString Computer::getType()
{
    //TODO implement

    return "";
}

bool Computer::getBuilt()
{
    //TODO implement

    return false;
}

void Computer::setName(string _name)
{
    //TODO implement
}

void Computer::setYear(string _name)
{
    //TODO implement
}

void Computer::setType(string _name)
{
    //TODO implement
}

void Computer::setBuilt(bool _was_built)
{
    //TODO implement
}

//========PRIVATE FUNCTIONS==========

//NO PRIVATE FUNCTIONS YET

//========FRIEND FUNCTIONS==========
istream& operator >>(std::istream& ins, Computer& comp)
{
    //TODO implement
    return ins;
}

ostream& operator <<(std::ostream& os, Computer comp)
{
    //TODO implement
    return os;
}
