#include "Board.h"
#include "Player.h"
#include "SaveLoad.h"
#include <iostream>
#include <string>
#include <memory>
#include <fstream>

SaveLoad::SaveLoad()
{
}

SaveLoad::~SaveLoad()
{
}

/**
 * Takes input from vaious places and puts it all into one .save file.
 * @return True if save was successful, otherwise false.
 */
bool SaveLoad::save(Board board, std::string fileName, Player player1, Player player2, LinkedList tileBag, std::string currentPLayer)
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
            saveFile << player1.getName() << std::endl;
            saveFile << player1.getScore() << std::endl;
            for (int i = 0; i < player1.getHand().size(); i++)
            {
                saveFile << player1.getHand().get(i)->colour;
                saveFile << player1.getHand().get(i)->shape;
                if (i != player1.getHand().size())
                {
                    saveFile << ",";
                }
            }
            saveFile << std::endl;
            saveFile << player2.getName() << std::endl;
            saveFile << player2.getScore() << std::endl;
            for (int i = 0; i < player2.getHand().size(); i++)
            {
                saveFile << player2.getHand().get(i)->colour;
                saveFile << player2.getHand().get(i)->shape;
                if (i != player2.getHand().size())
                {
                    saveFile << ",";
                }
            }
            saveFile << std::endl;

            // Inserting board details.
            saveFile << board.getBoardDimentions() << "," << board.getBoardDimentions() << std::endl;
            saveFile << board.getSaveFormat() << std::endl;
            for (int i = 0; i < tileBag.size(); i++)
            {
                saveFile << tileBag.get(i)->colour;
                saveFile << tileBag.get(i)->shape;
                if (i != tileBag.size())
                {
                    saveFile << ",";
                }
            }
            saveFile << std::endl;

            saveFile << currentPLayer << std::endl;
            saveFile.close();
            saved = true;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return saved;
}

bool SaveLoad::load(std::string fileName)
{
    bool loaded = false;

    try
    {
        std::string line;
        std::ifstream saveFile("saves/" + fileName + ".save");

        // Board and tile bag.
        std::string boardDimentions;

        std::string boardState;
        std::string tileBagContents;

        int lineNum = 0;

        while (getline(saveFile, line))
        {
            if (lineNum == 0)
            {
                loadedPlayer1.setName(line);
            }
            else if (lineNum == 1)
            {
                loadedPlayer1.setScore(stoi(line));
            }
            else if (lineNum == 2)
            {
                // Creating player1 hand.
                int i = 0;
                while (i < line.length())
                {

                    char color = line.at(i);
                    std::string strShape(1, line.at(i + 1));
                    int shape = stoi(strShape);
                    loadedPlayer1.getHand().add_back(new Tile(color, shape));

                    i += 3;
                }
            }
            else if (lineNum == 3)
            {
                loadedPlayer2.setName(line);
            }
            else if (lineNum == 4)
            {
                loadedPlayer2.setScore(stoi(line));
            }
            else if (lineNum == 5)
            {
                // Creatig player2 hand.
                int i = 0;
                while (i < line.length())
                {
                    char color = line.at(i);
                    std::string strShape(1, line.at(i + 1));
                    int shape = stoi(strShape);
                    loadedPlayer2.getHand().add_back(new Tile(color, shape));

                    i += 3;
                }
            }
            else if (lineNum == 6)
            {
                boardDimentions = line.at(0);
            }
            else if (lineNum == 7)
            {
                // Adding tiles to the board. --------------- NEED HELP
                int i = 0;
                while (i < line.length())
                {
                    char color = line.at(i);
                    std::string strShape(1, line.at(i + 1));
                    int shape = stoi(strShape);
                    // Need special method for adding tiles for load file?

                    i += 7;
                }
            }
            else if (lineNum == 8)
            {
                // Creating tile bag.
                int i = 0;
                while (i < line.length())
                {
                    char color = line.at(i);
                    std::string strShape(1, line.at(i + 1));
                    int shape = stoi(strShape);
                    loadedTileBag.add_back(new Tile(color, shape));

                    i += 3;
                }
            }
            else if (lineNum == 9)
            {
                currentPlayer = line;
            }

            // TODO: TESTING.
            std::cout << line;

            lineNum++;
        }

        saveFile.close();

        loaded = true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
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

Player SaveLoad::getPlayer1()
{
    return this->loadedPlayer1;
}
Player SaveLoad::getPlayer2()
{
    return this->loadedPlayer2;
}

std::vector<std::vector<Tile> > SaveLoad::getLoadedBoard()
{
    return this->loadedBoard;
}
LinkedList SaveLoad::getLoadedTileBag()
{
    return this->loadedTileBag;
}
std::string SaveLoad::getCurrentPlayer()
{
    return this->currentPlayer;
}
