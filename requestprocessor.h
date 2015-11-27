#include <QString>
#include "xmlfile.h"

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H


class RequestProcessor
{
public:
    RequestProcessor();
    void addPerson(QString personName);
private:
    XmlFile data;
    void getPersons(); //TODO
    //RESERVED FOR COMPUTER SCIENTIST VECTOR
};

#endif // REQUESTPROCESSOR_H
