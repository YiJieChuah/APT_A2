#include "LinkedList.h"
#include "TileCodes.h"
#include <iostream>
#include <memory>

int main() {
    Tile* t1 = new Tile(RED, CIRCLE);
    Tile* t2 = new Tile(PURPLE, CIRCLE);
    Tile* t3 = new Tile(BLUE, CIRCLE);
    Tile* t4 = new Tile(GREEN, CIRCLE);
    Tile* t5 = new Tile(GREEN, STAR_4);
    LinkedList* list = new LinkedList();
    list->add_back(t1);
    list->add_front(t2);
    list->add_front(t3);
    list->add_back(t4);
    list->add_back(t5);
    std::cout << list->size() << std::endl;
    std::cout << list->toString() << std::endl;

    // list->remove_front();
    // std::cout << list->size() << std::endl;
    // std::cout << list->toString() << std::endl;

    // list->remove_back();
    // std::cout << list->size() << std::endl;
    // std::cout << list->toString() << std::endl;

    // list->remove(2);
    // std::cout << list->size() << std::endl;
    // std::cout << list->toString() << std::endl;



    return EXIT_SUCCESS;
}