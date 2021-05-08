
#include "GameModel.h"
#include "GameView.h"

#include <iostream>
#include <memory>

#define EXIT_SUCCESS 0

int main(void)
{
   std::unique_ptr<GameModel> gameModel;
   std::unique_ptr<GameView> gameView;

   gameView->init();

   return EXIT_SUCCESS;
}
