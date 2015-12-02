#include <QCoreApplication>
#include "interface.h"
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Interface i;
    i.start();

    return 0;
}

