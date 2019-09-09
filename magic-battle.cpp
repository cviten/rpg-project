#include <iostream>
#include <random>

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> magic3(0,2);

struct Magic {
  enum MagicType {Fire, Water, Grass};
  /* data */
  MagicType type;
  Magic(MagicType type) : type(type) {}
};

struct Attack {
  /* data */
  Magic magic;
  Attack(Magic::MagicType type) : magic(type) {}
};

class Mage {
private:
  /* data */

public:
  // Mage ();
  Attack cast() {
    int i = magic3(rng);
    switch (i) {
      case 0: {

        return Attack(Magic::Fire);
      }
      case 2: {

        return Attack(Magic::Water);
      }
      case 1: {

        return Attack(Magic::Grass);
      }
    }
    // return Attack();
  }
  // ~Name ();
};

class BattleManager {
private:
  /* data */
  Mage m1;
  Mage m2;

public:
  // BattleManager ();
  void battle() {
    Attack a1 = m1.cast();
    Attack a2 = m2.cast();
    std::cout << "P1 casts spell " << a1.magic.type << " and P2 casts spell " << a2.magic.type << '\n';
    if (a1.magic.type == a2.magic.type) { std::cout << "Draw!" << '\n'; }
    switch (a1.magic.type) {
      case Magic::Fire:
      {
        if (a2.magic.type == Magic::Water) { std::cout << "P2 Wins!" << '\n'; }
        if (a2.magic.type == Magic::Grass) { std::cout << "P1 Wins!" << '\n'; }
        break;
      }
      case Magic::Water:
      {
        if (a2.magic.type == Magic::Grass) { std::cout << "P1 Wins!" << '\n'; }
        if (a2.magic.type == Magic::Fire) { std::cout << "P2 Wins!" << '\n'; }
        break;
      }
      case Magic::Grass:
      {
        if (a2.magic.type == Magic::Water) { std::cout << "P1 Wins!" << '\n'; }
        if (a2.magic.type == Magic::Fire) { std::cout << "P2 Wins!" << '\n'; }
        break;
      }
    }
    std::cout << "================================" << '\n';
  }
  // ~BattleManager ();
};

int main(int argc, char const *argv[]) {
  Mage m1;
  std::cout << m1.cast().magic.type  << '\n';

  BattleManager bm;
  bm.battle();
  bm.battle();
  bm.battle();
  bm.battle();
  return 0;
}
