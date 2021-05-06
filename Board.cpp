
#include "Board.h"

#include <iostream>
#include <string>
#include <memory>

Board::Board()
{
    // Adding empty tiles to a 2d vector that reperesents the board.
    for (int row = 0; row < BOARD_DIMENSIONS; row++)
    {
        std::vector<Tile> boardRow(BOARD_DIMENSIONS, Tile());
        board.push_back(boardRow);
    }
}


Board::~Board() {}

/**
 * There cannot be duplicate tiles in a line.
 * Minimum number of point a player can score is 2.
 */
void Board::addTile(Tile tile, int posX, int posY)
{
    if (tileIsValid(tile, posX, posY))
    {
        board.at(posX).at(posY).colour = tile.colour;
        board.at(posX).at(posY).shape = tile.shape;
    }
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

bool Board::tileIsValid(Tile tileToAdd, int posX, int posY) {
    bool isValid = true;

    // Check if position already has a tile
    if (!board.at(posX).at(posY).isEmpty()) {
        isValid = false;
    }
    // Explore combos to see if any duplicates present
    std::vector<Tile> horiCombo = getCombo(posX, posY, false);
    std::vector<Tile> vertCombo = getCombo(posX, posY, true);
    bool horiHasDup = checkDupTileInCombo(tileToAdd, horiCombo);
    bool vertHasDup = checkDupTileInCombo(tileToAdd, vertCombo);
    if (horiHasDup || vertHasDup) {
        isValid = false;
    }

    //Check if matching adjacent nodes
    if (horiCombo.size() > 0) {
        //TODO: Some magic numbers here.
        if (!tileToAdd.hasMatchingAttribute(horiCombo.at(1)))
        {
            isValid = false;
        };
    }

    if (vertCombo.size() > 0) {
        //TODO: Some magic numbers here.
        if (!tileToAdd.hasMatchingAttribute(vertCombo.at(1)))
        {
            isValid = false;
        };
    }

    return isValid;
}

/**
 * Returns a vector of the tile's 4 nearest neighbours.
 * Vector is sequenced NORTH, EAST, SOUTH, WEST (clockwise)
 */
std::vector<Tile> Board::getTileNearestNeighbors(int posX, int posY) {
    std::vector<Tile> neighbours(4);
    neighbours.push_back(board.at(posX).at(posY - 1)); //NORTH
    neighbours.push_back(board.at(posX + 1).at(posY)); //EAST
    neighbours.push_back(board.at(posX).at(posY - 1)); //SOUTH
    neighbours.push_back(board.at(posX - 1).at(posY)); //WEST

    return neighbours;
};

/**
 * Expects a value defined by the enum Direction for dir
 */
std::vector<Tile> Board::getCombo(int posX, int posY, bool comboIsVertical) {
    std::vector<Tile> combo;

    if (comboIsVertical) {
        int currPosY = posY;
        Tile currTile = board.at(posX).at(currPosY);
        //Traverse upwards to find combo
        while (!currTile.isEmpty()) {
            ++currPosY;
            currTile = board.at(posX).at(currPosY);
            combo.push_back(currTile);
        }

        //Reset position before traversing downwards
        currPosY = posY;
        //Traverse downwards to find combo
        while (!currTile.isEmpty()) {
            --currPosY;
            currTile = board.at(posX).at(currPosY);
            combo.push_back(currTile);
        }
    }

    else if (!comboIsVertical) {
        int currPosX = posX;
        Tile currTile = board.at(currPosX).at(posY);
        //Traverse right to find combo

        while (!currTile.isEmpty()) {
            ++currPosX;
            currTile = board.at(posX).at(currPosX);
            combo.push_back(currTile);
        }

        //Reset position before traversing downwards
        currPosX = posX;
        //Traverse left to find combo
        while (!currTile.isEmpty()) {
            --currPosX;
            currTile = board.at(posX).at(currPosX);
            combo.push_back(currTile);
        }
    }
    return combo;
}

bool Board::checkDupTileInCombo(Tile tile, std::vector<Tile> combo) {
    bool dupPresent = false;
    for (unsigned int tileIdx = 0; tileIdx < combo.size(); tileIdx++)
    {
        if (tile.equals(combo.at(tileIdx))) {
            dupPresent = true;
        }
    }
    return dupPresent;
};

void Board::printBoard()
{
    std::cout << "   ";
    // Printing the column numbers.
    for (int i = 0; i < BOARD_DIMENSIONS; i++)
    {
        if (i > 9)
        {
            std::cout << i << " ";
        }
        else
        {
            std::cout << i << "  ";
        }
    }
    std::cout << std::endl
        << "  -";

    // Printing the line below the comlumn numbers.
    for (int i = 0; i < BOARD_DIMENSIONS; i++)
    {
        std::cout << "---";
    }
    std::cout << std::endl;

    char alphabet = 'A';
    for (int i = 0; i < BOARD_DIMENSIONS; i++)
    {
        // Print the the first letter.
        std::cout << alphabet++ << " |";
        for (int j = 0; j < BOARD_DIMENSIONS; j++)
        {
            // If the tile is a exists, print it, otherwise print an empty space.
            if (board.at(i).at(j).colour != 'Z')
            {
                std::cout << board.at(i).at(j).colour << board.at(i).at(j).colour << "|";
            }
            else
            {
                std::cout << "  |";
            }
        }
        std::cout << std::endl;
    }
}
