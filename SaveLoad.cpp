#include "Board.h"
#include "Player.h"
#include "SaveLoad.h"
#include <iostream>
#include <string>
#include <memory>
#include <fstream>

SaveLoad::SaveLoad()
{
    loadedPlayer1 = new Player();
    loadedPlayer2 = new Player();
    loadedTileBag = new LinkedList();
    board = new Board();
}

SaveLoad::~SaveLoad()
{
    delete loadedPlayer1;
    delete loadedPlayer2;
    delete loadedTileBag;
    delete board;
}

/**
 * Takes input from vaious places and puts it all into one .save file.
 * @return True if save was successful, otherwise false.
 */
bool SaveLoad::save(Board board, std::string fileName, Player* player1, Player* player2, TileBag* tileBag, std::string currentPLayer)
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
                if (i != tileBag->getTiles()->size())
                {
                    saveFile << ",";
                }
            }

            saveFile << std::endl;

            saveFile << currentPLayer << std::endl;
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

bool SaveLoad::load(std::string fileName)
{
    bool loaded = false;
    try
    {
        std::string line = "";
        std::ifstream saveFile("saves/" + fileName + ".save");
        if (saveFile)
        {
            // Board and tile bag.
            std::string boardDimensions = "";

            std::string boardState = "";
            std::string tileBagContents = "";

            int lineNum = 0;

            while (getline(saveFile, line))
            {
                if (lineNum == 0)
                {
                    loadedPlayer1->setName(line);
                }
                else if (lineNum == 1)
                {
                    loadedPlayer1->setScore(stoi(line));
                }
                else if (lineNum == 2)
                {
                    // Creating player1 hand.
                    unsigned int i = 0;
                    while (i < line.length())
                    {

                        char color = line.at(i);
                        std::string strShape(1, line.at(i + 1));
                        int shape = stoi(strShape);
                        loadedPlayer1->addTileToHand(new Tile(color, shape));
                        i += 3;
                    }
                }
                else if (lineNum == 3)
                {
                    loadedPlayer2->setName(line);
                }
                else if (lineNum == 4)
                {
                    loadedPlayer2->setScore(stoi(line));
                }
                else if (lineNum == 5)
                {
                    // Creatig player2 hand.
                    unsigned int i = 0;
                    while (i < line.length())
                    {
                        char color = line.at(i);
                        std::string strShape(1, line.at(i + 1));
                        int shape = stoi(strShape);
                        loadedPlayer2->addTileToHand(new Tile(color, shape));

                        i += 3;
                    }
                }
                else if (lineNum == 6)
                {
                    boardDimensions = line.at(0);
                }
                else if (lineNum == 7)
                {
                    unsigned int i = 0;
                    while (i < line.length())
                    {
                        if (line.at(i) == ' ')
                        {
                            i++;
                        }
                        // I got frustrated trying to solve a probelm and so this is my temp solution.
                        char letters[BOARD_DIMENSIONS] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
                        char color = line.at(i);
                        std::string strShape(1, line.at(i + 1));
                        int shape = stoi(strShape);
                        // Getting the x position.
                        char charPositionX = tolower(line.at(i + 3));
                        int positionX = 0;
                        for (int i = 0; i < BOARD_DIMENSIONS; i++)
                        {
                            if (charPositionX == letters[i])
                            {
                                positionX = i;
                                i = BOARD_DIMENSIONS;
                            }
                        }

                        int position;
                        if (i + 5 < line.length())
                        {
                            position = i + 5;
                        }
                        else
                        {
                            position = i - 2;
                        }

                        if (line.at(position) != ',')
                        {
                            std::string strPositionY1(1, line.at(i + 4));
                            std::string strPositionY2(1, line.at(i + 5));
                            std::string strPositionY = strPositionY1 + strPositionY2;
                            int positionY = stoi(strPositionY);
                            Tile* tile = new Tile(color, shape);

                            board->addTileForLoad(*tile, positionX, positionY);
                            delete tile;
                        }
                        else
                        {
                            std::string strPositionY(1, line.at(i + 4));
                            int positionY = stoi(strPositionY);
                            Tile* tile = new Tile(color, shape);

                            board->addTileForLoad(*tile, positionX, positionY);
                            delete tile;
                        }

                        i += 7;
                    }
                }
                else if (lineNum == 8)
                {
                    // Creating tile bag.
                    unsigned int i = 0;
                    while (i < line.length())
                    {
                        char color = line.at(i);
                        std::string strShape(1, line.at(i + 1));
                        int shape = stoi(strShape);
                        loadedTileBag->add_back(new Tile(color, shape));

                        i += 3;
                    }
                }
                else if (lineNum == 9)
                {
                    currentPlayer = line;
                }

                lineNum++;
            }
            saveFile.close();
            loaded = true;
        }
        else
        {
            throw "No such file.";
        }
    }
    catch (const char* msg)
    {
        std::cerr << msg << '\n';
    }
    return loaded;
}

// TODO: Figure out why this method cant be called.
std::string SaveLoad::createTileString(LinkedList list)
{
    std::string tiles;
    for (int i = 0; i < list.size(); i++)
    {
        tiles += list.get(i)->colour;
        tiles += list.get(i)->shape;
        if (i != list.size())
        {
            tiles += ",";
        }
    }
    tiles += "\n";

    return "";
}

Player SaveLoad::getPlayer1() const
{
    return *this->loadedPlayer1;
}
Player SaveLoad::getPlayer2() const
{
    return *this->loadedPlayer2;
}

Board SaveLoad::getLoadedBoard()
{
    return *this->board;
}
LinkedList SaveLoad::getLoadedTileBag()
{
    return *this->loadedTileBag;
}
std::string SaveLoad::getCurrentPlayer()
{
    return this->currentPlayer;
}
