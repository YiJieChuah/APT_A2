#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "TileBag.h"

class Player
{
public:
    Player();
    Player(int id, std::string name);
    Player(const Player& other);
    ~Player();
    void draw(TileBag* bag);
    void play(Tile tile, TileBag* tileBag, Board* board, int posX, int posY);

    int getPlayerID();
    std::string getName();
    LinkedList getHand();
    std::string handToString();
    int getScore();

    void setName(std::string name);
    void setHand(LinkedList hand);
    void setScore(int score);

private:
    int id;
    std::string name;
    LinkedList* hand;
    int score;
};

#endif