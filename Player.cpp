#include <memory>

#include "Player.h"
#include "Board.h"

#define HAND_SIZE 6



Player::Player() {}

Player::Player(std::string name)
{
    this->name = name;
    this->score = 0;
    hand = new LinkedList();
}

Player::Player(const Player& other) {
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
            hand->add_back(bag->pop());
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
        handStr += hand->get(i)->colour;
        handStr += hand->get(i)->shape;
        if (i != hand->size())
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
