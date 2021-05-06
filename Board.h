#include "Tile.h"
#include <vector>
// This is crude but much faster access to the values than if we used an array.
#include "Alphabet.h"

#define BOARD_DIMENSIONS 26
#define MAX_COMBO 6
#define NUM_DIRECTIONS 4

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

    bool addTileIsValid(Tile tileToAdd, int posX, int posY);
    std::vector<Tile> getCombo(int posX, int posY, Direction dir);

public:
    Board();
    ~Board();
    int addTile(Tile tile, int positionX, int positionY);
    Tile getTile(int row, int col);
    int getTile(Tile);

    /**
     * The nearest neighbors will just be added to a in class array instead of
     * being returned.
     */
    void nearestNeighbors(Tile tile);

    std::vector<Tile> getTileNearestNeighbors(int posX, int posY);

    /**
     * The max number of combos is 4.
     * The max number of tiles to make a combo is 6.
     */
    int calculateScore();

    void printBoard();
    std::string getSaveFormat();
};