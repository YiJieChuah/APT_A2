
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
public:

   //TODO: Private or not private?
   Colour colour;
   Shape shape;

   Tile(Colour colour, Shape shape);
   Tile(Tile& other);
   Tile();
   ~Tile();
   std::string toString();

}
;

#endif // ASSIGN2_TILE_H
