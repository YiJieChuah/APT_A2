
// #include "LinkedList.h"

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"
#include "SaveLoad.h"

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

   Player *player1 = new Player("Player1");
   Player *player2 = new Player("Player2");

   std::string currentPlayer = player1->getName();

   LinkedList *tileBag = new LinkedList();

   SaveLoad *saver = new SaveLoad();

   saver->save(*board1, "first", *player1, *player2, *tileBag, currentPlayer);

   delete board1;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}
