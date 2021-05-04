#include "Tile.h"
#include <vector>

#define NEIGHBORSMAXDISTANCE 26

// This is crude but much faster access to the values than if we used an array.
#include "Alphabet.h"

using namespace std;

class Board
{
protected:
    vector<std::vector<Tile> > board;

    int alphabet[26] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};

public:
    Board();
    ~Board();
    int addTile(Tile);
    Tile getTile(int *row, int *col);
    int getTile(Tile);

    /**
     * The nearest neighbors will just be added to a in class array instead of
     * being returned.
     */
    void nearestNeighbors(Tile);

    /**
     * The max number of combos is 4.
     * The max number of tiles to make a combo is 6.
     */
    int calculateScore(Tile *combo[6][4]);

    void printBoard();
    string getSaveFormat();
};