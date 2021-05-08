
#include "GameModel.h"
#include "GameView.h"

#include <iostream>
#include <memory>

#define EXIT_SUCCESS 0

int main(void)
{
   GameModel* gameModelPtr = new GameModel();
   GameView* gameViewPtr = new GameView(gameModelPtr);

   gameViewPtr->init();

   delete gameModelPtr;
   delete gameViewPtr;
   return EXIT_SUCCESS;
}
