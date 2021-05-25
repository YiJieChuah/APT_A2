#ifndef ASSIGN2_GAMEVIEW_H
#define ASSIGN2_GAMEVIEW_H

#define NUM_ALPHABETS 26
#define MAX_CMD_LEN 4
#define COL_LEN 14
#define DIVIDER_LEN 35

#include <iostream>
#include <string>
#include <memory>

#include "GameModel.h"

class GameView
{
private:
    GameModel* gameModelPtr;
    bool gameOver;

    int getValidMenuSelection();
    void processMenuSelection(int input);

    void startNewGame();
    void startLoadedGame();

    int getNumPlayers();

    //validation methods
    bool validatePlaceCmd(std::vector<std::string> tokens);
    bool validatePlaceMultCmd(std::vector<std::string> tokens);
    bool validateReplaceCmd(std::vector<std::string> tokens);
    bool validateCoord(std::string coord);
    bool validateTile(std::string tile);
    bool validatePlayerName(std::string name);
    bool validateSave(std::vector<std::string> tokens);

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

    Tile convertStrToTile(std::string tileStr);
    std::vector<std::string> splitByComma(const std::string& list);

    void playerTurn(Player* player);
    void processGameInput(Player* player);

    void printScores();
    void newPlayer();
    std::string createFileDir();
    void printCredits();
    void gameOverScene();
    void helpManual();
    void printCharNumTimes(int numPrints, char character);

    int findFinalScored(std::vector<int> possibleScored);

public:
    GameView(GameModel* gameModelPtr);
    ~GameView();
    void init();
    void quit();
};

#endif // ASSIGN2_GAMEVIEW_H