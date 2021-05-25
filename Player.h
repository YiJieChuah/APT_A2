#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "TileBag.h"

class Player
{
public:
    Player();
    Player(std::string name);
    Player(std::string name, int score, LinkedList* hand);
    Player(const Player& other);
    ~Player();
    void draw(TileBag* bag);
    void play(Tile tile, TileBag* tileBag, Board* board, int posX, int posY);
    // void updateScore(int posX, int posY, Board* board);
    void updateScore(int scored);
    void replace(Tile tile, TileBag* tileBag);

    /**
     * @return -1 if no such tile is found and the index of the tile in the hand
     * if it is found.
     */
    int findTileInHand(Tile tile);

    int getPlayerID();
    std::string getName();
    LinkedList* getHand();
    std::string handToString();
    int getScore();

    void setName(std::string name);
    void setHand(LinkedList* hand);
    void setScore(int score);

    void addTileToHand(Tile* tile);

private:
    std::string name;
    int score;
    LinkedList* hand;
};

#endif