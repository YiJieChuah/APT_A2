#include <iostream>
#include <string>

using namespace std;

/**
 * Present the user with the iterface. Also process user input here?
 */
class Menu
{

public:
    Menu();
    ~Menu();
    void mainMenu();

    string selectPlayer1();
    string selectPlayer2();
    string createFileDir();
    void printCredits();
};

Menu::Menu()
{
}

Menu::~Menu()
{
}

/**
 * @return the users choice.
 */
void Menu::mainMenu()
{
    int selection;
    string strSelection;
    // Presenting the menu.
    cout << "Menu" << endl;
    cout << "----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show student information)" << endl;
    cout << "4. Quit" << endl;

    // Getting the users choice.
    bool inputValid = false;
    while (!inputValid)
    {
        cout << "\n> ";
        cin >> strSelection;
        if (strSelection == "q")
        {
            // EXIT THE GAME.
        }
        try
        {
            selection = stoi(strSelection);
            if (selection > 4)
            {
                throw 20;
            }
            inputValid = true;
        }
        catch (...)
        {
            cout << "Invalid Input";
        }
    }

    // Performing operations based on the users choice.
    string player1;
    string player2;
    string fileDirectory;

    if (selection == 1)
    {
        player1 = selectPlayer1();
        player2 = selectPlayer2();

        // FOR TESTING ONLY!
        cout << player1 << endl;
        cout << player2 << endl;
    }
    else if (selection == 2)
    {
        fileDirectory = createFileDir();

        // FOR TESTING ONLY!
        cout << fileDirectory << endl;
    }
    else if (selection == 3)
    {
        printCredits();
        mainMenu();
    }
    else if (selection == 4)
    {
        // MAJOR FUNCTIONALITY MISSING! NEED TO CLEAR MEMORY HERE!!!!
        cout << "\nGoodbye" << endl;
    }
}

/**
 * @return a player one's username.
 */
string Menu::selectPlayer1()
{
    string player1;
    cout << "Starting a New Game" << endl;
    cout << "\nEnter a name for player 1 (uppercase characters only)" << endl;
    cout << "> ";
    cin >> player1;

    // ADD FUNCTIONALITY: EITHER check for upper case or just make the usernames uppercase ourselves.
    return player1;
}

/**
 * @return a player two's username.
 */
string Menu::selectPlayer2()
{
    string player2;
    cout << "\nEnter a name for player 2 (uppercase characters only)" << endl;
    cout << "> ";
    cin >> player2;

    cout << "\nLet's Play!\n"
         << endl;
    return player2;
}

/** 
 * Difficult to check if file exists with current config. Maybe return
 * actual file instead?
 */
string Menu::createFileDir()
{
    cout << "Enter a filename from which load a game" << endl;
    cout << "> ";
    string fileDirectory = "saves/";
    string input;
    cin >> input;
    fileDirectory += input;
    return fileDirectory;
}

void Menu::printCredits()
{

    string names[4] = {"Seth Danford", "Simon Dean", "Jeremy West", "Yi Jie Chuah"};
    string studentIDs[4] = {"s3845408", "s3599190", "s3869546", "s3847905"};
    string emails[4] = {"s3845408@student.rmit.edu.au", "s3599190@student.rmit.edu.au", "s3869546@student.rmit.edu.au", "s3847905@student.rmit.edu.au"};

    cout << "-----------------------------------" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << "Name: " + names[i] << endl;
        cout << "Student ID: " + studentIDs[i] << endl;
        if (i != 3)
        {
            cout << "Email: " + emails[i] + "\n"
                 << endl;
        }
        else
        {
            cout << "Email: " + emails[i] << endl;
        }
    }
    cout << "-----------------------------------\n"
         << endl;
}