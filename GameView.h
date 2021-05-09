#ifndef ASSIGN2_GAMEVIEW_H
#define ASSIGN2_GAMEVIEW_H

#define NUM_ALPHABETS 26
#define MAX_CMD_LEN 4

#include <iostream>
#include <string>
#include <memory>

#include "GameModel.h"

class GameView
{
private:
    GameModel* gameModelPtr;

    bool validatePlaceCmd(std::vector <std::string> tokens);
    bool validateReplaceCmd(std::vector <std::string> tokens);
    bool validateCoord(std::string coord);
    bool validateTile(std::string tile);

    /**
     * Assumes that the char passed in is valid
     * @return colour typedef value matching the char
     */
    Colour convertCharToColour(char colour);

    /**
     * Assumes that the shape passed in is valid
     * @return shape typedef value matching the int
     */
    Shape convertIntToShape(int shape);

    int getValidMenuSelection();
    void processMenuSelection(int input);
    void startNewGame();
    void playerTurn(Player* player);
    std::string processGameInput(Player* player);
    void printScores();
    void newPlayer();
    std::string createFileDir();
    void printCredits();
public:
    GameView(GameModel* gameModelPtr);
    ~GameView();
    void init();


};

#endif // ASSIGN2_GAMEVIEW_H