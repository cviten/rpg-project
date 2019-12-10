#ifndef ITEM
#define ITEM

#include "mapobject.h"
#include "character.h"
#include "gameaction.h"

// class ItemAction {
// private:
//   /* data */
//   virtual void action() = 0;
// public:
//   ItemAction ();
//   void operator()() { action(); }
//   // ~ItemAction ();
// };

class Character;
class CharacterAction;

class Item {
private:
  /* data */
  int id;
  std::string name;
  // ItemAction act;
  // const CharacterAction* act;
  std::unique_ptr<CharacterAction> act;
public:
  // Work on NullAction()
  Item();
  Item(const std::string& name, std::unique_ptr<CharacterAction> act);
  // Item(const std::string& name = "Item A", std::unique_ptr<CharacterAction> act = std::make_unique<HealAction>(30)) : name(name), act(std::move(act)) {}
  const std::string& getName() const { return name; }
  const int& getID() const { return id; }
  void use(Character& target) const;
};

// Add ItemContainer?

class ItemObject : public MapObject {
private:
  /* data */
  Item item;
  // std::string name;

public:
  ItemObject (sf::Color spriteColor = Game::Colors::item) : MapObject(spriteColor, MapObject::MapObjectType::Item, true) {}
  const std::string& getName() const { return item.getName(); }
  Item& getItem() { return item; }
  // ~Item ();
};

#endif /* end of include guard: ITEM */
