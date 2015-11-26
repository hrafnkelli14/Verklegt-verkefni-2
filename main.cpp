#include <QCoreApplication>
#include "xmlfile.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    xmlfile newxml("data");
    //newxml.addPerson("Alan Turing"); //Adds new person to xml with the name Alan Turing

    return a.exec();
}

