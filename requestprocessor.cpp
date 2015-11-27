#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
   data.setFile("data");
}

//========PUBLIC FUNCTIONS==========
void RequestProcessor::addPerson(QString personname)
{
    data.addPerson(personname);
}

//========PRIVATE FUNCTIONS==========
void RequestProcessor::getPersons()
{
    //TODO: IMPLEMENT
}
