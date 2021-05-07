#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>
// This is crude but much faster access to the values than if we used an array.
#include "Alphabet.h"

#define BOARD_DIMENSIONS 26
#define MAX_COMBO 6
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
    void addTile(Tile tile, int positionX, int positionY);
    Tile getTile(int row, int col);
    int getTile(Tile);

    /**
     * The nearest neighbors will just be added to a in class array instead of
     * being returned.
     */
    void nearestNeighbors(Tile tile);

    std::vector<Tile> getTileNearestNeighbors(int posX, int posY);

    int convertDirToInt(Direction dir);

    /**
     * The max number of combos is 4.
     * The max number of tiles to make a combo is 6.
     */
    int calculateScore();

    void printBoard();
    std::string getSaveFormat();
};

#endif // BOARD_H