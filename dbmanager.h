#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QFileInfo>
#include <QVector>
#include <iostream> //DEBUGGING
#include "person.h"

#ifndef DBMANAGER_H
#define DBMANAGER_H


class DbManager
{
public:
    DbManager();
    bool isRunning();
    bool update(QVector<Person> pers);
    QVector<Person> getList();
private:
    bool execQuery(QString query_string);
    bool createTables();
    bool addPerson(Person pers);
    void readFile();
    QSqlDatabase db;
    bool db_run;
    QVector<Person> cscientists;
};

#endif // DBMANAGER_H
