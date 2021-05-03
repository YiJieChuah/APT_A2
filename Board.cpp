#include "Board.h"

#include <iostream>
#include <string>

using namespace std;

Board::Board()
{
    for (int i = 0; i < NEIGHBORSMAXDISTANCE; i++)
    {
        vector<Tile> temp;
        for (int j = 0; i < NEIGHBORSMAXDISTANCE; i++)
        {
            Tile *tempTile = new Tile('Z', 0);

            std::unique_ptr<Tile> tile(new Tile('Z', 1));

            temp.push_back(*tempTile);
        }
        board.push_back(temp);
    }
}
Board::~Board()
{
}
int Board::addTile(Tile)
{
}
Tile Board::getTile(int *row, int *col)
{
}
int Board::getTile(Tile)
{
}

/**
     * The nearest neighbors will just be added to a in class array instead of
     * being returned.
     */
void Board::nearestNeighbors(Tile)
{
}

/**
     * The max number of combos is 4.
     * The max number of tiles to make a combo is 6.
     */
int Board::calculateScore(Tile *combo[6][4])
{
}

void Board::printBoard()
{
    for (int i = 0; i < board.size(); i++)
    {
        vector<Tile> temp;
        for (int j = 0; i < board.size(); i++)
        {
            Tile *tempTile = new Tile('Z', 0);
            temp.push_back(*tempTile);
        }
        board.push_back(temp);
    }
}
string Board::getSaveFormat()
{
}