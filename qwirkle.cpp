
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
   std::unique_ptr<Tile> tile2(new Tile(PURPLE, STAR_4));
   std::unique_ptr<Tile> tile3(new Tile(GREEN, CIRCLE));
   std::unique_ptr<Tile> tile4(new Tile(PURPLE, CIRCLE));
   std::unique_ptr<Tile> tile5(new Tile(PURPLE, DIAMOND));
   std::unique_ptr<Tile> tile6(new Tile(PURPLE, STAR_4));
   std::unique_ptr<Tile> tile7(new Tile(PURPLE, CIRCLE));

   board->addTile(*tile1, 2, 2);
   board->addTile(*tile3, 2, 4);

   //Adding tiles in between vertically
   board->addTile(*tile4, 2, 3);

   //Adding tiles horizontally
   board->addTile(*tile2, 3, 3);
   board->addTile(*tile5, 3, 5);

   //Inserting vertically again but with horizontal connections
   board->addTile(*tile7, 3, 4);

   //Adding tiles at preoccupied spot
   board->addTile(*tile1, 3, 4);

   //Adding tiles after errors
   board->addTile(*tile5, 4, 3);

   board->printBoard();

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}

