#include <iostream>
#include <string>

/**
 * Present the user with the iterface. Also process user input here?
 */
class Menu
{

public:
    Menu();
    ~Menu();
    void mainMenu();

    std::string selectPlayer1();
    std::string selectPlayer2();
    std::string createFileDir();
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
    std::string strSelection;
    // Presenting the menu.
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;

    // Getting the users choice.
    bool inputValid = false;
    while (!inputValid)
    {
        std::cout << "\n> ";
        std::cin >> strSelection;
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
            std::cout << "Invalid Input";
        }
    }

    // Performing operations based on the users choice.
    std::string player1;
    std::string player2;
    std::string fileDirectory;

    if (selection == 1)
    {
        player1 = selectPlayer1();
        player2 = selectPlayer2();

        // FOR TESTING ONLY!
        std::cout << player1 << std::endl;
        std::cout << player2 << std::endl;
    }
    else if (selection == 2)
    {
        fileDirectory = createFileDir();

        // FOR TESTING ONLY!
        std::cout << fileDirectory << std::endl;
    }
    else if (selection == 3)
    {
        printCredits();
        mainMenu();
    }
    else if (selection == 4)
    {
        // MAJOR FUNCTIONALITY MISSING! NEED TO CLEAR MEMORY HERE!!!!
        std::cout << "\nGoodbye" << std::endl;
    }
}

/**
 * @return a player one's username.
 */
std::string Menu::selectPlayer1()
{
    std::string player1;
    std::cout << "Starting a New Game" << std::endl;
    std::cout << "\nEnter a name for player 1 (uppercase characters only)" << std::endl;
    std::cout << "> ";
    std::cin >> player1;

    // ADD FUNCTIONALITY: EITHER check for upper case or just make the usernames uppercase ourselves.
    return player1;
}

/**
 * @return a player two's username.
 */
std::string Menu::selectPlayer2()
{
    std::string player2;
    std::cout << "\nEnter a name for player 2 (uppercase characters only)" << std::endl;
    std::cout << "> ";
    std::cin >> player2;

    std::cout << "\nLet's Play!\n"
        << std::endl;
    return player2;
}

/**
 * Difficult to check if file exists with current config. Maybe return
 * actual file instead?
 */
std::string Menu::createFileDir()
{
    std::cout << "Enter a filename from which load a game" << std::endl;
    std::cout << "> ";
    std::string fileDirectory = "saves/";
    std::string input;
    std::cin >> input;
    fileDirectory += input;
    return fileDirectory;
}

void Menu::printCredits()
{

    std::string names[4] = { "Seth Danford", "Simon Dean", "Jeremy West", "Yi Jie Chuah" };
    std::string studentIDs[4] = { "s3845408", "s3599190", "s3869546", "s3847905" };
    std::string emails[4] = { "s3845408@student.rmit.edu.au", "s3599190@student.rmit.edu.au", "s3869546@student.rmit.edu.au", "s3847905@student.rmit.edu.au" };

    std::cout << "-----------------------------------" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << "Name: " + names[i] << std::endl;
        std::cout << "Student ID: " + studentIDs[i] << std::endl;
        if (i != 3)
        {
            std::cout << "Email: " + emails[i] + "\n"
                << std::endl;
        }
        else
        {
            std::cout << "Email: " + emails[i] << std::endl;
        }
    }
    std::cout << "-----------------------------------\n"
        << std::endl;
}