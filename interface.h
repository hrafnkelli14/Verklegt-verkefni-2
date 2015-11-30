#include "requestprocessor.h"

#ifndef INTERFACE_H
#define INTERFACE_H

class Interface
{
public:
    Interface();
    void start(); //essentially the main menu
private:
    void add(); //adds a new person
    void output(); //output menu

    //other menus
    void settingsMain(); //TODO finish this
    void settingsOrdering();
    void settingsGenders();

    //helpers
    void clearConsole(); //should clear the console window (NOTE: not tested for unix based systems, commented out)
    void printMainMenu(); //prints the main menu text
    void setStatus(string newstatus); //sets current_status
    void setSettingsStatus(); //sets current_settings according to the values in request processor
    void printStatus(); //prints status
    void printSettingsStatus(); //prints settings status
    void printMenuHead(string menuname); //prints header of a menu
    void printLines(); //prints "===================================================" easier for consistency
    void newMenu(string menuname); //combination of clearConsole(), printSettingsStatus(), printMenuHead() and printLines();

    string current_status; //current status (to display in main menu)
    string current_settings; //current settings (to display in various menus)

    RequestProcessor request;
};

#endif // INTERFACE_H
