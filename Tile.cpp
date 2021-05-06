#include "Tile.h"
#include <iostream>


Tile::Tile() {
    // default values for empty tiles
    this->colour = 'Z';
    this->shape = 0;
}
Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
};
Tile::Tile(const Tile& other) {
    this->colour = other.colour;
    this->shape = other.shape;
};
Tile::Tile() {};
Tile::~Tile() {}

std::string Tile::toString() {
    return colour + std::to_string(shape);
};

bool Tile::isEmpty() {
    bool isEmptyTile = false;
    if (this->shape == 'Z' && this->shape == 0) {
        isEmptyTile = true;
    }
    return isEmptyTile;
}