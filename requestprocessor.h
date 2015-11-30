#include <QString>
#include <QVector>
#include <algorithm>
#include "xmlfile.h"

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

enum ordering{NAME, NAME_R, DOB, DOB_R, DOD, DOD_R}; //enum for order_by setting.. _R means reverse.
enum gendertype{MALE, FEMALE, BOTH}; //enum for view gender settings
//BOTH is for implementation of a politically correct list(and is the default setting)

class RequestProcessor
{
public:
    RequestProcessor();
    void addPerson(const Person &pers); //contains the famous middle-out compression algorithm
    void deletePerson(); //TODO IMPLEMENT
    void editPerson(); //TODO implement
    void outputAll(); //FOR DEBUGGING - TO BE DELETED
    void updateSettings(); //what happens here?

    QVector<Person> outputList(); //this is the real function that is to be used
    QVector<Person> searchList(QString search_string); //TODO implement

    void setOrdering(ordering _order_by); //sets order_by attribute
    void setGenderView(gendertype _view_gender); //sets view_gender attribute

    ordering getOrdering(); //returns order_by attribute
    gendertype getGenderView(); //returns view_gender attribute
private:
    //sorting functions
    void orderByName(QVector<Person> &sortedVector);
    void orderByName_R(QVector<Person> &sortedVector); //TODO implement
    void orderByDoB(QVector<Person> &sortedVector); //TODO implement
    void orderByDoB_R(QVector<Person> &sortedVector); //TODO implement
    void orderByDoD(QVector<Person> &sortedVector); //TODO implement
    void orderByDoD_R(QVector<Person> &sortedVector); //TODO implement

    //gender view functions
    void malesOnly(QVector<Person> &sortedVector); //patriarchial female filter for sortedvector
    void femalesOnly(QVector<Person> &sortedVector); //this makes the sortedvector 37.1% better

    //searching functions
    QVector<Person> searchByName(); //TODO implement
    QVector<Person> searchByDoB(); //TODO implement
    QVector<Person> searchByDoD(); //TODO implement

    QString orderingToQStr();
    QString gendertypeToQStr();
    void readOrdering();
    void readGenderView();

    XmlFile data; //xml file connection
    QVector<Person> cscientists; //vector containing all our scientists

    ordering order_by; //order by setting
    gendertype view_gender; //gender view setting
};

#endif // REQUESTPROCESSOR_H
