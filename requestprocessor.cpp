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

void RequestProcessor::orderByDoB(QVector<Person> &sortedVector) //sets the list in order by date of birth
{
    QString Qtemp;
    Person temp;
    string date1, date2;

    int year1, year2, month1, month2, day1, day2;
    for(int i = 0; i < sortedVector.size(); i++)//loops through the vector to check each date
    {
        for(int j = i+1; j < sortedVector.size(); j++)  //compares each date with the date current lowest at each time
        {
            Qtemp = sortedVector[i].getDoB();
            date1 = Qtemp.toStdString();
            Qtemp = sortedVector[j].getDoB();
            date2 = Qtemp.toStdString();        //sets the dates as a normal string instead of a QString


            year1 = stoi(date1.substr(6,4));
            year2 = stoi(date2.substr(6,4)); //declares two variables as years and sets them as integers with stoi
            month1 = stoi(date1.substr(3,2));
            month2 = stoi(date2.substr(3,2));//declares two variables as months and sets them as integers with stoi
            day1 = stoi(date1.substr(0,2));
            day2 = stoi(date2.substr(0,2)); //declares two variables as months and sets them as integers with stoi

            if(year1 > year2)
            {
                temp = sortedVector[j];
                sortedVector[j] = sortedVector[i];
                sortedVector[i] = temp;
            }
            else if(year1 == year2 && month1 > month2)
            {
                temp = sortedVector[j];
                sortedVector[j] = sortedVector[i];
                sortedVector[i] = temp;
            }
            else if(year1 == year2 && month1 == month2 && day1 > day2)
            {
                temp = sortedVector[j];
                sortedVector[j] = sortedVector[i];
                sortedVector[i] = temp;
            }
        }
    }
}

void RequestProcessor::orderByDoB_R(QVector<Person> &sortedVector) //same as orderByDoB but reverses the output
{
    QString Qtemp;
    Person temp;
    string date1, date2;

    int year1, year2, month1, month2, day1, day2;
    for(int i = 0; i < sortedVector.size(); i++)
    {
        for(int j = i+1; j < sortedVector.size(); j++)
        {
            Qtemp = sortedVector[i].getDoB();
            date1 = Qtemp.toStdString();
            Qtemp = sortedVector[j].getDoB();
            date2 = Qtemp.toStdString();


            year1 = stoi(date1.substr(6,4));
            year2 = stoi(date2.substr(6,4));
            month1 = stoi(date1.substr(3,2));
            month2 = stoi(date2.substr(3,2));
            day1 = stoi(date1.substr(0,2));
            day2 = stoi(date2.substr(0,2));

            if(year1 < year2)
            {
                temp = sortedVector[j];
                sortedVector[j] = sortedVector[i];
                sortedVector[i] = temp;
            }
            else if(year1 == year2 && month1 < month2)
            {
                temp = sortedVector[j];
                sortedVector[j] = sortedVector[i];
                sortedVector[i] = temp;
            }
            else if(year1 == year2 && month1 == month2 && day1 < day2)
            {
                temp = sortedVector[j];
                sortedVector[j] = sortedVector[i];
                sortedVector[i] = temp;
            }
        }
    }
}

void RequestProcessor::orderByDoD(QVector<Person> &sortedVector)
{
    QString Qtemp;
    Person temp;
    string date1, date2;

    QVector<Person> alive, dead;
    for(int i = 0; i < sortedVector.size(); i++) // a loop that sets two vectors, dead with all comp. scientists that are dead
                                                 // and alive with all comp. scientists still alive
    {
        Qtemp = sortedVector[i].getDoD();
        date1 = Qtemp.toStdString();
        if(date1 == "alive")
        {
            alive.push_back(sortedVector[i]);
        }
        else
        {
            dead.push_back(sortedVector[i]);
        }
    }
    int year1, year2, month1, month2, day1, day2;
    for(int i = 0; i < dead.size(); i++)
    {
        for(int j = i+1; j < dead.size(); j++)  //same as orderbyDoB but uses just the dead comp. scientists
        {
            Qtemp = dead[i].getDoD();
            date1 = Qtemp.toStdString();
            Qtemp = dead[j].getDoD();
            date2 = Qtemp.toStdString();


            year1 = stoi(date1.substr(6,4));
            year2 = stoi(date2.substr(6,4));
            month1 = stoi(date1.substr(3,2));
            month2 = stoi(date2.substr(3,2));
            day1 = stoi(date1.substr(0,2));
            day2 = stoi(date2.substr(0,2));

            if(year1 > year2)
            {
                temp = dead[j];
                dead[j] = dead[i];
                dead[i] = temp;
            }
            else if(year1 == year2 && month1 > month2)
            {
                temp = dead[j];
                dead[j] = dead[i];
                dead[i] = temp;
            }
            else if(year1 == year2 && month1 == month2 && day1 > day2)
            {
                temp = dead[j];
                dead[j] = dead[i];
                dead[i] = temp;
            }
        }
    }
    for(int i = sortedVector.size(); i > 0; i--) //removes the current contents of sortedVector
    {
        sortedVector.pop_back();
    }
    for(int i = 0; i < alive.size(); i++)   //adds all scientists alive to dead in order to add to sortedVector
    {
        dead.push_back(alive[i]);
    }
    for(int i = 0; i < dead.size(); i++)
    {
        sortedVector.push_back(dead[i]);    //adds all scientists to sortedVector
    }
}

void RequestProcessor::orderByDoD_R(QVector<Person> &sortedVector)  //same as orderbyDoD but reverses the output
{
    QString Qtemp;
    Person temp;
    string date1, date2;

    QVector<Person> alive, dead;
    for(int i = 0; i < sortedVector.size(); i++)
    {
        Qtemp = sortedVector[i].getDoD();
        date1 = Qtemp.toStdString();
        if(date1 == "alive")
        {
            alive.push_back(sortedVector[i]);
        }
        else
        {
            dead.push_back(sortedVector[i]);
        }
    }
    int year1, year2, month1, month2, day1, day2;
    for(int i = 0; i < dead.size(); i++)
    {
        for(int j = i+1; j < dead.size(); j++)
        {
            Qtemp = dead[i].getDoD();
            date1 = Qtemp.toStdString();
            Qtemp = dead[j].getDoD();
            date2 = Qtemp.toStdString();


            year1 = stoi(date1.substr(6,4));
            year2 = stoi(date2.substr(6,4));
            month1 = stoi(date1.substr(3,2));
            month2 = stoi(date2.substr(3,2));
            day1 = stoi(date1.substr(0,2));
            day2 = stoi(date2.substr(0,2));

            if(year1 < year2)
            {
                temp = dead[j];
                dead[j] = dead[i];
                dead[i] = temp;
            }
            else if(year1 == year2 && month1 < month2)
            {
                temp = dead[j];
                dead[j] = dead[i];
                dead[i] = temp;
            }
            else if(year1 == year2 && month1 == month2 && day1 < day2)
            {
                temp = dead[j];
                dead[j] = dead[i];
                dead[i] = temp;
            }
        }
    }
    for(int i = sortedVector.size(); i > 0; i--)
    {
        sortedVector.pop_back();
    }
    for(int i = 0; i < dead.size(); i++)
    {
        alive.push_back(dead[i]);
    }
    for(int i = 0; i < alive.size(); i++)
    {
        sortedVector.push_back(alive[i]);
    }
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
    else
    {
        order_by = NAME; //defaults to name
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
    else
    {
        view_gender = BOTH; //defaults to both
    }
}
