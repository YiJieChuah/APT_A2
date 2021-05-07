
// #include "LinkedList.h"

#include "Board.h"
#include "LinkedList.h"
#include "TileCodes.h"

#include <iostream>
#include <memory>

#define EXIT_SUCCESS 0

int main(void)
{
   LinkedList* list = new LinkedList();
   delete list;

   std::unique_ptr<Board> board(new Board());
   std::unique_ptr<Tile> tile1(new Tile(RED, CIRCLE));
   std::unique_ptr<Tile> tile2(new Tile(RED, STAR_4));
   std::unique_ptr<Tile> tile3(new Tile(GREEN, CLOVER));

   board->addTile(*tile1, 0, 0);
   board->addTile(*tile2, 1, 0);
   board->addTile(*tile3, 0, 1);

   // try {
      // board1->addTile(*tile2, 2, 4); //Adding a pre-occupied tile
   // }
   // catch (const char* message) {
   //    std::cerr << message << std::endl;
   // }
   std::vector<Tile> vertline = board->getLine(0, 0, true);
   for (Tile tile : vertline)
      std::cout << tile.toString() << std::endl;
   std::cout << vertline.size() << std::endl;
   std::cout << "" << std::endl;

   std::vector<Tile> horline = board->getLine(0, 0, false);
   for (Tile tile : horline)
      std::cout << tile.toString() << std::endl;
   std::cout << horline.size() << std::endl;


   board->printBoard();

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}

