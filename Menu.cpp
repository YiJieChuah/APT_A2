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

    string *presentOption1();
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
 * @return a pointer to a string array with the two users.
 */
string *Menu::presentOption1()
{
    string stuff[2] = {"miao", "cow"};
    return stuff;
}