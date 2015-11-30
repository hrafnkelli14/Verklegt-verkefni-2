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
    XmlFile(QString xmlfilename); //Constructor
    void setFile(QString newfile); //Changes xml source file name(CREATES NEW)
    QVector<Person> getList(); //returns the cscientists vector read from XML
    void update(QVector<Person> newVector); //Update list and write to file
private:
    void writeToFile(); //writes cscientists to XML file
    void readFile(); //Reads XML file
    QString filename; //filename of xml file
    QFile file; //file instance
    QString order_by; //will be converted to enum in requestprocessor
    QString view_gender; //will be converted to enum in requestprocessor
    QXmlStreamWriter xmlwriter; //QXml library writer
    QXmlStreamReader xmlreader; //QXml library reader
    QVector<Person> cscientists; //The scientists read from prump XML
};

#endif // XMLFILE_H
