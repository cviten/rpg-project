#include "gameaction.h"

void doAction(Character& target, const CharacterAction& act) {
  act.action(target);
}

void doAction(Character& target, const std::unique_ptr<CharacterAction>& act) {
  act->action(target);
}

void doAction(CharacterObject& target, const CharacterAction& act) {
  act.action(target);
}

void doAction(CharacterObject& target, const std::unique_ptr<CharacterAction>& act) {
  act->action(target);
}

void CharacterAction::action(CharacterObject& target) const {
  action(target.getCharacterRef());
}

// --------

void NullAction::action(Character& target) const {
  std::cout << "No effect on " << target.getName() << '\n';
}

void MoveAction::action(Character& target) const {
  // target.move(x,y);
  throw GameActionException("Invalid action for the character");
}
void MoveAction::action(CharacterObject& target) const {
  target.move(x,y);
}

void HealAction::action(Character& target) const {
  target.restoreHealth(healAmount);
  std::cout << target.getName() << " is healed for " << healAmount << " HP" << '\n';
}

void DamageAction::action(Character& target) const {
  target.takeDamage(damageAmount);
  std::cout << target.getName() << " took " << damageAmount << " damage"  << '\n';
}

void GetItemAction::action(Character& target) const {
  std::cout << target.getName() << " got Item" << " (need to think about this function)" << '\n';
}
