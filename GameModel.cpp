#include "GameModel.h"

#include <iostream>
#include <string>
#include <memory>

GameModel::GameModel() {
    tileBag = new TileBag();
    board = new Board();
}

GameModel::~GameModel() {
    delete tileBag;
    delete board;
}

void GameModel::addPlayerToGame(std::string name) {
    Player* playerToAdd = new Player(name);
    playerToAdd->draw(tileBag);
    players.push_back(*playerToAdd);
}

Player GameModel::getPlayer(int playerNum) {
    return players[playerNum];
};

std::vector<Player> GameModel::getPlayers() {
    return this->players;
};

Board GameModel::getBoard() {
    return *board;
};

unsigned int GameModel::getNumPlayers() {
    return players.size();
}
