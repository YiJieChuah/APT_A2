#include <vector>

#include "TileBag.h"

TileBag::TileBag() {
    Colour allColours[6]{ RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };
    Shape allShapes[6]{ CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

    for (Colour colour : allColours) {
        for (Shape shape : allShapes) {
            tiles->add_back(new Tile(colour, shape));
        }
    }
    tiles->shuffle();

}

TileBag::~TileBag() {
    delete tiles;
}

Tile* TileBag::pop() {
    // Adding first element of bag to the back of players hand
    // Copied tile will belong to the player
    Tile* tile = new Tile(*tiles->get(0));
    // Removing the first element from bag
    tiles->remove_front();
    return tile;
}

int TileBag::numTilesLeft() {
    return tiles->size();
}