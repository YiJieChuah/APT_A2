
#include "LinkedList.h"

#include "Board.cpp"

#include "Alphabet.h"

#include <iostream>

#define EXIT_SUCCESS 0

int main(void)
{
   LinkedList *list = new LinkedList();
   delete list;

   Board *board1 = new Board();
   Tile *tile = new Tile('R', 4);
   board1->addTile(*tile, E, 4);
   board1->printBoard();

   delete board1;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}
