#ifndef GAMEACTION
#define GAMEACTION

#include "character.h"
#include <iostream>

class Character;

class GameAction {
private:
  /* data */
  // virtual void action() = 0;
public:
  // GameAction ();
  // void operator()() { action(); }
  // ~GameAction ();
};

class CharacterAction : public GameAction {
private:
  /* data */
  // Character& target;

public:
  // CharacterAction ();
  virtual void action(Character& target) const = 0;
  // ~CharacterAction ();
};

class NullAction : public CharacterAction {
public:
  // NullAction () : NullAction() {}
  void action(Character& target) const override;
  // ~HealAction ();
};

class MoveAction : public CharacterAction {
private:
  /* data */
  int x, y;

public:
  MoveAction (int x, int y) : x(x), y(y) {}
  void action(Character& target) const override;
  // ~MoveAction ();
};

class HealAction : public CharacterAction {
private:
  /* data */
  int healAmount;

public:
  HealAction (int healAmount) : healAmount(healAmount) {}
  void action(Character& target) const override;
  // ~HealAction ();
};

class DamageAction : public CharacterAction {
private:
  /* data */
  int damageAmount;

public:
  DamageAction (int damageAmount) : damageAmount(damageAmount) {}
  void action(Character& target) const override;
  // ~HealAction ();
};

class GetItemAction : public CharacterAction {
private:
  /* data */

public:
  // GetItemAction () {}
  void action(Character& target) const override;
  // ~GetItemAction ();
};

void doAction(Character& target, const CharacterAction& action);
void doAction(Character& target, const std::unique_ptr<CharacterAction>& action);
// namespace Actions {
//   const NullAction null;
//   const HealAction heal(30);
//   const DamageAction damage(50);
// } /* Actions */



#endif /* end of include guard: GAMEACTION */
