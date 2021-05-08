#ifndef ASSIGN2_GAMEMODEL_H
#define ASSIGN2_GAMEMODEL_H

#include <vector>
#include <memory>

#include "Player.h"
#include "Board.h"

class GameModel
{
public:
    GameModel();
    ~GameModel();

    void addPlayerToGame(std::string name);
    unsigned int getNumPlayers();
    Player getPlayer(int playerNum);
    std::vector<Player> getPlayers();
    Board getBoard();

private:
    std::vector<Player> players;

    //TODO: Need wrapper class?
    LinkedList* tileBag;
    Board* board;
};

#endif // ASSIGN2_GAMEMODEL_H
