#include <QString>
#include <QVector>
#include "xmlfile.h"

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H


class RequestProcessor
{
public:
    RequestProcessor();
    void addPerson(const Person &pers);
    void deletePerson(); //TODO IMPLEMENT
    void outputAll(); //FOR DEBUGGING
private:
    XmlFile data;
    QVector<Person> cscientists;
};

#endif // REQUESTPROCESSOR_H
