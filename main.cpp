#include <QCoreApplication>
#include "interface.h"
#include <iostream> //FOR DEBUGGING

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Interface i;
    i.start();

    return a.exec();
}

