#include "requestprocessor.h"

#ifndef INTERFACE_H
#define INTERFACE_H

class Interface
{
public:
    Interface();
    void start(); //essentially the main menu
private:
    //menus
    void addPerson();
    void addComputer();
    void outputPersons();
    void outputComputers();
    void searchPersons();
    void searchComputers();

    //settings menus
    void settingsMain();
    void settingsPersonOrdering();
    void settingsComputerOrdering();
    void settingsGenders();

    void about();

    //helpers
    void clearConsole(); //should clear the console window (NOTE: not tested for unix based systems, commented out)
    void printMainMenu(); //prints the main menu text
    void setStatus(string newstatus); //sets current_status
    void setSettingsStatus(); //sets current_settings according to the values in request processor
    void printStatus(); //prints status
    void printSettingsStatus(); //prints settings status
    void printMenuHead(string menuname); //prints header of a menu
    void printLines(); //prints "===================================================\n" easier for consistency
    void printSimpleLines(); //prints "------------------------------------------------------------------------\n" easier for consistency
    void newMenu(string menuname); //combination of clearConsole(), printSettingsStatus(), printMenuHead() and printLines();
    void waitForAnyKey(); //waits for any key

    string current_status; //current status (to display in main menu)
    string current_settings; //current settings (to display in various menus)

    RequestProcessor request;
};

#endif // INTERFACE_H
