#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>


#define BOARD_DIMENSIONS 26
#define QWIRKLE_LEN 6
#define NUM_DIMENSIONS 2

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Board
{
private:
    //2D Vector
    std::vector<std::vector<Tile>> board;
    Tile potentialCombos[4][6];

    /**
     * Returns a vector of the tile's 4 nearest neighbours.
     * Vector is sequenced NORTH, EAST, SOUTH, WEST (clockwise)
     */
    bool tileIsValid(Tile tileToAdd, int posX, int posY);
    /**
     * Expects a value defined by the enum Direction for dir
     */
    std::vector<Tile> getCombo(int posX, int posY, bool comboIsVertical);
    bool checkDupTileInCombo(Tile tile, std::vector<Tile> combo);

public:
    Board();
    ~Board();

    /**
     * Throws an "instance of char*"" error which needs to be caught if tile
     * add is invalid
     */
    void addTile(Tile tile, int positionX, int positionY);
    Tile getTile(int row, int col);
    int getTile(Tile);

    /**
     * Returns false if a neighbour is not found in the specified direction.
     * Neighbour tile passed in to be assigned.
     */
    Tile getTileNeighbour(int posX, int posY, Direction dir);

    /**
     * Returns the horizontal/vertical line which the tile at (posX,posY) is in.
     * Toggle between horizontal/vertical depending on checkVert boolean.
     */
    std::vector<Tile> getLine(int posX, int posY, bool checkVert);

    /**
     * Checks a series of tiles to see if duplicates of the specified tile
     * exist.
     */
    bool checkLineForDuplicates(std::vector<Tile> line, Tile tileToCheck);

    bool hasMatchingAttr(std::vector<Tile> line, Tile tileToCheck);

    void clearTile(int posX, int posY);

    /**
     * The max number of combos is 4.
     * The max number of tiles to make a combo is 6.
     */
    int calculateScore();
    void printBoard();
    std::string getSaveFormat();
};

#endif // BOARD_H