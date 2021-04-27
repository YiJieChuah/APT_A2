#include <iostream>
#include <string>
#include <fstream>

#include "Menu.h"

Menu::Menu()
{
    std::cout << "Welcome to Qwirkle" << std::endl;
    std::cout << "-------------------" << std::endl;
}

/**
 * @return the users choice.
 */
void Menu::mainMenu()
{
    int selection;
    // Presenting the menu.
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;

    bool inputValid = false;
    do
    {
        std::cout << "\n> ";
        std::cin >> selection;

        try
        {
            if (!std::cin.good()) {
                std::cin.clear();
                std::cin.ignore();
                throw std::domain_error("Error: Not a number");
            }
            if (selection <= 0 || selection > 4)
            {
                throw std::out_of_range("Error: No such option");
            }
            inputValid = true;
        }
        catch (std::out_of_range& e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (std::domain_error& e)
        {
            std::cout << e.what() << std::endl;
        }
    } while (!inputValid || !std::cin.good());
    // cin will return a failbit if selection was not an int

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
        std::string filePath;
        std::cout << "\nEnter the filename from which to load a game" << std::endl;
        std::cout << "> ";
        std::cin >> filePath;
        if (loadFile(filePath)) {
            std::cout << "Qwirkle game successfully loaded" << std::endl;
            //TODO: Replace when gameplay is implemented
            std::cout << "<Gameplay continues here>" << std::endl;
        }
    }
    else if (selection == 3)
    {
        printCredits();
        mainMenu();
    }
    else if (selection == 4)
    {
        // TODO: clear memory
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

bool Menu::loadFile(std::string filePath) {
    bool fileIsValid = false;
    std::ifstream myFile;
    std::string fileContents = "";
    myFile.open(filePath, std::ios::in);

    if (!myFile) {
        std::cout << "Error: No such file exists" << std::endl;
    }
    else {
        fileIsValid = true;
        std::string line;
        int lineIdx = 0;
        while (!getline(myFile, line).eof()) {
            //TODO: check if a line is valid
            ++lineIdx;
            // fileLineIsValid(int lineIdx);
            fileContents += line + '\n';
        }
    }
    std::cout << fileContents << std::endl;
    return fileIsValid;
}


// std::string Menu::createFileDir()
// {
//     std::cout << "Enter a filename from which load a game" << std::endl;
//     std::cout << "> ";
//     std::string fileDirectory = "saves/";
//     std::string input;
//     std::cin >> input;
//     fileDirectory += input;
//     return fileDirectory;
// }

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