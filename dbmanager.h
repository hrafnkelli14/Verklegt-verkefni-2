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
    DbManager(); //main constructor
    QVector<Person> getAllPersons(QString order_by, QString view_gender); //outputs list according to order_by and view_gender
    QVector<Person> searchPersons(QString search_type, QString search_query, QString order_by, QString view_gender); //searches in list according to order_by and view_gender
    bool addPerson(Person pers); //adds person to Person table
    bool deletePerson(Person pers); //TODO implement
    bool editPerson(Person pers); //TODO implement
private:
    bool execQuery(QString query_string); //executes query.
    void createTables(); //creates needed tables for the program
    QVector<Person> findPersons(QString conditions); //finds persons based on conditions in condition string(they must have an sql syntax)

    //helpers
    QString ascOrDesc(QString order_by);
    QString toISO(QString date);
    QString fromISO(QString date);

    QSqlDatabase db;
};

#endif // DBMANAGER_H
