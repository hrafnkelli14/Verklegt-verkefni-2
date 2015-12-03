#include <QString>
#include <string>

#ifndef COMPUTER_H
#define COMPUTER_H

using namespace std;

class Computer
{
public:
    Computer();

    //'get' functions
    QString getName(); //TODO implement
    QString getYear(); //TODO implement
    QString getType(); //TODO implement
    bool getBuilt();   //TODO implement

    //'set' functions
    void setName(string _name); //TODO implement
    void setYear(string _year_of_build); //TODO implement
    void setType(string _type); //TODO implement
    void setBuilt(bool _was_built); //TODO implement
private:
    string name;
    string year_of_build;
    string type;
    bool was_built;

    friend std::istream& operator >>(std::istream& ins, Computer& comp); //TODO implement
    friend std::ostream& operator <<(std::ostream& os, Computer comp); //TODO implement
};

#endif // COMPUTER_H
