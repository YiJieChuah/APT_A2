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
    int mainMenu();

    string selectPlayer1();
    string selectPlayer2();
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
int Menu::mainMenu()
{
    int selection;
    string strSelection;
    cout << "Menu" << endl;
    cout << "----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show student information)" << endl;
    cout << "4. Quit" << endl;

    bool inputValid = false;
    while (!inputValid)
    {
        cout << "\n>";
        cin >> strSelection;
        try
        {
            selection = stoi(strSelection);
            inputValid = true;
        }
        catch (...)
        {
            cout << "Invalid Input";
        }
    }
    return selection;
}

/**
 * @return a player one's username.
 */
string Menu::selectPlayer1()
{
    string player1;
    cout << "Starting a New Game" << endl;
    cout << "\nEnter a name for player 1 (uppercase characters only)" << endl;
    cout << ">";
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
    cout << ">";
    cin >> player2;

    cout << "\nLet's Play!\n"
         << endl;
    return player2;
}