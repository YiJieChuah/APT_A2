#include "Board.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;

string alphabet[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

Board::Board()
{
    // Adding empty tiles to a 2d vecotr that reperesents the board.
    for (int i = 0; i < BOARD_DIMENSIONS; i++)
    {
        vector<Tile> temp;
        for (int j = 0; j < BOARD_DIMENSIONS; j++)
        {
            std::unique_ptr<Tile> tile(new Tile('Z', 0));

            temp.push_back(*tile);
        }
        board.push_back(temp);
    }
}
Board::~Board()
{
}

/**
 * There cannot be duplicate tiles in a line.
 * Minimum number of point a player can score is 2.
 */
int Board::addTile(Tile tile, int positionX, int positionY)
{

    int score = 0;

    //TODO: Use getters and setters for color and shape?
    if (board.at(positionX).at(positionY).colour == 'Z')
    {
        board.at(positionX).at(positionY).colour = tile.colour;
        board.at(positionX).at(positionY).shape = tile.shape;
        this->nearestNeighbors(tile);

        score = this->calculateScore();
    }
    else
    {
        score = 0;
    }
    return score;
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

    int mainTileX = 0;
    int mainTileY = 0;
    for (unsigned int i = 0; i < board.size(); i++)
    {
        for (unsigned int j = 0; j < board.size(); j++)
        {
            if (board.at(i).at(j).colour == tile.colour && board.at(i).at(j).shape == tile.shape)
            {
                mainTileX = i;
                mainTileY = j;
            }
        }
    }

    Tile* tile1 = new Tile('Z', 0);

    int i = 0;
    for (int x = mainTileX; x < mainTileX + MAX_COMBO; x++)
    {
        //delete &potentialCombos[0][i];
        potentialCombos[0][i] = *tile1;
        if (x != BOARD_DIMENSIONS)
        {
            potentialCombos[0][i] = this->getTile(x, mainTileY);
            i++;
        }
    }

    i = 0;
    for (int x = mainTileX; x > mainTileX - MAX_COMBO; x--)
    {
        potentialCombos[1][i] = *tile1;
        if (x > 0)
        {
            potentialCombos[1][i] = this->getTile(x, mainTileY);
            i++;
        }
    }

    i = 0;
    for (int y = mainTileY; y < mainTileY + MAX_COMBO; y++)
    {
        potentialCombos[2][i] = *tile1;
        if (y != BOARD_DIMENSIONS)
        {
            potentialCombos[2][i] = this->getTile(mainTileX, y);
            i++;
        }
    }

    i = 0;
    for (int y = mainTileY; y > mainTileY - MAX_COMBO; y--)
    {
        potentialCombos[3][i] = *tile1;
        if (y > 0)
        {
            potentialCombos[3][i] = this->getTile(mainTileX, y);
            i++;
        }
    }
}

/**
     * TODO: THIS METHOD NEEDS TESTING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     *
     * The max number of combos is 4.
     * The max number of tiles to make a combo is 6.
     *
     * If this method returns 0 points then the tile was not placed on
     * the board.
     */
int Board::calculateScore()
{
    int score = 0;
    int qwirkle = 0;

    char currentColour = '\0';
    int currentShape = 0;
    bool scoreStreakBroken = false;
    bool cantPlaceTile = false;

    for (int x = 0; x < 4; x++)
    {
        qwirkle = 0;
        for (int y = 0; y < MAX_COMBO; y++)
        {
            if (y == 0)
            {
                currentColour = potentialCombos[x][y].colour;
                currentShape = potentialCombos[x][y].shape;
            }
            else if (y == 1)
            {
                if (potentialCombos[x][y].colour == currentColour)
                {
                    currentShape = 0;
                    score++;
                    qwirkle++;
                }
                else if (potentialCombos[x][y].shape == currentShape)
                {
                    currentColour = 'Z';
                    score++;
                    qwirkle++;
                }
                else if (potentialCombos[x][y].colour != 'Z')
                {
                    cantPlaceTile = true;
                }
                else
                {
                    scoreStreakBroken = true;
                }
            }
            else if (scoreStreakBroken == false)
            {
                if (potentialCombos[x][y].colour == currentColour)
                {
                    score++;
                    qwirkle++;
                }
                else if (potentialCombos[x][y].shape == currentShape)
                {
                    score++;
                    qwirkle++;
                }
                else
                {
                    scoreStreakBroken = true;
                }
            }
            if (scoreStreakBroken == true && potentialCombos[x][y].colour != 'Z')
            {
                cantPlaceTile = true;
            }
        }
        // TODO: I dont think we are supposed to print "QWIRKLE!!!" here.
        if (qwirkle == 6)
        {
            cout << "\nQWIRKLE!!!\n"
                << endl;
        }
        if (cantPlaceTile)
        {
            x = 5;
            score = 0;
        }
    }
    return score;
}

void Board::printBoard()
{
    cout << "   ";

    // Printing the column numbers.
    for (unsigned int i = 0; i < board.size(); i++)
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
        << "  -";

    // Printing the line below the comlumn numbers.
    for (unsigned int i = 0; i < board.size(); i++)
    {
        cout << "---";
    }
    cout << endl;

    for (unsigned int i = 0; i < board.size(); i++)
    {
        // Print the the first letter.
        cout << alphabet[i] << " |";
        for (unsigned int j = 0; j < board.size(); j++)
        {
            // If the tile is a exists, print it, otherwise print an empty space.
            if (board.at(i).at(j).colour != 'Z')
            {
                cout << board.at(i).at(j).colour << board.at(i).at(j).colour << "|";
            }
            else
            {
                cout << "  |";
            }
        }
        cout << endl;
    }
}
std::string Board::getSaveFormat()
{
    return "";
}