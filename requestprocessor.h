#include <QString>
#include <QVector>
#include "xmlfile.h"

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

enum ordering{NAME, NAME_R, DOB, DOB_R, DOD, DOD_R, GENDER}; //enum for order_by setting.. _R means reverse.

class RequestProcessor
{
public:
    RequestProcessor();
    void addPerson(const Person &pers);
    void deletePerson(); //TODO IMPLEMENT
    void outputAll(); //FOR DEBUGGING
    void setOrdering(ordering _order_by);
private:
    XmlFile data;
    QVector<Person> cscientists;
    ordering order_by; //order by setting, NAME(alphabetical by name) will be default, maybe implement a settings menu in interface?
};

#endif // REQUESTPROCESSOR_H
