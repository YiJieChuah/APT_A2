#include "Player.h"

#define HAND_SIZE 6

Player::~Player()
{
    //TODO
}

Player::Player() {

}
Player::Player(std::string name)
{
    this->name = name;
    // LinkedList *hand = new LinkedList();
    // score = 0;
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

std::string Player::getName() {
    return this->name;
}
LinkedList Player::getHand() {
    return this->hand;
}
int Player::getScore() {
    return this->score;
}
