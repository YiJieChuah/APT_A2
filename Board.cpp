#include "Board.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;

string alphabet[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

Board::Board()
{
    // Adding empty tiles to a 2d vecotr that reperesents the board.
    for (int i = 0; i < NEIGHBORSMAXDISTANCE; i++)
    {
        vector<Tile> temp;
        for (int j = 0; j < NEIGHBORSMAXDISTANCE; j++)
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

bool Board::addTile(Tile tile, int positionX, int positionY)
{
    bool added = true;

    //TODO: Use getters and setters for color and shape?
    if (board.at(positionX).at(positionY).colour == 'Z')
    {
        board.at(positionX).at(positionY).colour = tile.colour;
        board.at(positionX).at(positionY).shape = tile.shape;
        this->nearestNeighbors(tile);
        cout << "OPTION 1" << endl;
    }
    else
    {
        added = false;
    }
    return added;
}

Tile Board::getTile(int row, int col)
{
    Tile tile = board.at(row).at(col);
    return tile;
}

int Board::getTile(Tile)
{
    return 0;
}

/**
     * The nearest neighbors will just be added to a in class array instead of
     * being returned.
     */
void Board::nearestNeighbors(Tile tile)
{

    int mainTileX;
    int mainTileY;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board.at(i).at(j).colour == tile.colour && board.at(i).at(j).shape == tile.shape)
            {
                mainTileX = i;
                mainTileY = j;
            }
        }
    }

    int i = 0;
    for (int x = mainTileX; x < mainTileX + 6; x++)
    {
        if (x != NEIGHBORSMAXDISTANCE)
        {
            cout << "GOT HERE!  2.0" << endl;
            *potentialCombos[0][0] = this->getTile(x, mainTileY);
            cout << "GOT HERE!  3.0" << endl;
            i++;
        }
    }

    i = 0;
    for (int x = mainTileX; x > mainTileX - 6; x--)
    {
        if (x < 0)
        {
            *potentialCombos[1][i] = this->getTile(x, mainTileY);
        }
    }

    for (int y = mainTileY; y < mainTileY + 6; y++)
    {
        if (y != NEIGHBORSMAXDISTANCE)
        {
            *potentialCombos[2][i] = this->getTile(mainTileX, y);
        }
    }

    for (int y = mainTileY; y < mainTileY - 6; y--)
    {
        if (y < 0)
        {
            *potentialCombos[3][i] = this->getTile(mainTileX, y);
        }
    }

    // FOR TESTING ONLY!!!!
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout << potentialCombos[i][j]->colour << endl;
        }
    }
}

/**
     * The max number of combos is 4.
     * The max number of tiles to make a combo is 6.
     */
int Board::calculateScore(Tile *combo[4][6])
{
    return 0;
}

void Board::printBoard()
{
    cout << "   ";

    // Printing the column numbers.
    for (int i = 0; i < board.size(); i++)
    {
        if (i > 9)
        {
            cout << i << " ";
        }
        else
        {
            cout << i << "  ";
        }
    }
    cout << endl
         << "  ";

    // Printing the line below the comlumn numbers.
    for (int i = 0; i < board.size(); i++)
    {
        cout << "---";
    }
    cout << endl;

    for (int i = 0; i < board.size(); i++)
    {
        // Print the the first letter.
        cout << alphabet[i] << " |";
        for (int j = 0; j < board.size(); j++)
        {
            // If the tile is a exists, print it, otherwise print an empty space.
            if (board.at(i).at(j).colour != 'Z')
            {
                cout << board.at(i).at(j).getColour() << board.at(i).at(j).getShape() << "|";
            }
            else
            {
                cout << "  |";
            }
        }
        cout << endl;
    }
}
string Board::getSaveFormat()
{
    return "";
}