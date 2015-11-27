#include <QCoreApplication>
#include "requestprocessor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RequestProcessor newxml;
    newxml.addPerson("Alan Turing"); //Adds new person to xml with the name Alan Turing

    return a.exec();
}

