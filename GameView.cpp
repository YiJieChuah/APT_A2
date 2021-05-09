#include <iostream>
#include <sstream>
#include <string>

#include "GameView.h"
#include "Tile.h"

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

    int selection = getValidMenuSelection();
    processMenuSelection(selection);
}

int GameView::getValidMenuSelection() {
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

void GameView::processMenuSelection(int input) {
    std::string fileDirectory;

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

    std::cout << "\nLet's Play!\n"
        << std::endl;

    //TODO: temp for testing
    std::vector<Player*> players = gameModelPtr->getPlayers();
    for (Player* player : players) {
        playerTurn(player);
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

    //TODO: validate player name
    std::cin >> playerName;
    gameModelPtr->addPlayerToGame(playerName);
}

void GameView::playerTurn(Player* player)
{
    std::cout << player->getName() << ", it's your turn" << std::endl;
    printScores();
    gameModelPtr->getBoard()->printBoard();
    std::cout << "Your hand is" << std::endl;
    std::cout << player->handToString() << std::endl;
    processGameInput(player);
}

std::string GameView::processGameInput(Player* player) {
    bool inputValid = false;
    std::string cmd;
    do
    {
        std::cout << "\n> ";
        // std::string tmp;

        std::vector<std::string> tokens;
        std::string token;
        std::cin.ignore();
        std::getline(std::cin, token);
        std::istringstream iss(token);

        while (iss >> token) {
            tokens.push_back(token);
        }

        try
        {
            if (tokens.size() == 4)
            {
                if (validatePlaceCmd(tokens)) {
                    std::string tileStr = tokens[1];
                    Colour inputColour = convertCharToColour(tileStr[0]);

                    Shape inputShape = convertIntToShape(std::stoi(tileStr.substr(1, 1)));
                    Tile tile(inputColour, inputShape);

                    std::string coords = tokens[3];

                    int posX = std::stoi(coords.substr(1, 1));
                    int posY = coords[0] - 'A';

                    player->play(tile, gameModelPtr->getTileBag(), gameModelPtr->getBoard(),
                        posX, posY);
                }
                else {
                    throw "Invalid Input";
                }
            }
            else {
                throw "Invalid Input";
            }
            inputValid = true;
        }
        catch (const char* msg)
        {
            std::cout << msg << std::endl;
        }

    } while (!inputValid);

    return cmd;
}

bool GameView::validatePlaceCmd(std::vector <std::string> tokens) {
    bool isValid = true;
    if (tokens[0] != "place" && tokens[2] != "at") {
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
    return isValid;
};

bool GameView::validateReplaceCmd(std::vector <std::string> tokens) {
    return false;
};

bool GameView::validateTile(std::string tileStr) {
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
        if (inputColour == colour) {
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

    if (colourIsValid && shapeIsValid) {
        isValid = true;
    }
    return isValid;

};

bool GameView::validateCoord(std::string coord) {
    bool isValid = false;
    char baseAlph = 'A';
    int yVal = coord[0];
    int xVal = coord[1];

    for (int offset = 0; offset < NUM_ALPHABETS; offset++)
    {
        // Uses char addition to check if yVal is in the alphabet
        if (yVal == baseAlph + offset) {
            isValid = true;
        };
        if (xVal >= 0 || xVal < NUM_ALPHABETS) {
            isValid = true;
        }
    }
    return isValid;
};

Colour GameView::convertCharToColour(char colour) {
    Colour returnColour = EMPTY_COLOR;
    if (colour == 'R') {
        returnColour = RED;
    }
    else if (colour == 'O') {
        returnColour = ORANGE;
    }
    else if (colour == 'Y') {
        returnColour = YELLOW;
    }
    else if (colour == 'G') {
        returnColour = GREEN;
    }
    else if (colour == 'B') {
        returnColour = BLUE;
    }
    else if (colour == 'P') {
        returnColour = PURPLE;
    }
    return returnColour;
}

Shape GameView::convertIntToShape(int shape) {
    Shape returnShape = EMPTY_SHAPE;
    if (shape == 1) {
        returnShape = CIRCLE;
    }
    else if (shape == 2) {
        returnShape = STAR_4;
    }
    else if (shape == 3) {
        returnShape = DIAMOND;
    }
    else if (shape == 4) {
        returnShape = SQUARE;
    }
    else if (shape == 5) {
        returnShape = STAR_6;
    }
    else if (shape == 6) {
        returnShape = CLOVER;
    }
    return returnShape;
}


void GameView::printScores() {
    std::vector<Player*> players = gameModelPtr->getPlayers();
    for (Player* player : players) {
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