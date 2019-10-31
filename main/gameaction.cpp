#include "gameaction.h"

void HealAction::action(Character& target) const {
  target.restoreHealth(healAmount);
  std::cout << "Healed " << target.getName() << '\n';
}

void DamageAction::action(Character& target) const {
  target.takeDamage(damageAmount);
}
