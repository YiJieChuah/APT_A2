#include <memory>

#include "Player.h"
#include "Board.h"

#define HAND_SIZE 6



Player::Player() {}

Player::Player(int id, std::string name)
{
    this->id = id;
    this->name = name;
    this->score = 0;
    this->hand = new LinkedList();
}

Player::Player(const Player& other) {
    this->id = other.id;
    this->name = other.name;
    this->score = other.score;
    this->hand = new LinkedList(*other.hand);
}

Player::~Player() {
    delete hand;
}

void Player::draw(TileBag* bag)
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        if (hand->size() < HAND_SIZE)
        {
            this->hand->add_back(bag->pop());
        }
    }
}

void Player::play(Tile tile, TileBag* tileBag, Board* board, int posX, int posY)
{
    for (int i = 0; i < hand->size(); i++)
    {
        if (hand->get(i)->equals(tile)) {
            if (board->addTile(tile, posX, posY)) {
                hand->remove(i);
                score += board->calculateScore(posX, posY);
                draw(tileBag);
            }
        }
    }

}

int Player::getPlayerID()
{
    return this->id;
};

std::string Player::getName()
{
    return this->name;
}

void Player::setName(std::string name)
{
    this->name = name;
}

LinkedList Player::getHand() {
    return *this->hand;
}

std::string Player::handToString() {
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
