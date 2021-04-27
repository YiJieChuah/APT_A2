
#include "LinkedList.h"
#include "Menu.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   // LinkedList* list = new LinkedList();
   // delete list;

   // std::cout << "TODO: Implement Qwirkle!" << std::endl;

   Menu* menu = new Menu();
   menu->mainMenu();
   return 0;

   return EXIT_SUCCESS;
}
