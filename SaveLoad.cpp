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
        }
        else {
            std::cout << "Invalid Input." << std::endl;
        }
    }

    return loaded;
}

bool SaveLoad::loadFile(std::ifstream& input) {
    bool loaded = false;
    std::string line;
    int lineNum = 0;

    while (!getline(input, line).eof()) {
        ++lineNum;
        std::cout << line << std::endl;

    }

    return loaded;
}





// Player SaveLoad::getPlayer1() const
// {
//     return *this->loadedPlayer1;
// }
// Player SaveLoad::getPlayer2() const
// {
//     return *this->loadedPlayer2;
// }

// Board SaveLoad::getLoadedBoard()
// {
//     return *this->board;
// }
// LinkedList SaveLoad::getLoadedTileBag()
// {
//     return *this->loadedTileBag;
// }
// std::string SaveLoad::getCurrentPlayer()
// {
//     return this->currentPlayer;
// }
