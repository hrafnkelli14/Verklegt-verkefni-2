#include <QString>
#include <QVector>
#include <algorithm>
#include "xmlfile.h"
#include "dbmanager.h"

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

enum ordering{NAME, NAME_R, DOB, DOB_R, DOD, DOD_R}; //enum for order_by setting.. _R means reverse.
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
    QVector<Person> searchPersons(QString search_string); //ordering and view now broken since it searches straight from Db

    void setPersonOrdering(ordering _order_by); //sets order_by attribute
    void setGenderView(gendertype _view_gender); //sets view_gender attribute

    ordering getPersonOrdering(); //returns order_by attribute
    gendertype getGenderView(); //returns view_gender attribute

private:
    //settings functions
    QString orderingToQStr();
    QString gendertypeToQStr();
    void readOrdering();
    void readGenderView();
    void readSettings(); //combination of readOrdering() and readGenderView()

    XmlFile settings; //xml file connection(settings)
    DbManager data; //sql database connection

    ordering person_order_by; //order by setting
    gendertype view_gender; //gender view setting
};

#endif // REQUESTPROCESSOR_H
