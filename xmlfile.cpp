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

    checkFile();
    readFile();
}


QVector<QString> XmlFile::getList()
{
    return cscientists;
}

void XmlFile::update(QVector<QString> newVector)
{
    cscientists = newVector;
    writeToFile();
}

//========PRIVATE FUNCTIONS==========
void XmlFile::writeToFile() //Writes the vector to file
{
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlwriter(&file);
    xmlwriter.setAutoFormatting(true);
    xmlwriter.writeStartDocument();

    xmlwriter.writeStartElement("scientists");
    for(int i = 0; i < cscientists.size(); i++)
    {
        xmlwriter.writeStartElement("scientist");
        xmlwriter.writeTextElement("name", cscientists[i]);
        xmlwriter.writeEndElement();
    }
    xmlwriter.writeEndElement();

    file.close();
}

void XmlFile::createNewFile()
{
    file.open(QIODevice::WriteOnly);
    xmlwriter.writeStartDocument();
    xmlwriter.writeStartElement("scientist");
    xmlwriter.writeEndElement();

    file.close();
}

void XmlFile::checkFile()
{
    if (!file.exists())
    {
        createNewFile();
    }
}

void XmlFile::readFile()
{
   file.open(QIODevice::ReadOnly);
   xmlreader.setDevice(&file);

   QString tempname = "";


   xmlreader.readNext();
   while(!xmlreader.atEnd())
   {
       if(xmlreader.isStartElement())
       {
           if(xmlreader.name() == "scientist")
           {
               xmlreader.readNext();
           }

           //
           if(xmlreader.name() == "name")
           {
               tempname = xmlreader.readElementText();
               xmlreader.readNext();
               cscientists.push_back(tempname); //this has to be in the last tag within scientist
           }
           //

       }
       else if (xmlreader.isEndElement())
       {
           xmlreader.readNext();
       }
       xmlreader.readNext();
   }

   file.close();
}
