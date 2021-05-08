#include <iostream>
#include <string>

#include "GameView.h"

/**
 * Present the user with the iterface. Also process user input here?
 */
GameView::GameView(GameModel* gameModelPtr) {
    this->gameModelPtr = gameModelPtr;
}
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

    int selection = getValidSelection();
    processSelection(selection);
}

int GameView::getValidSelection() {
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

    return selection;
};

void GameView::processSelection(int input) {

    std::string player1;
    std::string player2;
    std::string fileDirectory;

    std::cout << "\n> ";
    std::cin >> input;

    if (input == 1)
    {
        startNewGame();
    }
    else if (input == 2)
    {
        fileDirectory = createFileDir();
        // FOR TESTING ONLY!
        std::cout << fileDirectory << std::endl;
    }
    else if (input == 3)
    {
        printCredits();
        //restart
        init();
    }
    else if (input == 4)
    {
        // MAJOR FUNCTIONALITY MISSING! NEED TO CLEAR MEMORY HERE!!!!
        std::cout << "\nGoodbye" << std::endl;
    }
}

void GameView::startNewGame() {
    std::cout << "Starting a New Game" << std::endl;

    //Setup 2 players
    newPlayer();
    newPlayer();
}

/**
 * @return a player's username.
 */
void GameView::newPlayer()
{
    std::string playerName;
    std::cout << "\nEnter a name for player"
        << gameModelPtr->getNumPlayers() + 1
        << "(uppercase characters only)"
        << std::endl;
    std::cout << "> ";

    //TODO: validate player name
    std::cin >> playerName;
    gameModelPtr->addPlayerToGame(playerName);

    std::cout << "\nLet's Play!\n"
        << std::endl;
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