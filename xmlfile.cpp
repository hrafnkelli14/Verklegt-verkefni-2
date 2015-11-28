#include "xmlfile.h"

//========CONSTRUCTORS==========
XmlFile::XmlFile()
{
    //JUST LEAVE THIS EMPTY
}

XmlFile::XmlFile(QString xmlfilename)
{
    setFile(xmlfilename);
}

//========PUBLIC FUNCTIONS==========
void XmlFile::setFile(QString newfile)
{
    filename = newfile + ".xml";
    file.setFileName(filename);
    xmlwriter.setDevice(&file);
    xmlreader.setDevice(&file);

    readFile();
}


QVector<Person> XmlFile::getList()
{
    return cscientists;
}

void XmlFile::update(QVector<Person> newVector)
{
    cscientists = newVector;
    writeToFile();
}

//========PRIVATE FUNCTIONS==========
void XmlFile::writeToFile() //Writes the vector to file
{
    file.open(QIODevice::WriteOnly);

    xmlwriter.setAutoFormatting(true);
    xmlwriter.writeStartDocument();

    xmlwriter.writeStartElement("scientists");
    for(int i = 0; i < cscientists.size(); i++)
    {
        xmlwriter.writeStartElement("scientist");
        xmlwriter.writeTextElement("name", cscientists[i].getName());
        xmlwriter.writeTextElement("gender", cscientists[i].getGender());
        xmlwriter.writeTextElement("dob", cscientists[i].getDoB());
        xmlwriter.writeTextElement("dod", cscientists[i].getDoD());
        xmlwriter.writeEndElement();
    }
    xmlwriter.writeEndElement();

    file.close();
}

void XmlFile::readFile()
{
    if(!file.exists())
    {
        return;
    }
    file.open(QIODevice::ReadOnly);
    xmlreader.setDevice(&file);

    QString tempqstr = "";
    string tempstr = "";
    Person temp;

    xmlreader.readNext();
    while(!xmlreader.atEnd()) //this is super ugly, BUT IT WORKS!. Everything I've tried to clean it up breaks its functionality.. BEWARE
    {
        if(xmlreader.isStartElement())
        {

            if(xmlreader.name() == "scientist")
            {
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "name")
            {
                tempqstr = xmlreader.readElementText();
                tempstr = tempqstr.toUtf8();
                temp.setName(tempstr);
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "gender")
            {
                tempqstr = xmlreader.readElementText();
                tempstr = tempqstr.toUtf8();
                temp.setGender(tempstr);
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "dob")
            {
                tempqstr = xmlreader.readElementText();
                tempstr = tempqstr.toUtf8();
                temp.setDoB(tempstr);
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "dod")
            {
                tempqstr = xmlreader.readElementText();
                tempstr = tempqstr.toUtf8();
                temp.setDoD(tempstr);
                xmlreader.readNext();
                cscientists.push_back(temp); //this has to be in the last tag within scientist
            }
       }
       else if (xmlreader.isEndElement())
       {
           xmlreader.readNext();
       }
       xmlreader.readNext();
   }

   file.close();
}
