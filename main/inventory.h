#ifndef INVENTORY
#define INVENTORY

#include <vector>

#include <iostream>
// #include <fstream>
// #include <vector>
#include <algorithm>

// Recipe class
// #include <initializer_list>

#include "item.h"

struct InventoryItem {
  int itemID;
  int count;
};

class Invetory {
private:
  /* data */
  std::vector<InventoryItem> invetory;

  std::vector<InvItem>::iterator findItem(Item item)
  void eraseItem(std::vector<InvItem>::iterator it)
public:
  Invetory ();
  // ~Invetory ();
  void addItem(Item item);
  void show() const;
  void use(Item item);
  std::vector<bool> checkList(const std::vector<InvItem> &recipe) const;
};

// class Recipe {
// private:
//   std::vector<InvItem> recipe;
//
// public:
//   Recipe (const std::vector<InvItem> &r);
//   // ~Recipe ();
//   Recipe (std::initializer_list<InvItem> list);
//   bool checkInv(const Inventory &inv) const;
//   void show() const;
// };


#endif /* end of include guard: INVENTORY */
