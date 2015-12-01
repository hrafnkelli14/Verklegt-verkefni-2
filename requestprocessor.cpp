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

QVector<Person> RequestProcessor::outputList()
{
    QVector<Person> sortedVector = cscientists;

    switch(order_by)
    {
    case NAME:
        orderByName(sortedVector);
        break;
    case NAME_R:
        orderByName_R(sortedVector);
        break;
    case DOB:
        orderByDoB(sortedVector);
        break;
    case DOB_R:
        orderByDoB_R(sortedVector);
        break;
    case DOD:
        orderByDoD_R(sortedVector);
        break;
    case DOD_R:
        orderByDoD_R(sortedVector);
        break;
    }

    switch(view_gender)
    {
    case MALE:
        malesOnly(sortedVector);
        break;
    case FEMALE:
        femalesOnly(sortedVector);
        break;
    case BOTH:
        //nothing needed
        break;
    }

    return sortedVector; //this shouldn't be reached
}

QVector<Person> RequestProcessor::searchList(QString search_string)
{
    QVector<Person> sortedVector = outputList();
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


    if(QString::compare(search_type, "name", Qt::CaseInsensitive) == 0) //search by NAME
    {
        searchByName(search_query, sortedVector);
    }
    else if(QString::compare(search_type, "dob", Qt::CaseInsensitive) == 0) //search by DOB
    {
        searchByDoB(search_query, sortedVector);
    }
    else if(QString::compare(search_type, "dod", Qt::CaseInsensitive) == 0) //search by DOD
    {
        searchByDoD(search_query, sortedVector);
    }
    else
    {
        //incorrect search type
        return QVector<Person>();
    }


    return sortedVector;
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
void RequestProcessor::orderByName(QVector<Person> &sortedVector)
{
    sort(sortedVector.begin(), sortedVector.end(), Person::lessThanName);
}

void RequestProcessor::orderByName_R(QVector<Person> &sortedVector)
{
    orderByName(sortedVector);
    reverse(sortedVector.begin(), sortedVector.end());
}

void RequestProcessor::orderByDoB(QVector<Person> &sortedVector)
{
    //TODO implement
}

void RequestProcessor::orderByDoB_R(QVector<Person> &sortedVector)
{
    //TODO implement
}

void RequestProcessor::orderByDoD(QVector<Person> &sortedVector)
{
    //TODO implement
}

void RequestProcessor::orderByDoD_R(QVector<Person> &sortedVector)
{
    //TODO implement
}

//--gender view functions--
void RequestProcessor::malesOnly(QVector<Person> &sortedVector)
{
    QVector<Person> malesOnlyCscientists;
    for(int i = 0; i < sortedVector.size(); i++)
    {
        if (sortedVector[i].getGender() == "Male")
        {
            malesOnlyCscientists.push_back(sortedVector[i]);
        }
    }

    sortedVector = malesOnlyCscientists;
}

void RequestProcessor::femalesOnly(QVector<Person> &sortedVector)
{
    QVector<Person> femalesOnlyCscientists;
    for(int i = 0; i < sortedVector.size(); i++)
    {
        if (sortedVector[i].getGender() == "Female")
        {
             femalesOnlyCscientists.push_back(sortedVector[i]);
        }
    }

    sortedVector = femalesOnlyCscientists;
}

//--searching functions--
void RequestProcessor::searchByName(QString search_query, QVector<Person> &sortedVector)
{
    QVector<Person> searchNames;

    for(int i = 0; i < sortedVector.size(); i++)
    {
        string stdNameString = sortedVector[i].getName().toStdString();
        string stdQueryString = search_query.toStdString();
        transform(stdNameString.begin(), stdNameString.end(), stdNameString.begin(), ::toupper); //case insensitive search
        transform(stdQueryString.begin(), stdQueryString.end(), stdQueryString.begin(), ::toupper); //case insensitive search

        if (stdNameString.find(stdQueryString) <= stdNameString.size())
        {
            searchNames.push_back(sortedVector[i]);
        }
    }
    sortedVector = searchNames;
}

void RequestProcessor::searchByDoB(QString search_query, QVector<Person> &sortedVector)
{
    QVector<Person> searchDoB;

    for(int i = 0; i < sortedVector.size(); i++)
    {
        string stdDoBString = sortedVector[i].getDoB().toStdString();
        if (stdDoBString.find(search_query.toStdString()) <= stdDoBString.size())
        {
            searchDoB.push_back(sortedVector[i]);
        }
    }
    sortedVector = searchDoB;
}

void RequestProcessor::searchByDoD(QString search_query, QVector<Person> &sortedVector)
{
    QVector<Person> searchDoD;

    for(int i = 0; i < sortedVector.size(); i++)
    {
        string stdDoDString = sortedVector[i].getDoD().toStdString();
        if (stdDoDString.find(search_query.toStdString()) <= stdDoDString.size())
        {
            searchDoD.push_back(sortedVector[i]);
        }
    }
    sortedVector = searchDoD;
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
