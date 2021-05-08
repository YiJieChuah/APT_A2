
#include "GameModel.h"
#include "GameView.h"

#include <iostream>
#include <memory>

#define EXIT_SUCCESS 0

int main(void)
{
   std::shared_ptr<GameModel> gameModelPtr(new GameModel());
   std::unique_ptr<GameView> gameViewPtr(new GameView(gameModelPtr));

   gameViewPtr->init();

   return EXIT_SUCCESS;
}
