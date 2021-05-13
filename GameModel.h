#ifndef ASSIGN2_GAMEMODEL_H
#define ASSIGN2_GAMEMODEL_H

#include <vector>
#include <memory>

#include "Player.h"
#include "Board.h"
#include "TileBag.h"

class GameModel
{
public:
    GameModel();
    ~GameModel();

    void addPlayerToGame(std::string name);
    void addPlayerToGame(Player* player);

    unsigned int getNumPlayers();
    std::vector<Player*> getPlayers();
    Board* getBoard();
    TileBag* getTileBag();

    std::string getCurrentPlayerName();
    void setCurrentPlayer(std::string currPlayerName);

    // Need to add.
    void addPlayer(Player* player);
    void setBoard(Board* board);
    void setTileBag(LinkedList* tiles);

private:
    std::vector<Player*> players;

    TileBag* tileBag;
    Board* board;
    std::string currentPlayerName;
};

#endif // ASSIGN2_GAMEMODEL_H
