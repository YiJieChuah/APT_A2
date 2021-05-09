#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include "TileCodes.h"
#include "Tile.h"
#include "LinkedList.h"

class TileBag {
private:
    LinkedList* tiles = new LinkedList();
public:
    TileBag();
    ~TileBag();

    Tile* pop();
    int numTilesLeft();
};


#endif //ASSIGN2_TILEBAG_H