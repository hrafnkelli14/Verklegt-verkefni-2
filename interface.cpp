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

    while(ch != '4') //there might be a better way to achieve a menu
    {
        printMainMenu();
        setStatus(""); //reset status message

        std::cout << "Choice: ";
        std::cin >> ch;
        switch(ch)
        {
        case '1':
            add();
            break;
        case '2': //a real output function has to be implemented that accounts for ordering & gender settings
            request.outputAll(); //should NOT be done this way.. only for testing purposes
            cin >> ch; //since there is no menu for output yet we have to use cin so the console doesn't clear
            break;
        case '3':
            settingsMain();
            break;
        default:
            break;
        }


    }
}

//========PRIVATE FUNCTIONS==========
void Interface::add()
{  
    clearConsole();
    printLines();
    printMenuHead("ADD PERSON");
    Person temp;
    cin >> temp;

    request.addPerson(temp);
    setStatus("\"" + temp.getName().toStdString() + "\" added to list!");
}

//--menus--
void Interface::settingsMain()
{
    newMenu("SETTINGS");

    char ch = ' ';


    std::cout << "press (1) to change ordering settings \n"
                 "press (2) to change gender view settings\n"
                 "press anything else to go to main menu\n";
    printLines();

    std::cout << "Choice: ";
    std::cin >> ch;

    switch(ch)
    {
    case '1':
        settingsOrdering();
        break;
    case '2':
        settingsGenders();
        break;
    default:
        //go to main menu
        break;
    }

    request.updateSettings();

}

void Interface::settingsOrdering()
{
    newMenu("ORDERING SETTINGS");

    char ch = ' ';

    std::cout << "press (1) to order list by names in alphabetical order \n"
                 "press (2) to order list by names in reverse alphabetical order\n"
                 "press (3) to order list by date of birth \n"
                 "press (4) to order list by date of birth in reverse order \n"
                 "press (5) to order list by date of death (those who are alive will be excluded)\n"
                 "press (6) to order list by date of death in reverse order \n"
                 "press (7) to go to main menu \n"
                 "press anything else to go back\n";
    printLines();

    std::cout << "Choice: ";
    std::cin >> ch;

    switch(ch)
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
    case '4':
        request.setOrdering(DOB_R);
        break;
    case '5':
        request.setOrdering(DOD);
        break;
    case '6':
        request.setOrdering(DOD_R);
        break;
    case '7':
        return; //go to main menu
        break;
    default:
        //nothing here, defaults to go back
        break;
    }

    setSettingsStatus(); //update settings status
    settingsMain();
}

void Interface::settingsGenders()
{
    newMenu("GENDER VIEW SETTINGS");

    char ch = ' ';

    std::cout << "press (1) to only view male computer scientists \n"
                 "press (2) to only view female computer scientists \n"
                 "press (3) view both genders \n"
                 "press (4) to go to main menu \n"
                 "press anything else to go back\n";
    printLines();

    std::cout << "Choice: ";
    std::cin >> ch;

    switch(ch)
    {
    case '1':
        request.setGenderView(MALE);
        break;
    case '2':
        request.setGenderView(FEMALE);
        break;
    case '3':
        request.setGenderView(BOTH);
        break;
    case '4':
        return; //go to main menu
        break;
    default:
        break;
    }

    setSettingsStatus(); //update settings status
    settingsMain(); //after changing gender view settings go back to main settings menu
}


//--helpers--
void Interface::clearConsole()
{
    //this function is ugly but it works for the purpose of this program
    for(int i = 0; i < 20; i++) //for smoother transition
    {
        std::cout << endl;
    }
    //std::system("clear"); //for unix based
    std::system("CLS"); //for windows

//NOTE: yeah yeah, I know, system() commands are really really bad
}

void Interface::printMainMenu()
{
    newMenu("MAIN MENU");

    std::cout << "press (1) to add a person to the list \n"
                 "press (2) to view list \n"
                 "press (3) for list view settings \n"
                 "press (4) to exit \n";
    printLines();
    printStatus();

}

void Interface::setStatus(string newstatus)
{
    current_status = newstatus;
}

void Interface::setSettingsStatus()
{
    ordering current_ordering = request.getOrdering();
    gendertype current_genderview = request.getGenderView();

    string new_settingsstatus = "Order by: ";

    switch (current_ordering)
    {
    case NAME:
        new_settingsstatus += "Name(alphabetical)";
        break;
    case NAME_R:
        new_settingsstatus += "Name(reverse alphabetical)";
        break;
    case DOB:
        new_settingsstatus += "Date of Birth";
        break;
    case DOB_R:
        new_settingsstatus += "Date of Birth(reversed)";
        break;
    case DOD:
        new_settingsstatus += "Date of Death(alive excluded)";
        break;
    case DOD_R:
        new_settingsstatus += "Date of Death(reversed, alive excluded)";
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

    current_settings = new_settingsstatus;
    setStatus("Settings updated!");
}

void Interface::printStatus()
{
    if(current_status != "")
    {
        std::cout << current_status << endl;
        printLines();
    }
}

void Interface::printSettingsStatus()
{
    printLines();
    printMenuHead("CURRENT SETTINGS");
    std::cout << current_settings << endl;
    printLines();
}

void Interface::printMenuHead(string menuname)
{
    std::cout << "\t\t\t";
    for(unsigned int i = 0; i < 70/menuname.size(); i++) //this makes the text appear centered(kind of)
    {
        std::cout << ' ';
    }
    std::cout << menuname << endl <<
                 "------------------------------------------------------------------------\n";

}

void Interface::printLines()
{
    std::cout << "========================================================================\n";
}

void Interface::newMenu(string menuname)
{
    clearConsole();
    printSettingsStatus();
    std::cout << endl;
    printLines();
    printMenuHead(menuname);
}
