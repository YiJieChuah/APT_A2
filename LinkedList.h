
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#define RAND_SEED 100

#include "Node.h"

class LinkedList
{
public:
   LinkedList();
   LinkedList(const LinkedList& other);
   ~LinkedList();

   int size() const;
   Tile* get(int index) const;

   void add_front(Tile* tile);
   void add_back(Tile* tile);

   void remove_front();
   void remove_back();

   void remove(int index);
   std::string toString();

   void shuffle();

   void clear();

private:
   Node* head;
   Node* tail;
   int currSize;
};

#endif // ASSIGN2_LINKEDLIST_H
