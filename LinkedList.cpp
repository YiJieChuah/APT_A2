#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList() {
   head = nullptr;
   currSize = 0;
}

LinkedList::LinkedList(LinkedList& other) {
   head = nullptr;
   this->currSize = other.size();
   for (int i = 0; i < other.size(); ++i) {
      Tile* tile = new Tile(*other.get(i));
      add_back(tile);
   }
}
LinkedList::~LinkedList() {
   clear();
}

int LinkedList::size() {
   return currSize;
}

Tile* LinkedList::get(int index) {
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
   Node* node = new Node(tile, head);
   head = node;
   ++currSize;
}
void LinkedList::add_back(Tile* tile) {
   Node* node = new Node(tile, nullptr);

   if (head == nullptr) {
      head = node;
   }
   else {
      Node* current = head;
      while (current->next != nullptr) {
         current = current->next;
      }
      current->next = node;
   }
   ++currSize;
}

void LinkedList::remove_front() {
   if (head != nullptr) {
      Node* toDelete = head;
      head = head->next;

      delete toDelete->tile;
      delete toDelete;
   }
   else {
      throw std::runtime_error("Nothing to remove");
   }
   --currSize;
}
void LinkedList::remove_back() {

   if (head != nullptr) {
      Node* current = head;
      //pre should point to node before current;
      Node* prev = nullptr;

      while (current->next != nullptr) {
         prev = current;
         current = current->next;
      }

      if (prev == nullptr) {
         head = nullptr;
      }
      else {
         prev->next = nullptr;
      }

      delete current->tile;
      delete current;
   }
   --currSize;
}

void LinkedList::remove(int index) {
   if (index >= 0 && index < size()) {
      if (head != nullptr) {
         int counter = 0;
         Node* current = head;
         //pre should point to node before current;
         Node* prev = nullptr;

         while (counter != index) {
            ++counter;
            prev = current;
            current = current->next;
         }

         if (prev == nullptr) {
            head = current->next;
         }
         else {
            prev->next = current->next;
         }
         --currSize;

         delete current->tile;
         delete current;
      }
   }
}

void LinkedList::clear() {
   while (head != nullptr) {
      remove_front();
   }
   currSize = 0;
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