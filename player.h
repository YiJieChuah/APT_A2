#ifndef PLAYER_H
#define PLAYER_H

#include "LinkedList.h"

class Player
{
public:

    Player();
    Player(std::string name);
    ~Player();
    void draw(LinkedList bag);

    std::string getName();
    LinkedList getHand();
    int getScore();

private:
    std::string name;
    LinkedList hand;
    int score;

};

#endif