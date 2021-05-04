#include "Board.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;

Board::Board()
{
    // Adding empty tiles to a 2d vecotr that reperesents the board.
    for (int i = 0; i < NEIGHBORSMAXDISTANCE; i++)
    {
        vector<Tile> temp;
        for (int j = 0; i < NEIGHBORSMAXDISTANCE; i++)
        {

            std::unique_ptr<Tile> tile(new Tile('Z', 1));

            temp.push_back(*tile);
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
    cout << "   ";

    // Printing the column numbers.
    for (int i = 0; i < board.size(); i++) {
        cout << i << "  ";
    }
    cout << endl << "  ";

    // Printing the line below the comlumn numbers.
    for (int i = 0; i < board.size(); i++) {
        cout << "---";
    }
    cout << endl;


    for (int i = 0; i < board.size(); i++)
    {
        // Print the the first letter.
        cout << alphabet[i] << " |";
        for (int j = 0; i < board.size(); i++)
        {
            // If the tile is a exists, print it, otherwise print an empty space.
            if (board.at(i).at(j).colour != 'Z') {
                cout << board.at(i).at(j).getColour() << board.at(i).at(j).getShape() << "|";
            } else {
                cout << "  |";
            }
        }
        cout << endl;
    }
}
string Board::getSaveFormat()
{
}