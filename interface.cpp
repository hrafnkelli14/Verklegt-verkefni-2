#include "interface.h"

//========CONSTRUCTORS==========
Interface::Interface()
{ 
    setSettingsStatus();
    current_status = "";
    r_pid = "";
    r_cid = "";
    second_view = false;

    switch(is_windows)
    {
    case 0: //is not windows.. assumes unix terminal
        clear_command = "clear";
        break;
    case 1: //is windows
        clear_command = "CLS";
        break;
    }
}

Interface::~Interface()
{
     //Intentionally left empty
}

//========PUBLIC FUNCTIONS==========
void Interface::start()
{
    char ch = ' ';

    while(ch != 'q')
    {
        checkRelation();

        printMainMenu();
        setStatus(""); //reset status message

        cout << "Choice: ";
        cin >> ch;
        switch(ch)
        {
        case 'a':
            about();
            break;
        case 's':
            enterTheMatrixQuestion();
            break;
        case '1':
            addCompOrPerson();
            break;
        case '2':
            viewCompsOrPersons();
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

void Interface::viewCompsOrPersons()
{
    newMenu("VIEW");

    char ch = ' ';

    cout << "(1) utility menu for computer scientists\n"
            "(2) utility menu for computers\n"
            "enter anything else to go to main menu \n";
    printLines();

    cout << "Choice: ";
    cin.ignore(1, '\n');
    ch = cin.get();

    switch(ch)
    {
    case '1':
        viewPersons();
        break;
    case '2':
        viewComputers();
        break;
    default:
        break;
    }


}

void Interface::viewPersons()
{
    newMenu("PERSON UTILITY");
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
            "'addr'   -- pick a person to add relations to via id\n"
            "            and then pick the related computer with 'addr id'\n"
            "'viewr'  -- view relations via id number\n"
            "Search results follow current settings\n";
    printSimpleLines();
    printStatus();

    if(!second_view)
    {
        cin.ignore(1000, '\n');
    }
    else
    {
        second_view = false;
    }

    while(1)
    {

        cout << "Query(empty to exit to main menu): ";
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

         if(search_string == "")
         {
            return;
         }

         if(request.isCommand(QString::fromStdString(search_string)))
         {
             doCommand(QString::fromStdString(search_string), 'p');
             return;
         }
         else
         {
             searchResultsPersons(search_string);
         }
    }
}

void Interface::viewComputers()
{
    newMenu("COMPUTER UTILITY");
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
            "'addr'   -- pick a computer to add relations to via id\n"
            "            and then pick the related person with 'addr id'\n"
            "'viewr'  -- view relations via id number\n"
            "Search results follow current settings\n";
    printSimpleLines();
    printStatus();

    if(!second_view)
    {
        cin.ignore(1000, '\n');
    }
    else
    {
        second_view = false;
    }

    while(1)
    {

        cout << "Query(empty to exit to main menu): ";
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

        if(search_string == "")
        {
           return;
        }

        if(request.isCommand(QString::fromStdString(search_string)))
        {
            doCommand(QString::fromStdString(search_string), 'c');
            return;
        }
        else
        {
            searchResultsComputers(search_string);
        }
    }
}

void Interface::searchResultsPersons(string search_string)
{
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
    printStatus();
}

void Interface::searchResultsComputers(string search_string)
{
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
    printStatus();
}

void Interface::viewPersonXComputers(QString id)
{
    string command_string;
    QString command;
    QString d_id;
    clearConsole();
    printLines();
    printMenuHead("PERSON RELATIONS");

    cout << request.outputPersonXComputers(id);

    printSimpleLines();
    cout << "Type 'delete id' to delete relation or leave empty to return" << endl;
    printSimpleLines();
    cout << "Query: ";

    getline(cin, command_string);
    command = request.extractCommand(QString::fromStdString(command_string));
    if(command == "delete")
    {
        d_id = request.extractId(QString::fromStdString(command_string));
        if(request.deleteRelation(d_id, id))
        {
            string p_name = request.getPerson(d_id).getName().toStdString();
            string c_name = request.getComputer(id).getName().toStdString();
            setStatus("Relation of '" + p_name + "' to '" + c_name + "' deleted!");
        }
        else
        {
            setStatus("Unable to delete relation");
        }
    }
}

void Interface::viewComputerXPersons(QString id)
{
    string command_string;
    QString command;
    QString d_id;
    clearConsole();
    printLines();
    printMenuHead("COMPUTER RELATIONS");

    cout << request.outputComputerXPersons(id);

    printSimpleLines();
    cout << "Type 'delete id' to delete relation or leave empty to return" << endl;
    printSimpleLines();
    cout << "Query: ";

    getline(cin, command_string);
    command = request.extractCommand(QString::fromStdString(command_string));
    if(command == "delete")
    {
        d_id = request.extractId(QString::fromStdString(command_string));    
        if(request.deleteRelation(id, d_id))
        {
            string c_name = request.getComputer(id).getName().toStdString();
            string p_name = request.getPerson(d_id).getName().toStdString();
            setStatus("Relation of '" + c_name + "' to '" + p_name + "' deleted!");
        }
        else
        {
            setStatus("Unable to delete relation");
        }
    }
}

void Interface::doCommand(QString command_string, char type)
{
    QString command = request.extractCommand(command_string);
    QString id = request.extractId(command_string);

    clearConsole();
    printLines();


    if(type == 'p') //PERSON
    {
        if(request.getPerson(id).getId().isEmpty()) //needed to prevent crashes
        {
            setStatus("Person #" + id.toStdString() + " does not exist or is omitted!");
            return;
        }

        printMenuHead(command.toUpper().toStdString() + " PERSON");

        if(command == "edit")
        {
            editPerson(id);
        }
        else if(command == "delete")
        {
            deletePerson(id);
        }
        else if(command == "addr")
        {
            addPersonRelation(id);
        }
        else if(command == "viewr")
        {
            viewPersonXComputers(id);
        }
    }
    else if(type == 'c') //COMPUTER
    {
        if(request.getComputer(id).getId().isEmpty()) //needed to prevent crashes
        {
            setStatus("Computer #" + id.toStdString() + " does not exist!");
            return;
        }

        printMenuHead(command.toUpper().toStdString() + " COMPUTER");

        if(command == "edit")
        {
            editComputer(id);
        }
        else if(command == "delete")
        {
            deleteComputer(id);
        }
        else if(command == "addr")
        {
            addComputerRelation(id);
        }
        else if(command == "viewr")
        {
            viewComputerXPersons(id);
        }
    }
}

void Interface::editPerson(QString id)
{
    char ch = ' ';
    string name = request.getPerson(id).getName().toStdString();
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

void Interface::editComputer(QString id)
{
    char ch = ' ';
    string name = request.getComputer(id).getName().toStdString();
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

void Interface::deletePerson(QString id)
{
    char ch = ' ';
    string name = request.getPerson(id).getName().toStdString();
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

void Interface::deleteComputer(QString id)
{
    char ch = ' ';
    string name = request.getComputer(id).getName().toStdString();
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

void Interface::addPersonRelation(QString id)
{
    string p_name = request.getPerson(id).getName().toStdString();
    r_pid = id;
    if(r_cid.isEmpty())
    {
        second_view = true;
        setStatus("Adding relation to '" + p_name + "', type addr and choose id for computer." );
        viewComputers();
    }
    else
    {

        string c_name = request.getComputer(r_cid).getName().toStdString();
        if(request.addComputerXPerson(r_cid, r_pid))
        {
            setStatus("Relation between '" + p_name + "' and '" + c_name + "' added!");
        }
        else
        {
            setStatus("Unable to add relation!");
        }
        r_cid = "";
        r_pid = "";
    }
}

void Interface::addComputerRelation(QString id)
{
    string c_name = request.getComputer(id).getName().toStdString();
    r_cid = id;
    if(r_pid.isEmpty())
    {
        second_view = true;
        setStatus("Adding relation to '" + c_name + "', type addr and choose id for person." );
        viewPersons();
    }
    else
    {
        string p_name = request.getPerson(r_pid).getName().toStdString();
        if(request.addComputerXPerson(r_cid, r_pid))
        {
            setStatus("Relation between '" + c_name + "' and '" + p_name + "' added!");
        }
        else
        {
             setStatus("Unable to add relation!");
        }
        r_cid = "";
        r_pid = "";
    }
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
            "(7) to order by ID\n"
            "(8) to order by ID in reverse order\n"
            "(9) to go to main menu \n"
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
        request.setPersonOrdering(pID);
        setSettingsStatus();
        break;
    case '8':
        request.setPersonOrdering(pID_R);
        setSettingsStatus();
        break;
    case '9':
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
            "(7) to order by ID\n"
            "(8) to order by ID in reverse order\n"
            "(9) to go to main menu \n"
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
        request.setComputerOrdering(cID);
        setSettingsStatus();
        break;
    case '8':
        request.setComputerOrdering(cID_R);
        setSettingsStatus();
        break;
    case '9':
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

    system(clear_command.c_str());
//NOTE: yeah yeah, I know, system() commands are really really bad
}

void Interface::printMainMenu()
{
    newMenu("MAIN MENU");

    cout << "(1) to add a computer scientist or a computer\n"
            "(2) for utility menus\n"
            "(3) to change settings\n"
            "(q) to exit\n"
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
    case pID:
        new_settingsstatus += "ID";
        break;
    case pID_R:
        new_settingsstatus += "ID (reversed)";
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
    case cID:
        new_settingsstatus += "ID";
        break;
    case cID_R:
        new_settingsstatus += "ID (reverse)";
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

void Interface::checkRelation()
{
    if(!r_pid.isEmpty() && r_cid.isEmpty())
    {
        r_pid = "";
        setStatus("");
    }
    else if(!r_cid.isEmpty() && r_pid.isEmpty())
    {
        r_cid = "";
        setStatus("");
    }
}

void Interface::enterTheMatrixQuestion()
{

    char ch = ' ';

    clearConsole();
    printLines();
    printMenuHead("I AM MORPHEUS");
    cout << "(1) Take the blue pill, the story ends\n"
            "(2) take the red pill, you stay in wonderland,\n"
            "    and I show you how deep the rabbit hole goes \n"

            "Your choice: ";
    cin.ignore(1, '\n');
    ch = cin.get();

    switch(ch)
    {
    case '1':
        return;
        break;
    case '2':
        enterTheMatrix();
        break;
     }
}

char Interface::mModulus(int i, int i_mod)
{
    int iq = (i/i_mod);
    return i - (iq*i_mod);

}

int Interface::getChar(int i_generator, char c_base, int i_range)
{
    return (c_base + mModulus(i_generator, i_range));

}

void Interface::enterTheMatrix()
{
        clearConsole();
    // Color code
        HANDLE  h_console;
        h_console = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h_console, 2);

        char ca_row[80];
        int j = 7;
        int k = 2;
        int l = 5;
        int m = 1;
        while (true)
        {
            int i = 0;
            // Output a random row of characters
            while (i < 80) {
                if (ca_row[i] != ' ') {
                    ca_row[i] = getChar(j + i*i, 33, 30);
                    if (((i*i + k) % 71) == 0) {
                        SetConsoleTextAttribute(h_console,  7);
                    } else {
                        SetConsoleTextAttribute(h_console,  2);
                    }
                }
                std::cout << ca_row[i];
                ++i;
                SetConsoleTextAttribute(h_console,  2);
            }
            j = (j + 31);
            k = (k + 17);
            l = (l + 47);
            m = (m + 67);
            ca_row[mModulus(j, 80)] = '-';
            ca_row[mModulus(k, 80)] = ' ';
            ca_row[mModulus(l, 80)] = '-';
            ca_row[mModulus(m, 80)] = ' ';
            // Delay
            Sleep(10);
        }
}
