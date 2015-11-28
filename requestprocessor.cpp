#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
   data.setFile("data");
   cscientists = data.getList();
   order_by = NAME;
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

void RequestProcessor::setOrdering(ordering _order_by)
{
    order_by = _order_by;
}

//========PRIVATE FUNCTIONS==========
