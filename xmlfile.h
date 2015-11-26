#include <QFile>
#include <QString>
#include <QXmlStreamWriter>

#ifndef XMLFILE_H
#define XMLFILE_H


class xmlfile {
public:
    xmlfile(QString xmlfilename); //Constructor
    void addPerson(QString newname); //Adds new Person, TODO: Create a 'Person' struct with DoB, name etc
private:
    void createNewFile(); //Creates a new xml file if there isn't a corresponding one
    QString filename; //filename of xml file
    QFile file;
    QXmlStreamWriter xmlwriter;
};

#endif // XMLFILE_H
