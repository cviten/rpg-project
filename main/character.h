#ifndef CHARACTER
#define CHARACTER

#include "mapobject.h"
#include "item.h"

struct Stats {
  /* data */
  int maxHP;
  int atk;
  Stats(int hp, int atk) : maxHP(hp), atk(atk) {}
  Stats() : Stats(30,15) {}
};


class Character : public MapObject {
public:
  struct Status {
    Stats stats;
    int currHP;
    Status(Stats stats, int HP) : stats(stats), currHP(HP) {}
  };
private:
  /* data */
  std::string name;
  Stats stats;

  int currHP;

public:
  Character (Point point, sf::Color spriteColor = Game::Colors::bot, const std::string& name = "Bot", Stats stats = Stats()) : MapObject(point,spriteColor), name(name), stats(stats), currHP(stats.maxHP) {}
  const std::string& getName() const { return name;}
  const Stats& getStats() const { return stats; }
  Status getStatus() const { return Status(stats,currHP); }
  void restoreHealth(int heal) { int fullheal = currHP + heal; currHP = (fullheal > stats.maxHP) ? stats.maxHP : fullheal; }
  void takeDamage(int atk) { currHP -= atk; if (currHP <= 0) { changeColor(Game::Colors::defeatedBot); setActive(false); }; }
  void attack(Character& target) { target.takeDamage(getStats().atk); }
  // ~Character ();
};

class PlayerCharacter : public Character {
private:
  /* data */
  // std::vector<Item> v;

public:
  PlayerCharacter(Point point, sf::Color spriteColor = Game::Colors::player, const std::string& name = "Player", Stats stats = Stats()) : Character(point, spriteColor, name, stats) {}
  // ~Character ();
};


#endif /* end of include guard: CHARACTER */
