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
    QVector<Person> getList(QString order_by, QString view_gender);
    QVector<Person> searchDb(QString search_type, QString search_query, QString order_by, QString view_gender); //TODO implement
    bool addPerson(Person pers);
    bool deletePerson(Person pers); //TODO implement
    bool editPerson(Person pers); //TODO implement
private:
    bool execQuery(QString query_string);
    bool createTables();
    void readFile();
    QVector<Person> findPersons(QString conditions);

    QString ascOrDesc(QString order_by);

    QSqlDatabase db;
};

#endif // DBMANAGER_H
