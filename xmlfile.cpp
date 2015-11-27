#include "xmlfile.h"

//========CONSTRUCTORS==========
XmlFile::XmlFile()
{
    //JUST LEAVE THIS EMPTY
}

XmlFile::XmlFile(QString xmlfilename)
{
    filename = xmlfilename + ".xml";
    file.setFileName(filename);
    xmlwriter.setDevice(&file);

    checkExists();
}

//========PUBLIC FUNCTIONS==========
void XmlFile::addPerson(QString newname) //Adds new Person, TODO: Create a 'Person' struct with DoB, name etc
{
    QString name = newname; //done this way for easier struct implementation
    //QString dateofbirth = newdob

    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QXmlStreamWriter xmlwriter(&file);
    xmlwriter.setAutoFormatting(true);

    xmlwriter.writeStartElement("person");
    xmlwriter.writeTextElement("name", name);
    //xmlwriter.writeTextElement("dateofbirth", dateofbirth); //TODO struct
    xmlwriter.writeEndElement();

    file.close();

}

void XmlFile::setFile(QString newfile)
{
    filename = newfile + ".xml";
    file.setFileName(filename);
    xmlwriter.setDevice(&file);

    checkExists();
}

void XmlFile::deletePerson(QString name)
{
    //TODO
}

//========PRIVATE FUNCTIONS==========
void XmlFile::createNewFile()
{
    file.open(QIODevice::WriteOnly);
    xmlwriter.writeStartDocument();
    file.close();
}

void XmlFile::checkExists()
{
    if (!file.exists())
    {
        createNewFile();
    }
}
