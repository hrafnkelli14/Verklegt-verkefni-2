#include "xmlfile.h"

//========CONSTRUCTORS==========
XmlFile::XmlFile()
{
    order_by = "NAME";
    view_gender = "BOTH";

    filename = "settings.xml";
    file.setFileName(filename);
    xmlwriter.setDevice(&file);
    xmlreader.setDevice(&file);

    readFile();
}

//========PUBLIC FUNCTIONS==========
QString XmlFile::getOrdering()
{
    return order_by;
}

QString XmlFile::getViewGender()
{
    return view_gender;
}

void XmlFile::update(QString _order_by, QString _view_gender)
{
    order_by = _order_by;
    view_gender = _view_gender;
    writeToFile();
}

//========PRIVATE FUNCTIONS==========
void XmlFile::writeToFile() //Writes the vector to file
{
    file.open(QIODevice::WriteOnly);

    xmlwriter.setAutoFormatting(true);
    xmlwriter.writeStartDocument();

    xmlwriter.writeStartElement("settings");
    xmlwriter.writeTextElement("order_by", order_by);
    xmlwriter.writeTextElement("view_gender", view_gender);
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

    xmlreader.readNext();
    while(!xmlreader.atEnd()) //this is super ugly, BUT IT WORKS!. Everything I've tried to clean it up breaks its functionality.. BEWARE
    {
        if(xmlreader.isStartElement())
        {
            // <settings>
            if(xmlreader.name() == "settings")
            {
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "order_by")
            {
                order_by = xmlreader.readElementText();
                xmlreader.readNext();
            }
            else if(xmlreader.name() == "view_gender")
            {
                view_gender = xmlreader.readElementText();
                xmlreader.readNext();
            }
            // </settings>
       }
       else if (xmlreader.isEndElement())
       {
           xmlreader.readNext();
       }
       xmlreader.readNext();
    }
    file.close();
}
