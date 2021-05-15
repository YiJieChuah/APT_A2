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

void GameModel::setTileBag(LinkedList* tiles)
{
    this->tileBag->setTiles(tiles);
}

std::string GameModel::getGameOutcome() {
    std::string retStr = "";
    bool drawOccured = false;
    Player* currMaxPtsPlayer = players[0];
    //start from second player
    for (unsigned int i = 1; i < players.size(); i++) {
        if (currMaxPtsPlayer->getScore() < players[i]->getScore()) {
            currMaxPtsPlayer = players[i];
            drawOccured = false;
        }
        if (currMaxPtsPlayer->getScore() == players[i]->getScore()) {
            currMaxPtsPlayer = players[i];
            drawOccured = true;
        }
    }
    if (!drawOccured) {
        retStr += "Player " + currMaxPtsPlayer->getName() + " won!";
    }
    else {
        retStr += "Draw!";
    }
    currMaxPtsPlayer = nullptr;

    return retStr;
}
