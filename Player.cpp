#include <memory>

#include "Player.h"

#define HAND_SIZE 6

Player::~Player()
{
    //TODO
}

Player::Player()
{
}

Player::Player(std::string name)
{
    this->name = name;
    std::unique_ptr<LinkedList> hand();
    score = 0;
}

void Player::draw(LinkedList bag)
{
    for (int i = 0; i < HAND_SIZE; i++)
    {
        if (hand.size() < HAND_SIZE)
        {
            // Adding first element of bag to the back of players hand
            this->hand.add_back(bag.get(0));
            // Removing the first element from bag
            bag.remove_front();
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

LinkedList Player::getHand()
{
    return this->hand;
}

void Player::setHand(LinkedList hand)
{
    this->hand = hand;
}

int Player::getScore()
{
    return this->score;
}

void Player::setScore(int score)
{
    this->score = score;
}
