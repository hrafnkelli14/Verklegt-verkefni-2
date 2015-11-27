#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
   data.setFile("data");
   cscientists = data.getList();
}

//========PUBLIC FUNCTIONS==========
void RequestProcessor::addPerson(QString personname)
{
    cscientists.push_back(personname);
    data.update(cscientists);
}

void RequestProcessor::deletePerson()
{
    //TODO IMPLEMENT
}

//========PRIVATE FUNCTIONS==========
