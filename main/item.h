#ifndef ITEM
#define ITEM

#include "mapobject.h"

struct Item {
  /* data */
  std::string name;
  Item(const std::string& name = "Item A") : name(name) {}
};

// Add ItemContainer?

class ItemObject : public MapObject {
private:
  /* data */
  Item item;
  // std::string name;

public:
  ItemObject (Point point, sf::Color spriteColor = Game::Colors::item) : MapObject(point, spriteColor, true) {}
  const std::string& getName() const { return item.name;}
  // ~Item ();
};

#endif /* end of include guard: ITEM */
