#ifndef PERSON
#define PERSON

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class person{
private:
    string name;
    string gender;
    string date_of_birth;
    string date_of_death;

public:
    person();   //default constructor
    string getName(person person1); //returns the name of a computer scientist

    friend std::istream& operator >>(std::istream& ins, person& person1);   //overloads the >> operator to read into the variable person
    friend std::ostream& operator <<(std::ostream& os, person person1);     //overloads the << operator to write out the contants of a variable person
};
#endif // PERSON
