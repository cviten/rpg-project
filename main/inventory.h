#ifndef INVENTORY
#define INVENTORY

#include <vector>

#include "item.h"

struct InventoryItem {
  Item item;
  int count;
};

class Invetory {
private:
  /* data */
  std::vector<InventoryItem> invetory;

public:
  Invetory ();
  // ~Invetory ();
};


#endif /* end of include guard: INVENTORY */
