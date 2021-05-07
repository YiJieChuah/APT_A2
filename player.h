#ifndef PLAYER_H
#define PLAYER_H

#include "LinkedList.h"

class player
{
public:
    player();
    ~player();
    void draw(LinkedList bag);

private:
    LinkedList hand;
    int score;
};

#endif