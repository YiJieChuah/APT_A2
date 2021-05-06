#include "Tile.h"
#include <vector>

#define BOARD_DIMENSIONS 26
#define MAX_COMBO 6

// This is crude but much faster access to the values than if we used an array.
#include "Alphabet.h"

class Board
{
protected:
    //2D Vector
    std::vector<std::vector<Tile>> board;
    Tile potentialCombos[4][6];

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

    /**
     * The max number of combos is 4.
     * The max number of tiles to make a combo is 6.
     */
    int calculateScore();

    void printBoard();
    std::string getSaveFormat();
};