#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "LinkedList.h"

class Player
{
public:
    Player();
    Player(std::string name);
    Player(const Player& other);
    ~Player();
    void draw(LinkedList bag);
    void play(Tile tile, LinkedList tileBag, Board board, int posX, int posY);

    std::string getName();
    LinkedList getHand();
    std::string handToString();
    int getScore();

    void setName(std::string name);
    void setHand(LinkedList hand);
    void setScore(int score);

private:
    std::string name;
    LinkedList* hand;
    int score;
};

#endif