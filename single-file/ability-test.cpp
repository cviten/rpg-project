#include <iostream>

class Action {
private:
  /* data */

public:
  Action ();
  // ~Action ();
};

class DamageAction : public Action {};
class StatusEffectAction : public Action {};
class HealAction : public Action {};
// class Name {};

// class NullAction : public Action {
// private:
//   /* data */
//
// public:
//   NullAction ();
//   // ~NullAction ();
// };

class Ability {
private:
  /* data */
  std::string name
  std::string desc

public:
  Ability ();
  // ~Ability ();
};

class ActiveAbility : public Ability {
private:
  /* data */
  int cost;

public:
  ActiveAbility ();
  // ~ActiveAbility ();
};

class PassiveAbility : public Ability {
public:
  enum Type { Preturn, Movement, Battle, PostTurn  };
private:
  /* data */

public:
  PassiveAbility ();
  // ~PassiveAbility ();
};

class Character {
private:
  Stats stats
  /* data */

  // std::vector<ActiveAbility> sidebar
  // std::vector<PassiveAbility> passAbil;;

public:
  Character ();
  // ~Character ();
};

void GameManager::getPassiveAbilityList(const Character& caster) {

}

void GameManager::actActiveAbility(Character& caster, ActiveAbility abil, Character& target) {

}

int main(int argc, char const *argv[]) {

  return 0;
}
