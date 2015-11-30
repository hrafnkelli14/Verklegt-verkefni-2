#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
   data.setFile("data");
   cscientists = data.getList();
   order_by = NAME;
   view_gender = BOTH;
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

void RequestProcessor::editPerson()
{
    //TODO implement
}

void RequestProcessor::outputAll() //FOR DEBUGGING
{
    for(int i = 0; i < cscientists.size(); i++)
    {
        std::cout << cscientists[i] << endl;
    }
}

QVector<Person> RequestProcessor::outputList()
{
   /* switch(order_by)
    {
    case NAME:
        //TODO implement
        break;
    case NAME_R:
        //TODO implement
        break;
        //etc, etc, etc, etc
    }*/

    switch(view_gender)
    {
    case MALE:
        //TODO implement
        break;
    case FEMALE:
        //TODO implement
        break;
    case BOTH:
        //TODO implement
        break;
    }

    return QVector<Person>();
}

QVector<Person> RequestProcessor::searchList()
{
    //TODO implement
    return QVector<Person>();
}

void RequestProcessor::setOrdering(ordering _order_by)
{
    order_by = _order_by;
}

void RequestProcessor::setGenderView(gendertype _view_gender)
{
    view_gender = _view_gender;
}

ordering RequestProcessor::getOrdering()
{
    return order_by;
}

gendertype RequestProcessor::getGenderView()
{
    return view_gender;
}

//========PRIVATE FUNCTIONS==========
//--sorting functions--
QVector<Person> orderByName()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> orderByName_R()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> orderByDoB()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> orderByDoB_R()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> orderByDoD()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> orderByDoD_R()
{
    //TODO implement
    return QVector<Person>();
}

//--searching functions--
QVector<Person> searchByName()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> searchByDoB()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> searchByDoD()
{
    //TODO implement
    return QVector<Person>();
}
