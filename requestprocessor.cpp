#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
    readSettings();
}

//========PUBLIC FUNCTIONS==========
void RequestProcessor::addPerson(Person pers)
{
    data.addPerson(pers);
}

void RequestProcessor::addComputer(Computer comp)
{
    data.addComputer(comp);
}

void RequestProcessor::updateSettings()
{
    settings.update(personOrderingToQStr(), gendertypeToQStr());
}

QVector<Person> RequestProcessor::outputPersons()
{
    return data.getAllPersons(personOrderingToQStr(), gendertypeToQStr());
}

QVector<Computer> RequestProcessor::outputComputers()
{
    // TODO FIX ORDERING AND TYPE
    return data.getAllComputers("name", "ALL");
}

QVector<Person> RequestProcessor::searchPersons(QString search_string)
{
    QVector<Person> search_results;
    QString search_type = "";
    QString search_query = "";

    int i = 0;
    while(1) //finds searchBy
    {
        if(search_string[i] == ' ')
        {
            break;
        }
        else
        {
            search_type += search_string[i];
        }

        if(i > search_string.length())
        {
            return QVector<Person>();
        }

        i++;
    }

    search_query = search_string.section(' ', 1); //finds the search query itself

    search_results = data.searchPersons(search_type, search_query, personOrderingToQStr(), gendertypeToQStr());
    return search_results;
}

void RequestProcessor::setPersonOrdering(ordering _order_by)
{
    person_order_by = _order_by;
}

void RequestProcessor::setGenderView(gendertype _view_gender)
{
    view_gender = _view_gender;
}

ordering RequestProcessor::getPersonOrdering()
{
    return person_order_by;
}

gendertype RequestProcessor::getGenderView()
{
    return view_gender;
}

//========PRIVATE FUNCTIONS==========
//--settings functions--
QString RequestProcessor::personOrderingToQStr()
{
    switch(person_order_by)
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
    QString orderingQStr = settings.getOrdering();
    if(orderingQStr == "NAME")
    {
        person_order_by = NAME;
    }
    else if(orderingQStr == "NAME_R")
    {
        person_order_by = NAME_R;
    }
    else if(orderingQStr == "DOB")
    {
        person_order_by = DOB;
    }
    else if(orderingQStr == "DOB_R")
    {
        person_order_by = DOB_R;
    }
    else if(orderingQStr == "DOD")
    {
        person_order_by = DOD;
    }
    else if(orderingQStr == "DOD_R")
    {
        person_order_by = DOD_R;
    }
    else
    {
        person_order_by = NAME; //defaults to name
    }
}

void RequestProcessor::readGenderView()
{
    QString genderViewQStr = settings.getViewGender();
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
    else
    {
        view_gender = BOTH; //defaults to both
    }
}

void RequestProcessor::readSettings()
{
    readOrdering();
    readGenderView();
}
