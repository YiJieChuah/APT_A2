#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <fstream>

#include "Board.h"
#include "Player.h"
#include "SaveLoad.h"

SaveLoad::SaveLoad(GameModel* gameModelPtr)
{
    this->gameModelPtr = gameModelPtr;
}

SaveLoad::~SaveLoad() {}

/**
 * Takes input from vaious places and puts it all into one .save file.
 * @return True if save was successful, otherwise false.
 */
bool SaveLoad::save(Board board, std::string fileName, Player* player1,
    Player* player2, TileBag* tileBag, std::string currPlayerName)
{
    bool saved = false;
    try
    {

        // Opens or creates the file.
        std::ofstream saveFile("saves/" + fileName + ".save");

        // Checking if the file was opened.
        if (saveFile.is_open())
        {
            // Inserting player details.
            saveFile << player1->getName() << std::endl;
            saveFile << player1->getScore() << std::endl;
            saveFile << player1->handToString() << std::endl;

            saveFile << player2->getName() << std::endl;
            saveFile << player2->getScore() << std::endl;
            saveFile << player2->handToString() << std::endl;

            // Inserting board details.
            saveFile << board.getBoardDimensions() << "," << board.getBoardDimensions() << std::endl;
            saveFile << board.getSaveFormat() << std::endl;

            for (int i = 0; i < tileBag->getTiles()->size(); i++)
            {
                saveFile << tileBag->getTiles()->get(i)->colour;
                saveFile << tileBag->getTiles()->get(i)->shape;
                if (i != tileBag->getTiles()->size() - 1)
                {
                    saveFile << ",";
                }
            }

            saveFile << std::endl;

            saveFile << gameModelPtr->getCurrentPlayerName() << std::endl;
            saveFile.close();
            saved = true;
        }
        else
        {
            throw "Error saving file!";
        }
    }
    catch (const char* msg)
    {
        std::cerr << msg << '\n';
    }

    return saved;
}

bool SaveLoad::load(std::string filePath)
{
    bool loaded = false;

    std::ifstream file(filePath);
    std::cin.ignore();

    if (!file) {
        std::cout << "No Such File." << std::endl;
    }
    else {
        if (loadFile(file)) {
            std::cout << "File Loaded!" << std::endl;
            loaded = true;
        }
        else {
            std::cout << "Error loading file" << std::endl;
        }
    }

    file.close();
    return loaded;
}

bool SaveLoad::loadFile(std::ifstream& input) {
    bool loaded = false;
    std::string line;
    int lineNum = 0;
    Player player1;
    Player player2;

    while (!getline(input, line).eof())
    {
        //Player 1 Load
        if (lineNum == 0) {
            player1.setName(line);
        }
        else if (lineNum == 1) {
            player1.setScore(stoi(line));
        }
        else if (lineNum == 2) {
            std::vector<std::string> tilesStr = splitByDelimiter(line, ',');
            player1.setHand(initTiles(tilesStr));
            gameModelPtr->addPlayerToGame(new Player(player1));
        }

        //Player 2 Load
        else if (lineNum == 3) {
            player2.setName(line);
        }
        else if (lineNum == 4) {
            player2.setScore(stoi(line));
        }
        else if (lineNum == 5) {
            std::vector<std::string> tilesStr = splitByDelimiter(line, ',');
            // LinkedList* hand = initHand(tilesStr);
            player2.setHand(initTiles(tilesStr));
            // hand = nullptr;

            gameModelPtr->addPlayerToGame(new Player(player2));
        }

        else if (lineNum == 6) {
            //Supposed to handle board dimensions
            //They are fixed at 26 for base gameplay so placeholder for now
        }
        else if (lineNum == 7) {
            std::vector<std::string> tokens = splitByDelimiter(line, ',');

            for (std::string token : tokens) {
                std::vector<std::string> tileLocInfo = splitByDelimiter(token, '@');

                //trim
                tileLocInfo[0].erase(0, tileLocInfo[0].find_first_not_of(' '));
                std::string tileStr = tileLocInfo[0];
                std::string tileLocStr = tileLocInfo[1];

                int posX = std::stoi(tileLocStr.substr(1, tileLocStr.size()));
                int posY = tileLocStr[0] - 'A';

                Tile* tile = strToTile(tileStr);
                gameModelPtr->getBoard()->addTileForLoad(*tile, posX, posY);
                delete tile;

            }
            loaded = true;
        }
        else if (lineNum == 8) {
            std::vector<std::string> tilesStr = splitByDelimiter(line, ',');
            gameModelPtr->setTileBag(initTiles(tilesStr));

        }
        ++lineNum;
    }

    return loaded;
}

std::vector<std::string> SaveLoad::splitByDelimiter(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(line);

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


LinkedList* SaveLoad::initTiles(std::vector<std::string> tilesStr) {
    LinkedList* tiles = new LinkedList();
    for (std::string tileStr : tilesStr) {
        tiles->add_back(strToTile(tileStr));
    }
    return tiles;
}


Tile* SaveLoad::strToTile(std::string tileStr) {
    Colour colour = tileStr[0];
    std::string shapeStr = tileStr.substr(1, tileStr.size());
    Shape shape = stoi(shapeStr);
    return new Tile(colour, shape);
}