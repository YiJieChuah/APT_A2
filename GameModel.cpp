#include "GameModel.h"

#include <iostream>
#include <string>
#include <memory>

GameModel::GameModel() {}

void GameModel::addPlayerToGame(std::string name) {
    players.push_back(Player(name));
}

Player GameModel::getPlayer(int playerNum) {
    return players[playerNum];
};

unsigned int GameModel::getNumPlayers() {
    return players.size();
}