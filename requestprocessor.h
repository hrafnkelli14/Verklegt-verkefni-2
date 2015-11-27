#include <QString>
#include <QVector>
#include "xmlfile.h"

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H


class RequestProcessor
{
public:
    RequestProcessor();
    void addPerson(QString personname);
    void deletePerson(); //TODO IMPLEMENT
private:
    XmlFile data;
    QVector<QString> cscientists;
};

#endif // REQUESTPROCESSOR_H
