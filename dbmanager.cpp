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
        std::cout << createTables();
    }

}
//========PUBLIC FUNCTIONS==========
QVector<Person> DbManager::getList(QString order_by, QString view_gender)
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

QVector<Person> DbManager::searchDb(QString search_type, QString search_query, QString order_by, QString view_gender)
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
    return execQuery("INSERT INTO Persons VALUES"
                     "('" + pers.getName() + "','" +
                     pers.getGender() + "','" +
                     pers.getDoB() + "','" +
                     pers.getDoD() + "')");
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

bool DbManager::createTables()
{
    return execQuery("CREATE TABLE Persons ( "
                     "name TEXT, "
                     "gender TEXT, " //this might be changed to char
                     "dob TEXT, "  //varchar will probably be easier than date.. for now
                     "dod TEXT, "
                     "PRIMARY KEY (name) )"); //might do better with a ID key, but this is good enough for testing
    //will other tables be needed?
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
        temp.setDoB(qry.value(i_dob).toString().toStdString());
        temp.setDoD(qry.value(i_dod).toString().toStdString());
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
