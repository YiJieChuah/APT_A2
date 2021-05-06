#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "LinkedList.h"

class Player
{
private:
    std::string name;
    LinkedList hand;
public:
    std::string getName();
    LinkedList getHand();

};

#endif // PLAYER_H