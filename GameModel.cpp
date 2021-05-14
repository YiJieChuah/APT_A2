#include "GameModel.h"

#include <iostream>
#include <string>
#include <memory>

GameModel::GameModel()
{
    tileBag = new TileBag();
    board = new Board();
}

GameModel::~GameModel()
{
    delete tileBag;
    delete board;
    for (Player* player : players)
    {
        delete player;
    }
    players.clear();
}

void GameModel::addPlayerToGame(std::string name)
{
    Player* playerToAdd = new Player(name);
    playerToAdd->draw(tileBag);
    players.push_back(playerToAdd);

    //Set the first player added as current player.
    if (players.size() == 1) {
        setCurrentPlayer(playerToAdd->getName());
    }
}

void GameModel::addPlayerToGame(Player* player)
{
    players.push_back(player);
}

std::vector<Player*> GameModel::getPlayers()
{
    return players;
};

Board* GameModel::getBoard()
{
    return board;
};

TileBag* GameModel::getTileBag()
{
    return tileBag;
}

unsigned int GameModel::getNumPlayers()
{
    return players.size();
}

std::string GameModel::getCurrentPlayerName()
{
    return currentPlayerName;
}

void GameModel::setCurrentPlayer(std::string currPlayerName)
{
    this->currentPlayerName = currPlayerName;
}

void GameModel::setBoard(Board* board)
{
    this->board = board;
}

void GameModel::setTileBag(LinkedList* tiles)
{
    this->tileBag->setTiles(tiles);
}
