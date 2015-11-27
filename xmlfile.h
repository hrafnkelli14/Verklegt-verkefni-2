#include <QFile>
#include <QString>
#include <QXmlStreamWriter>

#ifndef XMLFILE_H
#define XMLFILE_H


class XmlFile {
public:
    XmlFile(); //Constructor
    XmlFile(QString xmlfilename); //Constructor
    void addPerson(QString newname); //Adds new Person, TODO: Create a 'Person' struct with DoB, name etc
    void setFile(QString newfile); //Changes xml source file name(CREATES NEW)
private:
    void createNewFile(); //Creates a new xml file if there isn't a corresponding one
    void checkExists(); //Does the file exist?
    QString filename; //filename of xml file
    QFile file;
    QXmlStreamWriter xmlwriter;
};

#endif // XMLFILE_H
