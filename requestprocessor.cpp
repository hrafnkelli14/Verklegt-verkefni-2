#include "requestprocessor.h"

//========CONSTRUCTORS==========
RequestProcessor::RequestProcessor()
{
    readSettings();
}

//========PUBLIC FUNCTIONS==========
void RequestProcessor::addPerson(const Person &pers)
{
    data.addPerson(pers);
}

void RequestProcessor::updateSettings()
{
    settings.update(orderingToQStr(), gendertypeToQStr());
}

QVector<Person> RequestProcessor::outputList()
{
    return data.getList(orderingToQStr(), gendertypeToQStr());
}

QVector<Person> RequestProcessor::searchList(QString search_string)
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

    search_results = data.searchDb(search_type, search_query, orderingToQStr(), gendertypeToQStr());
    return search_results;
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
//--settings functions--
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
    QString orderingQStr = settings.getOrdering();
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
    else
    {
        order_by = NAME; //defaults to name
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
