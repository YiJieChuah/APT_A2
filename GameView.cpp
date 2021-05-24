#include <iostream>
#include <sstream>
#include <string>

#include <map>
#include <ios>
#include <limits>
#include <iomanip>

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
    //Init with dummy value
    int selection = -1;
    do
    {
        std::cout << "\n> ";
        std::cin >> selection;

        try
        {
            if (!std::cin.eof()) {
                // Checks for not a number
                if (!std::cin.good() && !gameOver)
                {
                    //Resets cin flags and clear buffer for next input attempt
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');
                    throw std::domain_error("Input was not a number!");
                }
                if (selection <= 0 || selection > 4)
                {
                    throw std::out_of_range("Make sure your input is between 1 and 4!");
                }
            }
            else {
                quit();
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
    } while ((!inputValid || !std::cin.good()) && !gameOver);

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
        } while (!loader->load(fileDirectory) && !std::cin.eof());

        if (!std::cin.eof()) {
            startLoadedGame();
        }
        else {
            quit();
        }
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


void GameView::startNewGame()
{
    std::cout << "Starting a New Game" << std::endl;

    int numPlayers = getNumPlayers();
    std::cout << "Setting up " << numPlayers << "-player game" << std::endl;

    for (int i = 0; i < numPlayers; i++)
    {
        newPlayer();
    }

    std::cout << "\nLet's Play!\n" << std::endl;
    // Ignores \n char to avoid instant input termination
    std::cin.ignore();
    while (gameModelPtr->getTileBag()->numTilesLeft() > 0 && !gameOver) {

        for (Player* player : gameModelPtr->getPlayers())
        {
            gameModelPtr->setCurrentPlayer(player->getName());
            playerTurn(player);
        }
    }


}

void GameView::startLoadedGame()
{
    // bool firstIteration = true;
    std::cout << "\nQwirkle game successfully loaded" << std::endl;

    std::vector<Player*> players = gameModelPtr->getPlayers();
    bool firstIter = true;
    while (!gameOver)
    {
        for (Player* player : players)
        {
            if (!firstIter) {
                gameModelPtr->setCurrentPlayer(player->getName());
            }

            std::string currPlayerName = gameModelPtr->getCurrentPlayerName();
            std::string loopName = player->getName();

            if (!gameOver) {
                if (currPlayerName == player->getName()) {
                    playerTurn(player);
                    firstIter = false;

                }
            }
        }
    }
}

int GameView::getNumPlayers()
{
    int numPlayers = 0;
    bool inputValid = false;

    std::cout << "Enter the number of players (minimum 2, maximum 4)";

    do {
        std::cout << "\n> ";
        std::cin >> numPlayers;
        try {
            if (!std::cin.eof()) {
                if (!std::cin.good() && !gameOver) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');
                    throw std::domain_error("Input was not a number!");
                }

                if (numPlayers < 2 || numPlayers > 4)
                {
                    throw std::out_of_range("Only 2-4 players allowed!");
                }
            }
            else {
                quit();
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
    } while (!inputValid);

    return numPlayers;
}


void GameView::newPlayer()
{
    std::string playerName;
    std::cout << "\nEnter a name for player"
        << gameModelPtr->getNumPlayers() + 1
        << "(uppercase characters only)";

    bool nameIsValid = false;
    do
    {
        std::cout << "\n> ";
        std::cin >> playerName;
        if (std::cin.eof()) {
            quit();
        }
        else {
            nameIsValid = validatePlayerName(playerName);
            if (!nameIsValid)
            {
                std::cout << "Invalid name. Make sure you include only uppercase alphanumerics!" << std::endl;
            }
        }
    } while (!nameIsValid && !gameOver);
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
    if (!gameOver) //necessary in order to break out of loop
    {
        std::cout << player->getName() << ", it's your turn" << std::endl;
        printScores();
        gameModelPtr->getBoard()->printBoard();
        std::cout << "Your hand is" << std::endl;
        std::cout << player->handToString() << std::endl;
        processGameInput(player);
        std::cout << std::endl;
    }
}

// TODO: Change this into an int return maybe?
void GameView::processGameInput(Player* player)
{

    std::string cmd;
    bool inputValid = false;
    bool isNormalInput = true;

    do
    {
        inputValid = false;
        isNormalInput = true;

        std::cout << "\n> ";
        std::vector<std::string> tokens;
        std::string token;
        std::getline(std::cin, token);
        if (std::cin.eof()) {
            tokens.push_back("quit");
        }
        else {
            std::istringstream iss(token);
            while (iss >> token)
            {
                tokens.push_back(token);
            }
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

                player->play(tile, gameModelPtr->getTileBag(),
                    gameModelPtr->getBoard(), posX, posY);
                if (player->getHand()->size() == 0 &&
                    gameModelPtr->getTileBag()->numTilesLeft() == 0) {
                    gameOverScene();
                    quit();
                }
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
                if (saver->save(tokens[1])) {
                    std::cout << "File Saved!" << std::endl;
                }
                else {
                    std::cout << "Error occured while saving!" << std::endl;
                };
                inputValid = true;
                delete saver;
            }

            if (tokens[0] == "quit")
            {
                quit();
                inputValid = true;
            }

            if (tokens[0] == "help")
            {
                helpManual();
                inputValid = true;
                isNormalInput = false;
            }

            if (!inputValid && isNormalInput)
            {
                throw "No Such Command. Type 'help' for the list of commands";
            }
        }
        catch (const char* msg)
        {
            std::cout << msg << std::endl;
        }

    } while (!(inputValid && isNormalInput));
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

    if (tileStr.size() == 2) {
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

    std::string names[4] =
    { "Seth Danford", "Simon Dean", "Jeremy West", "Yi Jie Chuah" };
    std::string studentIDs[4] =
    { "s3845408", "s3599190", "s3869546", "s3847905" };
    std::string emails[4] =
    { "s3845408@student.rmit.edu.au", "s3599190@student.rmit.edu.au",
    "s3869546@student.rmit.edu.au", "s3847905@student.rmit.edu.au" };

    printCharNumTimes(DIVIDER_LEN, '-');
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
    printCharNumTimes(DIVIDER_LEN, '-');
    std::cout << std::endl;
}

void GameView::gameOverScene() {
    std::cout << "Game over" << std::endl;
    printScores();
    std::cout << gameModelPtr->getGameOutcome() << std::endl;
}

void GameView::quit()
{
    std::cout << "\nGoodbye" << std::endl;
    this->gameOver = true;
}

void GameView::helpManual()
{
    std::map<char, std::string> colourMap = {
        {RED, "Red"},
        {ORANGE, "Orange"},
        {YELLOW, "Yellow"},
        {GREEN, "Green"},
        {BLUE, "Blue"},
        {PURPLE, "Purple"}
    };

    std::string shapeNames[6] = {
        "Circle", "4-Star", "Diamond", "Square", "6-Star", "Clover"
    };

    std::cout << "***************HELP***************" << std::endl;

    std::cout << "There are 4 commands you can do in-game:" << std::endl;
    std::cout << "1. place <tilecode> at <coordinates>" << std::endl;
    std::cout << "2. replacing tiles (note that this will replace the first tile which matches from the left) - replace <tile>" << std::endl;
    std::cout << "3. save <filename> - will save the current game as a '.save' file under the 'saves' directory. " << std::endl;
    std::cout << "4. quit - will exit the game without saving it. So make sure you save first!" << std::endl;
    std::cout << std::endl;
    std::cout << "Tile shape and colour code are as follows:" << std::endl;

    printCharNumTimes(COL_LEN * 4 + 5, '-');

    std::cout << '|';
    std::cout << std::setw(COL_LEN);
    std::cout << "Colour Code" << '|';
    std::cout << std::setw(COL_LEN);
    std::cout << "Colour" << '|';
    std::cout << std::setw(COL_LEN);
    std::cout << "Shape Code" << '|';
    std::cout << std::setw(COL_LEN);
    std::cout << "Shape";
    std::cout << '|' << std::endl;

    printCharNumTimes(COL_LEN * 4 + 5, '-');

    int iter = 0;
    for (auto const& colour : colourMap)
    {
        std::cout << '|';
        std::cout << std::setw(COL_LEN);
        std::cout << colour.first << '|';
        std::cout << std::setw(COL_LEN);
        std::cout << colour.second << '|';
        std::cout << std::setw(COL_LEN);
        std::cout << shapeNames[iter] << '|';
        std::cout << std::setw(COL_LEN);
        std::cout << ++iter;
        std::cout << '|' << std::endl;
    }
    printCharNumTimes(COL_LEN * 4 + 5, '-');
    std::cout << "*************END HELP*************" << std::endl;

}

void GameView::printCharNumTimes(int numPrints, char character) {
    for (int i = 0; i < numPrints; i++)
    {
        std::cout << character;
    }
    std::cout << std::endl;
};