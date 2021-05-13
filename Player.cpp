#include <memory>
#include <iostream>

#include "Player.h"
#include "Board.h"

#define HAND_SIZE 6

Player::Player() {}

Player::Player(std::string name)
{
    this->name = name;
    this->score = 0;
    this->hand = new LinkedList();
}

Player::Player(std::string name, int score, LinkedList* hand)
{
    this->name = name;
    this->score = score;
    this->hand = hand;
}

Player::Player(const Player& other)
{
    this->name = other.name;
    this->score = other.score;
    this->hand = new LinkedList(*other.hand);
}

Player::~Player()
{
    delete hand;
}

void Player::draw(TileBag* bag)
{
    while (hand->size() < HAND_SIZE)
    {
        this->hand->add_back(bag->pop());
    }
}

void Player::play(Tile tile, TileBag* tileBag, Board* board, int posX, int posY)
{
    int tileIdx = findTileInHand(tile);
    if (tileIdx != -1)
    {
        if (board->addTile(tile, posX, posY))
        {
            hand->remove(tileIdx);
            score += board->calculateScore(posX, posY);
            draw(tileBag);
        }
    }
    else
    {
        throw "Invalid Input";
    }
}

void Player::replace(Tile tile, TileBag* tileBag)
{
    int tileIdx = findTileInHand(tile);
    if (tileIdx != -1)
    {
        hand->remove(tileIdx);
        draw(tileBag);
    }
    else
    {
        throw "Invalid Input";
    }
}

int Player::findTileInHand(Tile tile)
{
    int idx = -1;
    for (int i = 0; i < hand->size(); i++)
    {
        if (hand->get(i)->equals(tile))
        {
            idx = i;
        }
    }
    return idx;
}

std::string Player::getName()
{
    return this->name;
}

void Player::setName(std::string name)
{
    this->name = name;
}

LinkedList* Player::getHand()
{
    return this->hand;
}

std::string Player::handToString()
{
    std::string handStr = "";
    for (int i = 0; i < hand->size(); i++)
    {
        handStr += hand->get(i)->toString();
        if (i != hand->size() - 1)
        {
            handStr += ",";
        }
    }
    return handStr;
}

int Player::getScore()
{
    return this->score;
}

void Player::setScore(int score)
{
    this->score = score;
}

void Player::addTileToHand(Tile* tile)
{
    if (this->hand != nullptr)
    {
        this->hand->add_back(tile);
    }
    else
    {
        this->hand = new LinkedList();
        this->hand->add_back(tile);
    }
}
