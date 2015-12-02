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
bool DbManager::update(QVector<Person> newVector)
{
    bool personsAdded = false;

    if(newVector.isEmpty())
    {
        return false;
    }

    for(int i = 0; i < newVector.size(); i++)
    {
        if(std::find(cscientists.begin(), cscientists.end(), newVector[i]) == cscientists.end())
        {
            personsAdded = addPerson(newVector[i]);
        }
    }

    return personsAdded;
}

QVector<Person> DbManager::getList()
{
    readFile();
    return cscientists;
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

bool DbManager::addPerson(Person pers)
{
    return execQuery("INSERT INTO Persons VALUES"
              "('" + pers.getName() + "','" +
              pers.getGender() + "','" +
              pers.getDoB() + "','" +
              pers.getDoD() + "')");
}

void DbManager::readFile()
{
    db.open();
    Person temp;
    QSqlQuery qry;

    qry.exec("SELECT name, gender, dob, dod "
              "FROM Persons");

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
        cscientists.push_back(temp);
    }
    db.close();
}
