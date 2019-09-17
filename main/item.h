#ifndef ITEM
#define ITEM

#include "mapobject.h"

struct Item {
  /* data */
  std::string name;
};

class ItemMap : public MapObject {
private:
  /* data */
  std::string name;

public:
  ItemMap (Point point, sf::Color spriteColor = Game::Colors::item, const std::string& name = "Item A") : MapObject(point, spriteColor, true), name(name) {}
  const std::string& getName() const { return name;}
  // ~Item ();
};

#endif /* end of include guard: ITEM */
