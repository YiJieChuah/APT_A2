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

    void addPlayerToGame(std::string name);
    unsigned int getNumPlayers();

private:
    std::vector<Player> players;

    //TODO: Need wrapper class?
    std::unique_ptr<LinkedList> tileBag;
    std::unique_ptr<Board> board;
};

#endif // ASSIGN2_GAMEMODEL_H
