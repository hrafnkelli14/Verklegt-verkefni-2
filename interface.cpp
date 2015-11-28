#include "interface.h"

//========CONSTRUCTORS==========
Interface::Interface()
{
    //...
}

//========PUBLIC FUNCTIONS==========
void Interface::start()
{
    char ch = ' ';

    std::cout << "press (1) to add a person to the list \n"
                 "press (2) to view list \n"
                 "press (3) for list ordering settings \n"
                 "press (4) to exit \n";
    //TODO SOME AWESOME WHILE LOOP THING
    while(ch != '4') //PRIMITIVE WHILE LOOP, VERY TEMPORARY
    {
        std::cin >> ch; //THIS IS VERY VERY TEMPORARY
        switch(ch) //THIS IS ALSO VERY TEMPORARY
        {
        case '1':
            add();
            break;
        case '2':
            request.outputAll(); //should NOT be done this way.. only for testing purposes
            break;
        case '3':
            std::cout << "Allan please add details\n"; //TODO Implement this
            break;
        default:
            break;
        }
    }
}

//========PRIVATE FUNCTIONS==========
void Interface::add()
{
    Person temp;
    cin >> temp;

    request.addPerson(temp);
}

void Interface::orderingSettings()
{
    char ch = ' ';

    std::cout << "press (1) To order list by names in alphabetical order \n"
                 "press (2) To order list by names in reverse alphabetical order \n"
                 "press (3) To order list by etc etc etc \n"
                 "press (4) to exit \n"; //to be continued

    std::cin >> ch;

    switch(ch) //to be continued
    {
    case '1':
        request.setOrdering(NAME);
        break;
    case '2':
        request.setOrdering(NAME_R);
        break;
    case '3':
        request.setOrdering(DOB);
        break;
    default:
        break;
    }
}
