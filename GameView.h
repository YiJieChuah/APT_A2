#ifndef ASSIGN2_GAMEVIEW_H
#define ASSIGN2_GAMEVIEW_H

#include <iostream>
#include <string>
#include <memory>

#include "GameModel.h"

class GameView
{
private:
    GameModel* gameModelPtr;
public:
    GameView(GameModel* gameModelPtr);
    ~GameView();
    void init();
    int getValidSelection();
    void processSelection(int input);
    void startNewGame();
    void playerTurn(Player player);
    void printScores();

    void newPlayer();
    std::string createFileDir();
    void printCredits();

};

#endif // ASSIGN2_GAMEVIEW_H