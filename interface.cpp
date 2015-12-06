#include "interface.h"

//========CONSTRUCTORS==========
Interface::Interface()
{ 
    setSettingsStatus();
    current_status = "";
}

//========PUBLIC FUNCTIONS==========
void Interface::start()
{
    char ch = ' ';

    while(ch != '4')
    {
        printMainMenu();
        setStatus(""); //reset status message

        cout << "Choice: ";
        cin >> ch;
        switch(ch)
        {
        case 'a':
            about();
            break;
        case '1':
            addCompOrPerson();
            break;
        case '2':
            searchCompsOrPersons();
            break;
        case '3':
            settingsMain();
            break;
        case 't':
            cout << request.outputComputerXPersons("1"); //TODO CREATE MENU
            waitForAnyKey();
        case 'y':
            cout << request.outputPersonXComputers("1"); //TODO CREATE MENU
            waitForAnyKey();
        case 'u':
            addComputerXPerson();
        default:
            break;
        }
    }
}

//========PRIVATE FUNCTIONS==========
//--menus--
void Interface::addCompOrPerson()
{
    newMenu("ADD VIEW");

    char ch = ' ';

    cout << "(1) to add a computer scientist\n"
            "(2) to add a computer\n"
            "enter anything else to go to main menu \n";
    printLines();

    cout << "Choice: ";
    cin.ignore(1, '\n');
    ch = cin.get();

    switch(ch)
    {
    case '1':
        addPerson();
        break;
    case '2':
        addComputer();
        break;
    default:
        break;
    }


}

void Interface::addPerson()
{  
    clearConsole();
    printLines();
    printMenuHead("ADD PERSON");
    Person temp;
    char ch;
    cin >> temp;

    cout << "Are you sure you want to add " << temp.getName().toStdString() << "?(y/n): ";
    cin >> ch;
    if(ch == 'y' || ch == 'Y')
    {
       if(request.addPerson(temp))
       {
            setStatus("\"" + temp.getName().toStdString() + "\" added to computer scientists!");
       }
       else
       {
           setStatus("\"" + temp.getName().toStdString() + "\" could not be added to computer scientists!");
       }
    }
}

void Interface::addComputer()
{
    clearConsole();
    printLines();
    printMenuHead("ADD COMPUTER");
    Computer temp;
    char ch;
    cin >> temp;

    cout << "Are you sure you want to add " << temp.getName().toStdString() << "?(y/n): ";
    cin >> ch;
    if(ch == 'y' || ch == 'Y')
    {
        if(request.addComputer(temp))
        {
            setStatus("\"" + temp.getName().toStdString() + "\" added to computers!");
        }
        else
        {
            setStatus("\"" + temp.getName().toStdString() + "\" could not be added to computers!");
        }
    }
}

void Interface::addComputerXPerson()
{
    QString cid = "";
    QString pid = "";
    string temp;

    cout << "Personid:";
    cin >> temp;
    pid = QString::fromStdString(temp);
    cout << "Computerid:";
    cin >> temp;
    cid = QString::fromStdString(temp);
    request.addComputerXPerson(cid, pid);
}

void Interface::searchCompsOrPersons()
{
    newMenu("SEARCH VIEW");

    char ch = ' ';

    cout << "(1) to search for computer scientists\n"
            "(2) to search for computers\n"
            "enter anything else to go to main menu \n";
    printLines();

    cout << "Choice: ";
    cin.ignore(1, '\n');
    ch = cin.get();

    switch(ch)
    {

    case '1':
        searchPersons();
        break;
    case '2':
        searchComputers();
        break;
    default:
        break;
    }


}

void Interface::searchPersons()
{
    //searching menu
    newMenu("PERSON SEARCH");
    cout << "'*' to view all\n"
            "Search syntax: \"searchtype searchquery\"\n"
            "Available search types:\n"
            "'name'   -- searches for names containing query\n"
            "'dob'    -- searches for dates of birth containing query (DD/MM/YYYY)\n"
            "'dod'    -- searches for dates of death containing query - also accepts 'alive'\n"
            "'id'     -- searches for for computer with specified id\n"
            "Command syntax: \"command id\"\n"
            "'edit'   -- edits a person via id number\n"
            "'delete' -- deletes a person via id number\n"
            "Search results follow current settings\n";
    printSimpleLines();


    cin.ignore(1000, '\n');

    while(1)
    {
        cout << "Search query(empty to exit to main menu): ";
        char ch = ' ';
        string search_string = "";

        do
        {
            ch = cin.get();
            if(ch != '\n')
            {
                search_string += ch;
            }
        }while(ch != '\n');
    //

         if(search_string == "")
         {
            return;
         }

    //search results
         if(request.isCommand(QString::fromStdString(search_string)))
         {
             doCommand(QString::fromStdString(search_string), 'p');
             return;
         }

         QVector<Person> search_results = request.searchPersons(QString::fromStdString(search_string));
         clearConsole();
         printLines();
         printMenuHead("SEARCH RESULTS");

         if(search_results.size() > 0)
         {
             for(int i = 0; i < search_results.size(); i++)
             {
                 cout << search_results[i] << endl;
             }
         }
         else
         {
             cout << "NO RESULTS(did you forget to prepend search string with a correct searchtype?)" << endl;
         }

         printSettingsStatus();
    }
    //
}

void Interface::searchComputers()
{
    //searching menu
    newMenu("COMPUTER SEARCH");
    cout << "'*' to view all\n"
            "Search syntax: \"searchtype searchquery\"\n"
            "Available search types:\n"
            "'name'   -- searches for names containing query\n"
            "'year'   -- searches for year when built\n"
            "'type'   -- searches for specific types\n"
            "'id'     -- searches for for computer with specified id\n"
            "Command syntax: \"command id\"\n"
            "'edit'   -- edits a computer via id number\n"
            "'delete' -- deletes a computer via id number\n"
            "Search results follow current settings\n";
    printSimpleLines();


    cin.ignore(1000, '\n');

    while(1)
    {
        cout << "Search query(empty to exit to main menu): ";
        char ch = ' ';
        string search_string = "";

        do
        {
            ch = cin.get();
            if(ch != '\n')
            {
                search_string += ch;
            }
        }while(ch != '\n');
    //

         if(search_string == "")
         {
            return;
         }

    //search results
         if(request.isCommand(QString::fromStdString(search_string)))
         {
             doCommand(QString::fromStdString(search_string), 'c');
             return;
         }

         QVector<Computer> search_results = request.searchComputers(QString::fromStdString(search_string));
         clearConsole();
         printLines();
         printMenuHead("SEARCH RESULTS");

         if(search_results.size() > 0)
         {
             for(int i = 0; i < search_results.size(); i++)
             {
                 cout << search_results[i] << endl;
             }
         }
         else
         {
             cout << "NO RESULTS(did you forget to prepend search string with a correct searchtype?)" << endl;
         }

         printSettingsStatus();
    }
}

void Interface::doCommand(QString command_string, char type)
{
    QString command = request.extractCommand(command_string);
    QString id = request.extractId(command_string);
    char ch = ' ';

    clearConsole();
    printLines();


    if(type == 'p') //PERSON
    {
        printMenuHead(command.toUpper().toStdString() + " PERSON");
        if(request.searchPersons("id " + id).isEmpty()) //needed to prevent crashes
        {
            setStatus("Person #" + id.toStdString() + " does not exist or is omitted!");
            return;
        }
        string name = request.searchPersons("id " + id).first().getName().toStdString();
        if(command == "edit")
        {
            cout << "Are you sure you want to edit " << name << "?(y/n): ";
            cin >> ch;
            if(ch == 'y' || ch == 'Y')
            {
                Person to_edit;
                cin >> to_edit;
                if(request.editPerson(to_edit, id))
                {
                    setStatus("\"" + name + "\" changed to \"" + to_edit.getName().toStdString() + "\"");
                }
                else
                {
                    setStatus("\"" + name + "\" was NOT changed!");
                }
            }
        }
        else if(command == "delete")
        {
            cout << "Are you sure you want to delete " << name << "?(y/n): ";
            cin >> ch;
            if(ch == 'y' || ch == 'Y')
            {
                if(request.deletePerson(id))
                {
                    setStatus("\"" + name + "\" deleted!");
                }
                else
                {
                    setStatus("\"" + name + "\" was NOT deleted!");
                }
            }
        }
    }
    else if(type == 'c') //COMPUTER
    {
        printMenuHead(command.toUpper().toStdString() + " COMPUTER");
        if(request.searchComputers("id " + id).isEmpty()) //needed to prevent crashes
        {
            setStatus("Computer #" + id.toStdString() + " does not exist!");
            return;
        }
        string name = request.searchComputers("id " + id).first().getName().toStdString();
        if(command == "edit")
        {
            cout << "Are you sure you want to edit " << name << "?(y/n): ";
            cin >> ch;
            if(ch == 'y' || ch == 'Y')
            {
                Computer to_edit;
                cin >> to_edit;
                if(request.editComputer(to_edit, id))
                {
                    setStatus("\"" + name + "\" changed to \"" + to_edit.getName().toStdString() + "\"");
                }
                else
                {
                    setStatus("\"" + name + "\" was NOT changed!");
                }
            }
        }
        else if(command == "delete")
        {
            cout << "Are you sure you want to delete " << name << "?(y/n): ";
            cin >> ch;
            if(ch == 'y' || ch == 'Y')
            {
                if(request.deleteComputer(id))
                {
                    setStatus("\"" + name + "\" deleted!");
                }
                else
                {
                    setStatus("\"" + name + "\" was NOT deleted!");
                }
            }
        }
    }
    cin.ignore(1, '\n');
}

void Interface::editPerson(QString pid)
{
    //TODO implement
}

void Interface::editComputer(QString cid)
{
    //TODO implement
}

void Interface::deletePerson(QString pid)
{
    //TODO implement
}

void Interface::deleteComputer(QString cid)
{
    //TODO implement
}

void Interface::settingsMain()
{
    cin.ignore(1, '\n');
    while(1)
    {
        newMenu("SETTINGS");

        char ch = ' ';


        cout << "(1) to change person ordering\n"
                "(2) to change computer ordering\n"
                "(3) to change gender view\n"
                "enter anything else to go to main menu\n";
        printLines();

        cout << "Choice: ";

        ch = cin.get();

        switch(ch)
        {
        case '1':
            settingsPersonOrdering();
            break;
        case '2':
            settingsComputerOrdering();
            break;
        case '3':
            settingsGenders();
        default:
            //go to main menu
            break;
        }

        request.updateSettings();
        return;
    }

}

void Interface::settingsPersonOrdering()
{
    newMenu("PERSON ORDERING");

    char ch = ' ';

    cout << "(1) to order by name in lexicographical order \n"
            "(2) to order by name in reverse lexicographical order\n"
            "(3) to order by date of birth \n"
            "(4) to order by date of birth in reverse order \n"
            "(5) to order by date of death \n"
            "(6) to order by date of death in reverse order \n"
            "(7) to go to main menu \n"
            "enter anything else to go back\n";
    printLines();

    cout << "Choice: ";
    cin.ignore(1, '\n');
    ch = cin.get();

    switch(ch)
    {
    case '1':
        request.setPersonOrdering(NAME);
        setSettingsStatus(); //update settings status
        break;
    case '2':
        request.setPersonOrdering(NAME_R);
        setSettingsStatus(); //update settings status
        break;
    case '3':
        request.setPersonOrdering(DOB);
        setSettingsStatus(); //update settings status
        break;
    case '4':
        request.setPersonOrdering(DOB_R);
        setSettingsStatus(); //update settings status
        break;
    case '5':
        request.setPersonOrdering(DOD);
        setSettingsStatus(); //update settings status
        break;
    case '6':
        request.setPersonOrdering(DOD_R);
        setSettingsStatus(); //update settings status
        break;
    case '7':
        return; //go to main menu
        break;
    default:
        //nothing here, defaults to go back
        break;
    }

    settingsMain();
}

void Interface::settingsComputerOrdering()
{
    newMenu("COMPUTER ORDERING");

    char ch = ' ';

    cout << "(1) to order by name in lexicographical order \n"
            "(2) to order by name in reverse lexicographical order\n"
            "(3) to order by year when built \n"
            "(4) to order by year when built in reverse order \n"
            "(5) to order by type \n"
            "(6) to order by type in reverse order \n"
            "(7) to go to main menu \n"
            "enter anything else to go back\n";
    printLines();

    cout << "Choice: ";
    cin.ignore(1, '\n');
    ch = cin.get();

    switch(ch)
    {
    case '1':
        request.setComputerOrdering(CNAME);
        setSettingsStatus(); //update settings status
        break;
    case '2':
        request.setComputerOrdering(CNAME_R);
        setSettingsStatus(); //update settings status
        break;
    case '3':
        request.setComputerOrdering(YEAR);
        setSettingsStatus(); //update settings status
        break;
    case '4':
        request.setComputerOrdering(YEAR_R);
        setSettingsStatus(); //update settings status
        break;
    case '5':
        request.setComputerOrdering(TYPE);
        setSettingsStatus(); //update settings status
        break;
    case '6':
        request.setComputerOrdering(TYPE_R);
        setSettingsStatus(); //update settings status
        break;
    case '7':
        return; //go to main menu
        break;
    default:
        //nothing here, defaults to go back
        break;
    }

    settingsMain();
}

void Interface::settingsGenders()
{
    newMenu("GENDER VIEW");

    char ch = ' ';

    cout << "(1) to only view male computer scientists \n"
            "(2) to only view female computer scientists \n"
            "(3) view both genders \n"
            "(4) to go to main menu \n"
            "enter anything else to go back\n";
    printLines();

    cout << "Choice: ";

    cin.ignore(1, '\n');
    ch = cin.get();

    switch(ch)
    {
    case '1':
        request.setGenderView(MALE);
        setSettingsStatus(); //update settings status
        break;
    case '2':
        request.setGenderView(FEMALE);
        setSettingsStatus(); //update settings status
        break;
    case '3':
        request.setGenderView(BOTH);
        setSettingsStatus(); //update settings status
        break;
    case '4':
        return; //go to main menu
        break;
    default:
        break;
    }

    settingsMain(); //after changing gender view settings go back to main settings menu
}

void Interface::about()
{
    clearConsole();
    printLines();
    printMenuHead("ABOUT");
    cout << "Verklegt Namsskeid - Skil 2 \t Reykjavik University - Fall 2015\n\n"
            "Created by:\n"
            "Hrafnkell Ivarsson\n"
            "Arnar Freyr Saevarsson\n"
            "Eirikur Hakon Fridriksson\n";
    printLines();
    cout << "Press enter to continue: ";
    waitForAnyKey();
}

//--helpers--
void Interface::clearConsole()
{
    //this function is ugly but it works for the purpose of this program
    for(int i = 0; i < 20; i++) //for smoother transition
    {
        cout << endl;
    }
    //std::system("clear"); //for unix based
    system("CLS"); //for windows

//NOTE: yeah yeah, I know, system() commands are really really bad
}

void Interface::printMainMenu()
{
    newMenu("MAIN MENU");

    cout << "(1) to add a computer scientist or a computer\n"
            "(2) to search for computer scientists or computers\n"
            "(3) to change settings\n"
            "(4) to exit\n"
            "(a) for information about this program\n";
    printLines();
    printStatus();

}

void Interface::setStatus(string newstatus)
{
    current_status = newstatus;
}

void Interface::setSettingsStatus()
{
    personordering current_person_ordering = request.getPersonOrdering();
    gendertype current_genderview = request.getGenderView();
    computerordering current_computer_ordering = request.getComputerOrdering();

    string new_settingsstatus = "Order by(P): ";

    switch (current_person_ordering)
    {
    case NAME:
        new_settingsstatus += "Name(lexicographical)";
        break;
    case NAME_R:
        new_settingsstatus += "Name(reverse lexicographical)";
        break;
    case DOB:
        new_settingsstatus += "Date of Birth";
        break;
    case DOB_R:
        new_settingsstatus += "Date of Birth(reversed)";
        break;
    case DOD:
        new_settingsstatus += "Date of Death";
        break;
    case DOD_R:
        new_settingsstatus += "Date of Death(reversed)";
        break;
    default:
        new_settingsstatus += "This is awkward"; //this should never happen anyway
        break;
    }

    new_settingsstatus += "   #   View genders: ";

    switch(current_genderview)
    {
    case MALE:
        new_settingsstatus += "Males only";
        break;
    case FEMALE:
        new_settingsstatus += "Females only";
        break;
    case BOTH:
        new_settingsstatus += "Both";
        break;
    default:
        new_settingsstatus += "Does gender really matter?"; //this should never happen anyway
    }

    new_settingsstatus += "\nOrder by(C): ";

    switch(current_computer_ordering)
    {
    case CNAME:
        new_settingsstatus += "Name(lexicographical)";
        break;
    case CNAME_R:
        new_settingsstatus += "Name(reverse lexicographical)";
        break;
    case YEAR:
        new_settingsstatus += "Year";
        break;
    case YEAR_R:
        new_settingsstatus += "Year(reversed)";
        break;
    case TYPE:
        new_settingsstatus += "Type(lexicographical)";
        break;
    case TYPE_R:
        new_settingsstatus += "Type(reverse lexicographical)";
        break;
    }

    current_settings = new_settingsstatus;
    setStatus("Settings updated!");
}

void Interface::printStatus()
{
    if(current_status != "")
    {
        cout << current_status << endl;
        printLines();
    }
}

void Interface::printSettingsStatus()
{
    printLines();
    printMenuHead("CURRENT SETTINGS");
    cout << current_settings << endl;
    printLines();
}

void Interface::printMenuHead(string menuname)
{
    cout << "\t\t\t";
    for(unsigned int i = 0; i < 70/menuname.size(); i++) //this makes the text appear centered(kind of)
    {
        cout << ' ';
    }
    cout << menuname << endl;
    printSimpleLines();

}

void Interface::printLines()
{
    cout << "========================================================================\n";
}

void Interface::printSimpleLines()
{
    cout << "------------------------------------------------------------------------\n";
}

void Interface::newMenu(string menuname)
{
    clearConsole();
    printSettingsStatus();
    cout << endl;
    printLines();
    printMenuHead(menuname);
}

void Interface::waitForAnyKey()
{
    char ch = ' ';
    cin.clear();
    cin.ignore(1000, '\n');
    while(ch != '\n') //ugly but works
    {
        ch = cin.get();
    }
}
