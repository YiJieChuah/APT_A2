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

Tile::~Tile() {}

std::string Tile::toString() {
    std::string output = colour + std::to_string(shape);
    if(colour == 'R'){
        output = "\e[0;31m" + output + "\033[m";
    }
    else if(colour == 'O'){
        output = "\e[38;5;215m" + output + "\033[m";
    }
    else if(colour == 'Y'){
        output = "\e[0;33m" + output + "\033[m";
    }
    else if(colour == 'G'){
        output = "\e[0;92m" + output + "\033[m";
    }
    else if(colour == 'B'){
        output = "\e[0;34m" + output + "\033[m";
    }
    else if(colour == 'P'){
        output = "\e[0;35m" + output + "\033[m";
    }
    return output;
};

bool Tile::isEmpty() {
    bool isEmptyTile = false;
    if (this->colour == 'Z' && this->shape == 0) {
        isEmptyTile = true;
    }
    return isEmptyTile;
}

bool Tile::equals(Tile& other) {
    bool isEqual = false;
    if (this->colour == other.colour &&
        this->shape == other.shape) {
        isEqual = true;
    }
    return isEqual;
}

bool Tile::hasMatchingAttribute(Tile& other) {
    bool hasMatchingAttribute = false;
    if (this->colour == other.colour ||
        this->shape == other.shape) {
        hasMatchingAttribute = true;
    }
    return hasMatchingAttribute;
}