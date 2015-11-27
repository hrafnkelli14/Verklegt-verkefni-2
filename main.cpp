#include <QCoreApplication>
#include "requestprocessor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RequestProcessor request;
    //request.addPerson("Alan Turing2"); //Adds new person to xml with the name Alan Turing

    return a.exec();
}

