#include "Tile.h"
#include <iostream>

Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
};
Tile::Tile() {};
Tile::~Tile() {}
std::string Tile::toString() {
    return colour + std::to_string(shape);
};

