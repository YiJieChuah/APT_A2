#include "LinkedList.h"
#include <stdexcept>
#include <iostream>

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   currSize = 0;
}

LinkedList::LinkedList(const LinkedList& other) {
   head = nullptr;
   tail = nullptr;
   currSize = 0;
   for (int i = 0; i < other.size(); ++i) {
      Tile* tile = new Tile(*other.get(i));
      add_back(tile);
   }
}

LinkedList::~LinkedList() {
   clear();
}

int LinkedList::size() const {
   return currSize;
}

Tile* LinkedList::get(int index) const {
   Tile* retTile = nullptr;

   if (index >= 0 && index < size()) {

      int counter = 0;
      Node* current = head;

      while (counter < index) {
         ++counter;
         current = current->next;
      }

      retTile = current->tile;

   }
   return retTile;
}

void LinkedList::add_front(Tile* tile) {
   Node* node = new Node(tile, head, nullptr);
   head->prev = node;
   head = node;
   ++currSize;
}
void LinkedList::add_back(Tile* tile) {
   Node* node = new Node(tile, nullptr, tail);

   if (tail == nullptr) {
      head = node;
      tail = node;
   }
   else {
      tail->next = node;
      tail = node;
   }
   ++currSize;
}

void LinkedList::remove_front() {
   if (head == tail) { //one element in list
      delete head;
      head = nullptr;
      tail = nullptr;
   }
   else if (head != tail) {
      Node* toDelete = head;
      head = head->next;
      head->prev = nullptr;
      delete toDelete;
   }
   else {
      throw std::runtime_error("Nothing to remove");
   }
   --currSize;
}
void LinkedList::remove_back() {

   if (head != nullptr) {
      Node* toDelete = tail;
      tail = tail->prev;
      tail->next = nullptr;

      delete toDelete;
   }
   else {
      throw std::runtime_error("Nothing to remove");
   }
   --currSize;
}

void LinkedList::remove(int index) {
   if (index >= 0 && index < size()) {
      if (head != nullptr) {
         int counter = 0;
         Node* current = head;
         Node* prevNode = nullptr;

         while (counter != index) {
            ++counter;
            prevNode = current;
            current = current->next;
         }

         if (prevNode == nullptr) {
            remove_front();
         }
         else if (current->next == nullptr) {
            remove_back();
         }
         else {
            prevNode->next = current->next;
            current->next->prev = prevNode;
            delete current;
            --currSize;
         }

      }
   }
}

void LinkedList::clear() {
   while (head != nullptr) {
      remove_front();
   }
}

void LinkedList::shuffle() {
   // IMPORTANT NOTE FOR MARKER:
   // Static seed set for reliably testing save methods that don't load files
   srand(RAND_SEED);
   // Switch to actual randomness by uncommenting line below, comment line above
   // and recompile
   // srand(time(NULL));
   for (int i = 0; i < currSize; i++)
   {
      int randNum = std::rand() % currSize;
      this->add_back(new Tile(*this->get(randNum)));
      this->remove(randNum);
   }
}


std::string LinkedList::toString() {
   std::string retStr = "";
   if (head != nullptr) {
      Node* current = head;

      while (current != nullptr) {
         retStr += current->tile->toString() + " ";
         current = current->next;
      }
   }
   return retStr;
}