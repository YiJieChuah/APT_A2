#include <memory>

#include "Player.h"
#include "Board.h"

#define HAND_SIZE 6



Player::Player() {}

Player::Player(std::string name)
{
    this->name = name;
    score = 0;
}

Player::Player(const Player& other) {
    this->name = other.name;
    this->score = other.score;
    this->hand = new LinkedList(*other.hand);
}

Player::~Player() {
    delete hand;
}

void Player::draw(LinkedList bag)
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        if (hand->size() < HAND_SIZE)
        {
            // Adding first element of bag to the back of players hand
            hand->add_back(bag.get(0));
            // Removing the first element from bag
            bag.remove_front();
        }
    }
}

void Player::play(Tile tile, Board board, int posX, int posY)
{
    for (int i = 0; i < hand->size(); i++)
    {
        if (hand->get(i)->equals(tile)) {
            if (board.addTile(tile, posX, posY)) {
                hand->remove(i);
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

int Player::getScore()
{
    return this->score;
}

void Player::setScore(int score)
{
    this->score = score;
}
