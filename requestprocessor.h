#include <QString>
#include <QVector>
#include <algorithm>
#include "xmlfile.h"
#include "dbmanager.h"

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

enum personordering{NAME, NAME_R, DOB, DOB_R, DOD, DOD_R}; //enum for order_by setting.. _R means reverse.
enum computerordering{CNAME, CNAME_R, YEAR, YEAR_R, TYPE, TYPE_R};
enum gendertype{MALE, FEMALE, BOTH}; //enum for view gender settings
//BOTH is for implementation of a politically correct list(and is the default setting)

class RequestProcessor
{
public:
    RequestProcessor();
    void addPerson(Person pers); //contains the famous middle-out compression algorithm
    void addComputer(Computer comp);

    void updateSettings(); //what happens here?

    QVector<Person> outputPersons();
    QVector<Computer> outputComputers();
    ComputerXPersons outputComputerXPersons(QString cid);
    PersonXComputers outputPersonXComputers(QString pid);
    QVector<Person> searchPersons(QString search_string);
    QVector<Computer> searchComputers(QString search_string);

    void setPersonOrdering(personordering _order_by); //sets order_by attribute
    void setComputerOrdering(computerordering _order_by);
    void setGenderView(gendertype _view_gender); //sets view_gender attribute

    personordering getPersonOrdering(); //returns order_by attribute
    computerordering getComputerOrdering();
    gendertype getGenderView(); //returns view_gender attribute

private:
    //settings functions
    QString personOrderingToQStr();
    QString computerOrderingToQStr();
    QString gendertypeToQStr();
    void readPersonOrdering();
    void readComputerOrdering();
    void readGenderView();
    void readSettings();

    XmlFile settings; //xml file connection(settings)
    DbManager data; //sql database connection

    personordering person_order_by; //order by setting
    computerordering computer_order_by;
    gendertype view_gender; //gender view setting
};

#endif // REQUESTPROCESSOR_H
