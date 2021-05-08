#include <iostream>
#include <string>

#include "GameView.h"

/**
 * Present the user with the iterface. Also process user input here?
 */
GameView::GameView() {}
GameView::~GameView() {}

/**
 * @return the users choice.
 */
void GameView::init()
{

    // Presenting the menu.
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;

    processInput();
}

void GameView::processInput() {
    int selection;
    std::string player1;
    std::string player2;
    std::string fileDirectory;

    std::cout << "\n> ";
    std::cin >> selection;

    if (selection == 1)
    {
        startNewGame();
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
        init();
    }
    else if (selection == 4)
    {
        // MAJOR FUNCTIONALITY MISSING! NEED TO CLEAR MEMORY HERE!!!!
        std::cout << "\nGoodbye" << std::endl;
    }
}

int GameView::getValidInput(int input) {
    bool inputValid = false;
    int selection;
    do
    {
        std::cout << "\n> ";
        std::cin >> selection;

        try
        {
            if (!std::cin.good()) {
                //Resets cin flags for next input attempt
                std::cin.clear();
                std::cin.ignore();
                throw std::domain_error("Invalid Input");
            }
            if (selection <= 0 || selection > 4)
            {
                throw std::out_of_range("Invalid Input");
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

    return input;
};

void GameView::startNewGame() {
    std::cout << "Starting a New Game" << std::endl;

    //Setup players
    newPlayer();
}

/**
 * @return a player two's username.
 */
std::string GameView::newPlayer()
{
    std::string player;
    std::cout << "\nEnter a name for player 2 (uppercase characters only)"
        << std::endl;
    std::cout << "> ";
    std::cin >> player;

    std::cout << "\nLet's Play!\n"
        << std::endl;
    return player;
}

/**
 * Difficult to check if file exists with current config. Maybe return
 * actual file instead?
 */
std::string GameView::createFileDir()
{
    std::cout << "Enter a filename from which load a game" << std::endl;
    std::cout << "> ";
    std::string fileDirectory = "saves/";
    std::string input;
    std::cin >> input;
    fileDirectory += input;
    return fileDirectory;
}

void GameView::printCredits()
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