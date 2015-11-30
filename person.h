#ifndef PERSON
#define PERSON

#include <string>
#include <fstream>
#include <iostream>
#include <QString>
#include <QDate>

using namespace std;

class Person{
private:
    string name;
    string gender;
    string date_of_birth;
    string date_of_death;

    bool checkDateFormat(string date); //checks if date follows DD/MM/YYYY format
    QDate strToQDate(string date); //changes date string to QDate for input testing
public:
    Person();   //default constructor

    //needed to add more 'get' functions for db 'read from' functionality
    QString getName(); //returns the name of a computer scientist //attribute not needed
    QString getGender();
    QString getDoB();
    QString getDoD();

    //needed to add 'set' functions for db 'read to' functionality
    void setName(string _name);
    void setGender(string _gender);
    void setDoB(string dob);
    void setDoD(string dod);

    friend std::istream& operator >>(std::istream& ins, Person& person1);   //overloads the >> operator to read into the variable person
    friend std::ostream& operator <<(std::ostream& os, Person person1);     //overloads the << operator to write out the contants of a variable person
};
#endif // PERSON
