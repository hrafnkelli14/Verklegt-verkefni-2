#include "xmlfile.h"

//========CONSTRUCTOR==========
xmlfile::xmlfile(QString xmlfilename)
{
    filename = xmlfilename + ".xml";
    file.setFileName(filename);
    initializeWriter();

    if (!file.exists())
    {
        createNewFile();
    }

}

//========PUBLIC FUNCTIONS==========
void xmlfile::addPerson(QString newname) //Adds new Person, TODO: Create a 'Person' struct with DoB, name etc
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

//========PRIVATE FUNCTIONS==========
void xmlfile::initializeWriter()
{
    xmlwriter.setDevice(&file);
}

void xmlfile::createNewFile()
{
    file.open(QIODevice::WriteOnly);
    xmlwriter.writeStartDocument();
    file.close();
}
