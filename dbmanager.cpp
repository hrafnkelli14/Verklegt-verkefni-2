#include "dbmanager.h"

//========CONSTRUCTORS==========
DbManager::DbManager()
{
    QFileInfo checkFile("data.db");
    bool db_exists = checkFile.exists();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("data.db");

    if(!db_exists)
    {
        createTables();
    }

}
//========PUBLIC FUNCTIONS==========
QVector<Person> DbManager::getAllPersons(QString order_by, QString view_gender)
{
    if(view_gender != "BOTH")
    {
        return findPersons("WHERE gender LIKE '" + view_gender + "' " +
                           "ORDER BY " + ascOrDesc(order_by));
    }
    else
    {
        return findPersons("ORDER BY " + ascOrDesc(order_by));
    }

}

QVector<Person> DbManager::searchPersons(QString search_type, QString search_query, QString order_by, QString view_gender)
{
    if(view_gender != "BOTH")
    {
       return findPersons("WHERE " + search_type + " COLLATE UTF8_GENERAL_CI LIKE '%" + search_query + "%' "
                          "AND gender LIKE '" + view_gender + "' " +
                          "ORDER BY " + ascOrDesc(order_by));
    }
    else
    {
        return findPersons("WHERE " + search_type + " COLLATE UTF8_GENERAL_CI LIKE '%" + search_query + "%' "
                           "ORDER BY " + ascOrDesc(order_by));
    }
}

bool DbManager::addPerson(Person pers)
{
    QString dob_iso = toISO(pers.getDoB());
    QString dod_iso = toISO(pers.getDoD());

    return execQuery("INSERT INTO Persons VALUES"
                     "( NULL, '" +
                     pers.getName() + "','" +
                     pers.getGender() + "','" +
                     dob_iso + "','" +
                     dod_iso + "')");
}

bool DbManager::deletePerson(Person pers)
{
    //TODO implement
    return false;
}

bool DbManager::editPerson(Person pers)
{
    //TODO implement
    return false;
}

//========PRIVATE FUNCTIONS==========
bool DbManager::execQuery(QString query_string)
{
    db.open();
    QSqlQuery qry;
    return qry.exec(query_string);
    db.close();
}

void DbManager::createTables()
{
    execQuery("CREATE TABLE Persons ( "
              "pID INT AUTO_INCREMENT, " //we don't have to worry about ID with auto_increment
              "name VARCHAR[40], "
              "gender VARCHAR[7], " //this might be changed to char
              "dob DATE, "
              "dod DATE, "
              "PRIMARY KEY (pID), "
              "UNIQUE (name) )");

    execQuery("CREATE TABLE Computers ( "
              "cID INT AUTO_INCREMENT, "
              "name VARCHAR[40], "
              "year VARCHAR[5], "
              "built BOOLEAN, "
              "PRIMARY KEY (cID), "
              "UNIQUE (name) )");

    execQuery("CREATE TABLE ComputersXPersons ( "
              "pID INT, "
              "cID INT, "
              "FOREIGN KEY (pID) REFERENCES Persons(pID), "
              "FOREIGN KEY (cID) REFERENCES Computers(cID) )");
}

QVector<Person> DbManager::findPersons(QString conditions)
{
    db.open();
    Person temp;
    QVector<Person> results;
    QSqlQuery qry;

    qry.exec("SELECT name, gender, dob, dod "
             "FROM Persons "
             + conditions);

    int i_name = qry.record().indexOf("name");
    int i_gender = qry.record().indexOf("gender");
    int i_dob = qry.record().indexOf("dob");
    int i_dod = qry.record().indexOf("dod");

    while(qry.next())
    {
        temp.setName(qry.value(i_name).toString().toStdString());
        temp.setGender(qry.value(i_gender).toString().toStdString());
        temp.setDoB(fromISO(qry.value(i_dob).toString()).toStdString());
        temp.setDoD(fromISO(qry.value(i_dod).toString()).toStdString());
        results.push_back(temp);
    }
    db.close();

    return results;
}

QString DbManager::ascOrDesc(QString order_by)
{
    if(order_by.toStdString().find("_R") <= order_by.size())
    {
        QString n_order_by = "";
        for(int i = 0; i < order_by.size(); i++)
        {
            if(order_by[i] == '_')
            {
                break;
            }
            n_order_by += order_by[i];
        }
        return n_order_by + " DESC";
    }
    else
    {
        return order_by + " ASC";
    }
}

QString DbManager::toISO(QString date)
{
    if(date == "alive")
    {
        return "alive";
    }

    QString year = date.mid(6,4);
    QString month = date.mid(3,2);
    QString day = date.mid(0,2);

    return year + '-' + month + '-' + day;
}

QString DbManager::fromISO(QString date)
{
    if(date == "alive")
    {
        return "alive";
    }

    QString year = date.mid(0,4);
    QString month = date.mid(5,2);
    QString day = date.mid(8,2);

    return day + '/' + month + '/' + year;
}
