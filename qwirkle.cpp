
// #include "LinkedList.h"

#include "Board.h"
#include "LinkedList.h"
#include "Alphabet.h"

#include <iostream>

#define EXIT_SUCCESS 0

int main(void)
{
   LinkedList *list = new LinkedList();
   delete list;

   Board *board1 = new Board();
   Tile *tile1 = new Tile('R', 4);
   Tile *tile2 = new Tile('R', 4);
   board1->addTile(*tile1, 2, 4);
   board1->addTile(*tile2, 2, 5);
   board1->printBoard();

   std::cout << board1->getSaveFormat();

   delete board1;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}
