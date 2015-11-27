#include <QCoreApplication>
#include "requestprocessor.h"
#include <iostream> //FOR DEBUGGING

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RequestProcessor request;
    Person pers;
    //cin >> pers;
    //request.addPerson(pers); //Adds new person to xml

    request.outputAll(); //DEBUGGING

    return a.exec();
}

