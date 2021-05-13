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
    void addPlayerToGame(std::string name, int score, LinkedList* hand);

    unsigned int getNumPlayers();
    Player* getPlayer(int playerID);
    std::vector<Player*> getPlayers();
    Board* getBoard();
    TileBag* getTileBag();
    std::string getCurrentPlayer();

    void setCurrentPlayer(std::string name);

    // Need to add.
    void addPlayer(Player* player);
    void setBoard(Board* board);
    void setTileBag(LinkedList* tileBag);

private:
    std::vector<Player*> players;

    TileBag* tileBag;
    Board* board;
    std::string currentPlayer;
};

#endif // ASSIGN2_GAMEMODEL_H
