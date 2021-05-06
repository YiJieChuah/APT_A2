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
int Board::addTile(Tile tile, int posX, int posY)
{
    if (addTileIsValid(tile, posX, posY))
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

bool Board::addTileIsValid(Tile tileToAdd, int posX, int posY) {
    bool isValid = true;
    if (!board.at(posX).at(posY).isEmpty()) {
        isValid = false;
    }
    std::vector<Tile> tileNeighbours = getTileNearestNeighbors(posX, posY);
    for (int direction = 0; direction < NUM_DIRECTIONS; direction++)
    {
        Tile neighbour = tileNeighbours.at(direction);
        if (!neighbour.isEmpty()) {
            //  neighbour.getChain()
        }
    }

    return false;
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

std::vector<Tile> getCombo(int posX, int posY, Direction dir) {

}
