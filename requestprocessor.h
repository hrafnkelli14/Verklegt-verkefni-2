#include <QString>
#include <QVector>
#include "xmlfile.h"

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

enum ordering{NAME, NAME_R, DOB, DOB_R, DOD, DOD_R}; //enum for order_by setting.. _R means reverse.
enum gendertype{MALE, FEMALE, BOTH}; //enum for view gender settings
//BOTH is for implementation of a politically correct list(and is the default setting)

class RequestProcessor
{
public:
    RequestProcessor();
    void addPerson(const Person &pers);
    void deletePerson(); //TODO IMPLEMENT
    void outputAll(); //FOR DEBUGGING

    void setOrdering(ordering _order_by);
    void setGenderView(gendertype _view_gender);

    ordering getOrdering();
    gendertype getGenderView();
private:
    XmlFile data;
    QVector<Person> cscientists;

    ordering order_by; //order by setting
    gendertype view_gender; //gender view setting
};

#endif // REQUESTPROCESSOR_H
