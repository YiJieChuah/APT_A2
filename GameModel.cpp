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
    players.push_back(Player(name));
    players.back().draw(tileBag);
}

Player GameModel::getPlayer(int playerNum) {
    return players[playerNum];
};

std::vector<Player> GameModel::getPlayers() {
    return players;
};

Board GameModel::getBoard() {
    return *board;
};

unsigned int GameModel::getNumPlayers() {
    return players.size();
}
