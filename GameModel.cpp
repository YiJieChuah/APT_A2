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
}

void GameModel::addPlayerToGame(std::string name, int score, LinkedList* hand)
{
    Player* playerToAdd = new Player(name, score, hand);
    players.push_back(playerToAdd);
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

std::string GameModel::getCurrentPlayer()
{
    return currentPlayer;
}
void GameModel::setCurrentPlayer(std::string name)
{
    this->currentPlayer = name;
}

void GameModel::addPlayer(Player* player)
{
    players.push_back(player);
}
void GameModel::setBoard(Board* board)
{
    this->board = board;
}
void GameModel::setTileBag(LinkedList* tileBag)
{
    this->tileBag->setTiles(tileBag);
}
