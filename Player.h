#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "LinkedList.h"

class Player
{
public:
    Player();
    Player(std::string name);
    ~Player();
    void draw(LinkedList bag);
    void play(Tile tile, Board board, int posX, int posY);

    std::string getName();
    LinkedList getHand();
    int getScore();

    void setName(std::string name);
    void setHand(LinkedList hand);
    void setScore(int score);

private:
    std::string name;
    std::unique_ptr<LinkedList> hand;
    int score;
};

#endif