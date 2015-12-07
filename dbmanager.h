#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QFileInfo>
#include <QVector>
#include <iostream> //DEBUGGING
#include "person.h"
#include "computer.h"
#include "computerxpersons.h"
#include "personxcomputers.h"

#ifndef DBMANAGER_H
#define DBMANAGER_H


class DbManager
{
public:
    DbManager(); //main constructor
    ~DbManager();
    QVector<Person> getAllPersons(QString order_by, QString view_gender); //outputs list according to order_by and view_gender
    QVector<Computer> getAllComputers(QString order_by);
    QVector<Person> searchPersons(QString search_type, QString search_query, QString order_by, QString view_gender);
    QVector<Computer> searchComputers(QString search_type, QString search_query, QString order_by);
    ComputerXPersons getComputerXPersons(QString cid); //this might have a better way to be implemented
    PersonXComputers getPersonXComputers(QString pid); //TODO implement
    bool addPerson(Person pers); //adds person to Person table
    bool addComputer(Computer comp);
    bool addComputerXPerson(QString cid, QString pid);
    bool deletePerson(QString pid);
    bool deleteComputer(QString cid);
    bool deleteComputerXPerson(QString cid, QString pid);
    bool editPerson(Person pers);
    bool editComputer(Computer comp);
    Person getPerson(QString pid);
    Computer getComputer(QString cid);
private:
    bool execQuery(QString query_string); //executes query.
    void createTables(); //creates needed tables for the program
    QVector<Person> findPersons(QString conditions); //finds persons based on conditions in condition string(they must have an sql syntax)
    QVector<Computer> findComputers(QString conditions);

    //helpers
    QString ascOrDesc(QString order_by);
    QString toISO(QString date);
    QString fromISO(QString date);


    QSqlDatabase db;
};

#endif // DBMANAGER_H
