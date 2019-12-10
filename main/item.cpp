#include "item.h"

int ItemID() {
  static int id = 0;
  return ++id;
}

Item::Item(const std::string& name = "Item A", std::unique_ptr<CharacterAction> act = std::make_unique<HealAction>(30)) : id(ItemID()), name(name), act(std::move(act)) {}

Item::Item() : Item("Item A", std::make_unique<HealAction>(30)) {}

void Item::use(Character& target) const { doAction(target, act); }
