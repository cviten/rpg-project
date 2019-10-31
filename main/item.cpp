#include "item.h"

Item::Item() : Item("Item A", std::make_unique<HealAction>(30)) {}

Item::Item(const std::string& name = "Item A", std::unique_ptr<CharacterAction> act = std::make_unique<HealAction>(30)) : name(name), act(std::move(act)) {}

void Item::use(Character& target) { act->action(target); }
