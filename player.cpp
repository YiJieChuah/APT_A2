#include "player.h"

#define HAND_SIZE 6

player::~player()
{
    //TODO
}

player::player()
{
   LinkedList *hand = new LinkedList();
   score = 0;
}


void player::draw(LinkedList bag) {
    for (int i = 0; i < HAND_SIZE; i ++) {
        if (hand.size() < HAND_SIZE) {
            // Adding first element of bag to the back of players hand
            this->hand.add_back(bag.get(0));
            // Removing the first element from bag
            bag.remove_front();
        }
    }   
}