#include <vector>

#include "TileBag.h"

//TODO: Do we need this class?
TileBag::TileBag() {
    Colour allColours[6]{ RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };
    Shape allShapes[6]{ CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

    //temp vector to hold generated tiles
    std::vector<Tile> tilesInOrder;

    for (Colour colour : allColours) {
        for (Shape shape : allShapes) {
            tilesInOrder.push_back(Tile(colour, shape));
        }
    }

}

TileBag::~TileBag() {
    delete tiles;
}