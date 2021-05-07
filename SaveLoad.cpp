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

bool SaveLoad::save(Board board, std::string fileName, Player player1, Player player2)
{

    try
    {
        std::ofstream saveFile("saves/" + fileName + ".save");

        if (saveFile.is_open())
        {
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
            saveFile << board.getBoardDimentions() << "," << board.getBoardDimentions() << std::endl;
            saveFile << board.getSaveFormat() << std::endl;
            // INSERT TILEBAG CONTENTS
            // INSERT CURRENT PLAYERS NAME
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