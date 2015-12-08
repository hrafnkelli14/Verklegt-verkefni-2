#include "requestprocessor.h"
#include "oscheck.h"

#ifndef INTERFACE_H
#define INTERFACE_H

class Interface
{
public:
    Interface();
    ~Interface();
    void start(); //essentially the main menu
private:
    //menus
    void addCompOrPerson();
    void addPerson();
    void addComputer();
    void viewCompsOrPersons();
    void viewPersons();
    void viewComputers();
    void searchResultsPersons(string search_string);
    void searchResultsComputers(string search_string);
    void viewPersonXComputers(QString id);
    void viewComputerXPersons(QString id);

    void doCommand(QString search_string, char type);
    void editPerson(QString id);
    void editComputer(QString id);
    void deletePerson(QString id);
    void deleteComputer(QString id);
    void addPersonRelation(QString id);
    void addComputerRelation(QString id);

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
    void waitForAnyKey();

    //relation helpers
    void checkRelation();
    bool second_view;
    QString r_pid;
    QString r_cid;

    string current_status; //current status (to display in main menu)
    string current_settings; //current settings (to display in various menus)

    string clear_command; //clear console command(see constructor)

    RequestProcessor request;
};

#endif // INTERFACE_H
