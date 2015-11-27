#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
   data.setFile("data");
   cscientists = data.getList();
}

//========PUBLIC FUNCTIONS==========
void RequestProcessor::addPerson(const Person &pers)
{
    cscientists.push_back(pers);
    data.update(cscientists);
}

void RequestProcessor::deletePerson()
{
    //TODO IMPLEMENT
}

void RequestProcessor::outputAll() //FOR DEBUGGING
{
    for(int i = 0; i < cscientists.size(); i++)
    {
        std::cout << cscientists[i];
    }
}

//========PRIVATE FUNCTIONS==========
