#include "Board.h"
#include <iostream>
#include <string>
#include <memory>
#include <fstream>

class SaveLoad
{

public:
    bool save(Board board, std::string fileName);
    bool load(std::string fileName);
};

bool SaveLoad::save(Board board, std::string fileName)
{

    try
    {
        std::ofstream saveFile(fileName + ".save");

        if (saveFile.is_open())
        {
            saveFile << board.getSaveFormat();
            saveFile.close();
        }
        else
            std::cout << "There was a problem saving the game.";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool SaveLoad::load(std::string fileName)
{

    return false;
}