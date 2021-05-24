
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

#include "TileCodes.h"

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
public:
   Colour colour;
   Shape shape;


   Tile();
   Tile(Colour colour, Shape shape);
   Tile(const Tile& other);
   ~Tile();


   std::string toString();
   bool isEmpty();
   bool equals(Tile& other);
   bool hasMatchingAttribute(Tile& other);
};

#endif // ASSIGN2_TILE_H
