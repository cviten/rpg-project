#include <iostream>
#include <memory>

struct Stats {
  int maxHP = 20;
  int maxMP = 15;
  int atk = 5;
  Stats() = default;
  Stats(int _hp, int _mp, int _atk) : maxHP(_hp), maxMP(_mp), atk(_atk) {}
};

class Character;

class Skill {
private:
  /* data */
  int cost = 10;

public:
  // ActiveAbility ();
  int getCost() const { return cost; }
  virtual void use(Character& target) = 0;
  // ~ActiveAbility ();
};

class Damage : public Skill {
private:
  /* data */

public:
  // Damage ();
  // void use(Character& target) { target.takeDamage(15); }
  void use(Character& target);
  // ~Damage ();
};

class Heal : public Skill {
private:
  /* data */

public:
  // Heal ();
  // void use(Character& target) { target.takeDamage(-10); }
  void use(Character& target);
  // ~Heal ();
};

class Character {
private:
  /* data */
  Stats stats;
  std::string name;
  int hp;
  int mp;

  // ActiveAbility act;
  std::unique_ptr<Skill> act;

public:
  // Character (const std::string& _name) : name(_name), hp(stats.maxHP), mp(stats.maxMP) {act.reset(new Damage());};
  // Character (const std::string& _name) : name(_name), hp(stats.maxHP), mp(stats.maxMP) {act.reset(new Damage());};
  Character (const std::string& _name, Stats st = Stats()) : stats(st), name(_name), hp(stats.maxHP), mp(stats.maxMP) {act.reset(new Damage());};
  // ~Character () { delete act;}


  // Debug
  void takeDamage(int damage);
  void takeMana(int cost);
  void restore();
  void print() const;
  void use(Character& target);
  Skill* getSkill() const;
};


class BattleManager {
private:
  /* data */
  Character p1;
  Character p2;


public:
  BattleManager () : p1("Bob"), p2("Dummy" ,Stats(100,0,0)) {}
  void p1use();
  void status() const;
  // ~BattleManager ();
};

void Character::takeDamage(int damage) { hp -= damage; }
void Character::takeMana(int cost) { mp -= cost; }
void Character::restore() { hp = stats.maxHP; mp = stats.maxMP; }
void Character::print() const { std::cout << name << " - HP: " << hp << "  MP: " << mp << '\n';}
// void Character::use(Character& target) { act->use(target); }
void Character::use(Character& target) { }
Skill* Character::getSkill() const { return act.get(); }


void Damage::use(Character& target) { target.takeDamage(30); }
void Heal::use(Character& target) { target.takeDamage(-10); }

void BattleManager::p1use() {
  auto s = p1.getSkill();
  p1.takeMana(s->getCost());
  s->use(p2);
}

void BattleManager::status() const {
  std::cout << "=================" << '\n';
  p1.print();
  p2.print();
}

int main(int argc, char const *argv[]) {
  // Stats dstats(100,0,0);
  // Character bob("Bob"), dummy("Dummy", dstats);

  BattleManager bm;
  bm.status();
  bm.p1use();
  bm.status();


  // dummy.print();
  // bob.use(dummy);
  // dummy.print();
  // dummy.takeDamage(5);
  // dummy.print();
  // dummy.restore();
  // dummy.print();


  return 0;
}
