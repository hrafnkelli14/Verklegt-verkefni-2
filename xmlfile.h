#include <QFile>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QVector>
#include "person.h"

#ifndef XMLFILE_H
#define XMLFILE_H


class XmlFile {
public:
    XmlFile(); //Constructor
    QString getOrdering(); //returns ordering as string
    QString getViewGender(); //returns view gender as string
    void update(QString _order_by, QString _getViewGender); //Update list and write to file
private:
    void writeToFile(); //writes cscientists to XML file
    void readFile(); //Reads XML file
    QString filename; //filename of xml file
    QFile file; //file instance
    QString order_by; //will be converted to enum in requestprocessor
    QString view_gender; //will be converted to enum in requestprocessor
    QXmlStreamWriter xmlwriter; //QXml library writer
    QXmlStreamReader xmlreader; //QXml library reader
};

#endif // XMLFILE_H
