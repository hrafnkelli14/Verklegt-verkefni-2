#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
   data.setFile("data");
   cscientists = data.getList();
   readOrdering();
   readGenderView();
}

//========PUBLIC FUNCTIONS==========
void RequestProcessor::addPerson(const Person &pers)
{
    cscientists.push_back(pers);
    data.update(cscientists, orderingToQStr(), gendertypeToQStr());
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

void RequestProcessor::updateSettings()
{
    data.update(cscientists, orderingToQStr(), gendertypeToQStr());
}

QVector<Person> genderSortVector;
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
        for(int i = 0; i < cscientists.size(); i++)
        {
            if (cscientists[i].getGender() == "Male" )
            {
                genderSortVector.push_back(cscientists[i]); //The cscientists vector should not be here, rather is should be a pre-sorted vector
            }
        }
        break;
    case FEMALE:
            for(int i = 0; i < cscientists.size(); i++)
            {
                if (cscientists[i].getGender() == "Female")
                {
                     genderSortVector.push_back(cscientists[i]); //The cscientists vector should not be here, rather is should be a pre-sorted vector
                }
            }
        break;
    case BOTH:
            genderSortVector = cscientists; //The cscientists vector should not be here, rather is should be a pre-sorted vector
        break;
    }



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
QVector<Person> RequestProcessor::orderByName()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> RequestProcessor::orderByName_R()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> RequestProcessor::orderByDoB()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> RequestProcessor::orderByDoB_R()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> RequestProcessor::orderByDoD()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> RequestProcessor::orderByDoD_R()
{
    //TODO implement
    return QVector<Person>();
}

//--searching functions--
QVector<Person> RequestProcessor::searchByName()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> RequestProcessor::searchByDoB()
{
    //TODO implement
    return QVector<Person>();
}

QVector<Person> RequestProcessor::searchByDoD()
{
    //TODO implement
    return QVector<Person>();
}

//--helpers--
QString RequestProcessor::orderingToQStr()
{
    switch(order_by)
    {
    case NAME:
        return "NAME";
        break;
    case NAME_R:
        return "NAME_R";
        break;
    case DOB:
        return "DOB";
        break;
    case DOB_R:
        return "DOB_R";
        break;
    case DOD:
        return "DOD";
        break;
    case DOD_R:
        return "DOD_R";
        break;
    }

    return "";
}

QString RequestProcessor::gendertypeToQStr()
{
    switch(view_gender)
    {
    case MALE:
        return "MALE";
        break;
    case FEMALE:
        return "FEMALE";
        break;
    case BOTH:
        return "BOTH";
        break;
    }

    return "";
}

void RequestProcessor::readOrdering()
{
    QString orderingQStr = data.getOrdering();
    if(orderingQStr == "NAME")
    {
        order_by = NAME;
    }
    else if(orderingQStr == "NAME_R")
    {
        order_by = NAME_R;
    }
    else if(orderingQStr == "DOB")
    {
        order_by = DOB;
    }
    else if(orderingQStr == "DOB_R")
    {
        order_by = DOB_R;
    }
    else if(orderingQStr == "DOD")
    {
        order_by = DOD;
    }
    else if(orderingQStr == "DOD_R")
    {
        order_by = DOD_R;
    }
}

void RequestProcessor::readGenderView()
{
    QString genderViewQStr = data.getViewGender();
    if(genderViewQStr == "MALE")
    {
        view_gender = MALE;
    }
    else if(genderViewQStr == "FEMALE")
    {
        view_gender = FEMALE;
    }
    else if(genderViewQStr == "BOTH")
    {
        view_gender = BOTH;
    }
}
