
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   LinkedList(LinkedList& other);
   ~LinkedList();

   int size();
   Tile* get(int index);

   void add_front(Tile* tile);
   void add_back(Tile* tile);

   void remove_front();
   void remove_back();

   void remove(int index);

   void clear();

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
