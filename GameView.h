#ifndef ASSIGN2_GAMEVIEW_H
#define ASSIGN2_GAMEVIEW_H

#include <iostream>
#include <string>
#include <memory>

#include "GameModel.h"

class GameView
{
private:
    std::shared_ptr<GameModel> gameModelPtr;
public:
    GameView(std::shared_ptr<GameModel> gameModelPtr);
    ~GameView();
    void init();
    int getValidSelection();
    void processSelection(int input);
    void startNewGame();

    void newPlayer();
    std::string createFileDir();
    void printCredits();

};

#endif // ASSIGN2_GAMEVIEW_H