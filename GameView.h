#ifndef ASSIGN2_GAMEVIEW_H
#define ASSIGN2_GAMEVIEW_H

#include <iostream>
#include <string>

class GameView
{

public:
    GameView();
    ~GameView();
    void init();
    int getValidInput(int input);
    void processInput();
    void startNewGame();

    std::string newPlayer();
    std::string createFileDir();
    void printCredits();
};

#endif // ASSIGN2_GAMEVIEW_H