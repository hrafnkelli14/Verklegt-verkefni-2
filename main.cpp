#include <QCoreApplication>
#include "interface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Interface i;
    i.start();

    return 0;
}

