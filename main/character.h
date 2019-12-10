#ifndef CHARACTER
#define CHARACTER

#include "mapobject.h"
#include "item.h"

class Container {
private:
  /* data */
  int max;
  int current;
  bool overflow;

public:
  Container (int max, bool overflow = false) : max(max), current(max), overflow(overflow) {}
  Container (int max, int current, bool overflow = false) : max(max), current(current), overflow(overflow) {}
  int getMax() const { return max; }
  int getCurrent() const { return current; }
  void give(int amount) { current = (((current + amount > max) && overflow) || (current + amount < max)) ? current + amount : max;  }
  void take(int amount) { current = (current - amount < 0) ? 0 : current - amount; }
  void changeMax(int newValue) { max = newValue; }
  void raiseMax(int amount) { max += amount; }
  // ~Container ();
};

class HPContainer : public Container {
private:
  /* data */
public:
  HPContainer (int max, bool overflow = false) : Container(max,overflow) {}
  HPContainer (int max, int current, bool overflow = false) : Container(max,current,overflow) {}
  // ~HPContainer ();
};

class MPContainer : public Container {
private:
  /* data */
public:
  MPContainer (int max, bool overflow = false) : Container(max,overflow) {}
  MPContainer (int max, int current, bool overflow = false) : Container(max,current,overflow) {}
  // ~HPContainer ();
};

// struct Stats {
//   /* data */
//   int maxHP;
//   int atk;
//   Stats(int hp, int atk) : maxHP(hp), atk(atk) {}
//   Stats() : Stats(30,15) {}
// };

class Status {
private:
  /* data */
  HPContainer hp;
  int atk;
public:
  Status(HPContainer hp = HPContainer(30), int atk = 15) : hp(hp), atk(atk) {}
  const HPContainer& getStats() const { return hp; }
  void giveHP(int amount) { hp.give(amount); }
  void takeHP(int amount) { hp.take(amount); }
  int getCurrentHP() const { return hp.getCurrent(); }
  int getAttack() const { return atk; }
  bool isDead() const { return getCurrentHP() == 0; }
};

class Character {
private:
  /* data */
  std::string name;
  Status status;

public:
  Character (const std::string& name = "Bot", Status status = Status()) : name(name), status(status) {}
  const std::string& getName() const { return name;}
  // const Stats& getStats() const { return stats; }
  const Status& getStatus() const { return status; }
  void restoreHealth(int heal) { status.giveHP(heal); }
  void takeDamage(int atk) {
    status.takeHP(atk);
    // if (status.isDead()) {
    //   // changeColor(Game::Colors::defeatedBot);
    //   // setActive(false);
    // };
  }
  // ~Character ();
};


class CharacterObject : public MapObject {
private:
  /* data */
  // std::string name;
  // Status status;
  Character character;

public:
  CharacterObject (sf::Color spriteColor = Game::Colors::bot, const std::string& name = "Bot", Status status = Status()) : MapObject(spriteColor, MapObject::MapObjectType::Char), character(name,status) {}
  const Character& getCharacter() const { return character; }
  Character& getCharacterRef() { return character; }
  bool isDead() { return character.getStatus().isDead(); }
  // const std::string& getName() const { return character.getName();}
  // // const Stats& getStats() const { return stats; }
  // const Status& getStatus() const { return character.getStatus(); }
  // void restoreHealth(int heal) { status.giveHP(heal); }
  // void takeDamage(int atk) { status.takeHP(atk); if (status.isDead()) { changeColor(Game::Colors::defeatedBot); setActive(false); }; }
  // void attack(Character& target) { target.takeDamage(getStatus().atk); }
  // ~Character ();
};

class PlayerObject : public CharacterObject {
private:
  /* data */
  // std::vector<Item> v;

public:
  PlayerObject(sf::Color spriteColor = Game::Colors::player, const std::string& name = "Player", Status status = Status()) : CharacterObject(spriteColor, name, status) {}
  // ~Character ();
};


#endif /* end of include guard: CHARACTER */
