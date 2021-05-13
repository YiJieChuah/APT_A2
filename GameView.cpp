#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

#include "GameView.h"
#include "Tile.h"
#include "SaveLoad.h"

/**
 * Present the user with the iterface. Also process user input here?
 */
GameView::GameView(GameModel* gameModelPtr)
{
    this->gameModelPtr = gameModelPtr;
    gameOver = false;
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

    int selection = getValidMenuSelection();
    processMenuSelection(selection);
}

int GameView::getValidMenuSelection()
{
    bool inputValid = false;
    int selection;
    do
    {
        std::cout << "\n> ";
        std::cin >> selection;

        try
        {
            if (!std::cin.good())
            {
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

void GameView::processMenuSelection(int input)
{
    std::string fileDirectory;

    if (input == 1)
    {
        startNewGame();
    }
    else if (input == 2)
    {
        SaveLoad* loader = new SaveLoad(gameModelPtr);
        do {
            fileDirectory = createFileDir();
        } while (!loader->load(fileDirectory));

        startGame();
        delete loader;
    }
    else if (input == 3)
    {
        printCredits();
        //restart
        init();
    }
    else if (input == 4)
    {
        quit();
    }
}

void GameView::startGame()
{
    bool firstIteration = true;
    std::cout << "\nQwirkle game successfully loaded" << std::endl;

    std::vector<Player*> players = gameModelPtr->getPlayers();
    while (gameModelPtr->getTileBag()->numTilesLeft() > 0 && !gameOver)
    {
        for (Player* player : players)
        {
            if (!gameOver) {
                if (!firstIteration)
                {
                    gameModelPtr->setCurrentPlayer(player->getName());
                    firstIteration = false;
                }
                playerTurn(player);
            }
        }
    }
}

void GameView::startNewGame()
{
    std::cout << "Starting a New Game" << std::endl;

    //Setup 2 players
    newPlayer();
    newPlayer();

    std::cout << "\nLet's Play!\n"
        << std::endl;

    std::vector<Player*> players = gameModelPtr->getPlayers();

    // For when we take input for the first iteration later
    std::cin.ignore();
    while (gameModelPtr->getTileBag()->numTilesLeft() > 0 && !gameOver)
    {
        for (Player* player : players)
        {
            if (!gameOver && player->getName() == gameModelPtr->getCurrentPlayerName()) {
                playerTurn(player);
            }
        }
    }
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

    bool nameIsValid = false;
    do
    {
        std::cout << "\n> ";
        std::cin >> playerName;
        nameIsValid = validatePlayerName(playerName);
        if (!nameIsValid)
        {
            std::cerr << "Invalid Input" << std::endl;
        }
    } while (!nameIsValid);
    gameModelPtr->addPlayerToGame(playerName);
}

bool GameView::validatePlayerName(std::string name)
{
    bool isValid = true;
    std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (unsigned int i = 0; i < name.size(); i++)
    {
        if (allowedChars.find(name[i]) == std::string::npos)
        {
            isValid = false;
        }
    }
    return isValid;
}

void GameView::playerTurn(Player* player)
{
    gameModelPtr->setCurrentPlayer(player->getName());
    std::cout << player->getName() << ", it's your turn" << std::endl;
    printScores();
    gameModelPtr->getBoard()->printBoard();
    std::cout << "Your hand is" << std::endl;
    std::cout << player->handToString() << std::endl;
    processGameInput(player);
    std::cout << std::endl;
}

std::string GameView::processGameInput(Player* player)
{

    std::string cmd;
    bool inputValid = false;

    do
    {
        std::cout << "\n> ";
        std::vector<std::string> tokens;
        std::string token;
        std::getline(std::cin, token);
        std::istringstream iss(token);

        while (iss >> token)
        {
            tokens.push_back(token);
        }

        try
        {
            if (validatePlaceCmd(tokens))
            {
                std::string tileStr = tokens[1];
                Tile tile = convertStrToTile(tileStr);

                std::string coords = tokens[3];
                int posX = std::stoi(coords.substr(1, coords.size()));
                int posY = coords[0] - 'A';

                player->play(tile, gameModelPtr->getTileBag(), gameModelPtr->getBoard(),
                    posX, posY);
                inputValid = true;
            }

            if (validateReplaceCmd(tokens))
            {
                std::string tileStr = tokens[1];
                Tile tile = convertStrToTile(tileStr);
                player->replace(tile, gameModelPtr->getTileBag());
                inputValid = true;
            }

            if (validateSave(tokens))
            {
                SaveLoad* saver = new SaveLoad(gameModelPtr);
                saver->save(*gameModelPtr->getBoard(), tokens[1], gameModelPtr->getPlayers()[0], gameModelPtr->getPlayers()[1],
                    gameModelPtr->getTileBag(), gameModelPtr->getCurrentPlayerName());
                delete saver;
                inputValid = true;
            }

            if (tokens[0] == "quit")
            {
                quit();
                inputValid = true;
            }


            if (!inputValid)
            {
                throw "Invalid Input";
            }
        }
        catch (const char* msg)
        {
            std::cerr << msg << std::endl;
        }

    } while (!inputValid && !gameOver);

    return cmd;
}

bool GameView::validatePlaceCmd(std::vector<std::string> tokens)
{
    bool isValid = true;
    if (tokens.size() == 4)
    {
        if (tokens[0] != "place" && tokens[2] != "at")
        {
            isValid = false;
        }
        if (!validateTile(tokens[1]))
        {
            isValid = false;
        }
        if (!validateCoord(tokens[3]))
        {
            isValid = false;
        }
    }
    else
    {
        isValid = false;
    }
    return isValid;
};

bool GameView::validateReplaceCmd(std::vector<std::string> tokens)
{
    bool isValid = true;
    if (tokens.size() == 2 && tokens[0] == "replace")
    {

        if (!validateTile(tokens[1]))
        {
            isValid = false;
        }
    }
    else
    {
        isValid = false;
    }

    return isValid;
};

bool GameView::validateSave(std::vector<std::string> tokens)
{
    bool isValid = true;
    if (tokens.size() == 2 && tokens[0] == "save")
    {
        std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

        for (char& c : tokens[1])
        {
            if (allowedChars.find((char)toupper(c)) == std::string::npos)
            {
                isValid = false;
            }
        }
    }
    else
    {
        isValid = false;
    }

    return isValid;
}

bool GameView::validateTile(std::string tileStr)
{
    bool isValid = false;
    char allColours[6]{ 'R', 'O', 'Y', 'G', 'B', 'P' };

    char inputColour = tileStr[0];
    //convert to string to use stoi
    std::string tmp = "";
    tmp += tileStr[1];
    int inputShape = std::stoi(tmp);

    bool colourIsValid = false;
    for (char colour : allColours)
    {
        if (inputColour == colour)
        {
            colourIsValid = true;
        }
    }

    bool shapeIsValid = false;

    //type casting is checked for here already
    //if a char like 'a' is passed in, it will have an out of range value
    if (inputShape > 0 && inputShape <= 6)
    {
        shapeIsValid = true;
    }

    if (colourIsValid && shapeIsValid)
    {
        isValid = true;
    }
    return isValid;
};

Tile GameView::convertStrToTile(std::string tileStr)
{
    Colour colour = tileStr[0];
    std::string shapeStr = tileStr.substr(1, tileStr.size());
    Shape shape = std::stoi(shapeStr);

    return Tile(colour, shape);
}

bool GameView::validateCoord(std::string coord)
{
    bool isValid = false;
    char baseAlph = 'A';
    int yVal = coord[0];
    int xVal = coord[1];

    for (int offset = 0; offset < NUM_ALPHABETS; offset++)
    {
        // Uses char addition to check if yVal is in the alphabet
        if (yVal == baseAlph + offset)
        {
            isValid = true;
        };
        if (xVal >= 0 || xVal < NUM_ALPHABETS)
        {
            isValid = true;
        }
    }
    return isValid;
};

void GameView::printScores()
{
    std::vector<Player*> players = gameModelPtr->getPlayers();
    for (Player* player : players)
    {
        std::cout << "Score for " << player->getName() << ": "
            << player->getScore() << std::endl;
    }
}

/**
 * Difficult to check if file exists with current config. Maybe return
 * actual file instead?
 */
std::string GameView::createFileDir()
{
    std::cout << "Enter a filename from which load a game" << std::endl;
    std::cout << "> ";
    std::string file = "";
    std::cin >> file;
    return "saves/" + file + ".save";
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

void GameView::quit()
{
    std::cout << "\nGoodbye" << std::endl;
    this->gameOver = true;
}