#include <iostream>

struct LevelUpPath {
  /* data */
  int hp;
  int mp;
  int atk;
  LevelUpPath(int _hp, int _mp, int _atk) : hp(_hp), mp(_mp), atk(_atk) {}
};

class CharStats {
private:
  /* data */
  int level = 1;

  int hp = 100;
  int mp = 100;
  int atk = 10;

  LevelUpPath path;

public:
  CharStats (const LevelUpPath& p) : path(p) {}
  // ~CharStats ();
  void levelup();
  void print() const;
};

void CharStats::levelup() {
  level++;

  hp += path.hp;
  mp += path.mp;
  atk += path.atk;
}

void CharStats::print() const {
  std::cout << "Bob - Lvl:" << level << " HP: " << hp << " MP: " << mp << " Atk: " << atk << '\n';
}

int main(int argc, char const *argv[]) {
  LevelUpPath war(40,5,10), mage(20,30,5);

  CharStats bob1(war);
  bob1.print();
  bob1.levelup();
  bob1.levelup();
  bob1.levelup();
  bob1.levelup();
  bob1.print();

  std::cout << "============================" << '\n';

  CharStats bob2(mage);
  bob2.print();
  bob2.levelup();
  bob2.levelup();
  bob2.levelup();
  bob2.levelup();
  bob2.print();

  std::cout << "============================" << '\n';

  CharStats bob3(war);
  bob3.print();
  for (int i = 1; i < 50; i++) {
    /* code */
    bob3.levelup();
  }
  bob3.print();
  for (int i = 1; i < 50; i++) {
    /* code */
    bob3.levelup();
  }
  bob3.print();


  return 0;
}
