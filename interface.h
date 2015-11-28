#include "requestprocessor.h"

#ifndef INTERFACE_H
#define INTERFACE_H

class Interface
{
public:
    Interface();
    void start(); //TODO make awesome while loop
private:
    void add(); //adds a new person
    void orderingSettings(); //TODO finish this

    RequestProcessor request;
};

#endif // INTERFACE_H
