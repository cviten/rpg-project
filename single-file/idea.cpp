#include <iostream>
#include <vector>

struct Stats {
  /* data */
  int maxhp;
  int maxmp;
  int physatk;
  int physdef;
  int magatk;
  int physdef;
  int speed;
};


struct Damage {
  enum DamageType { Physical, Magic, Direct};
  struct MagicDamage {
    /* data */
    enum Type { None, Fire, Water  };
    Type type {None};
    MagicDamage() {};
    MagicDamage(Type t) : type(t) {}
  };
  struct PhysicalDamage {
    /* data */
    // enum PhysicalType { None. Sword, Spear  };
    enum Type { None, Sword, Spear  };
    Type type { None };
    PhysicalDamage() {}
    PhysicalDamage(Type t) : type(t) {}
  };
  //------------------
  DamageType type;
  MagicDamage magdam;
  PhysicalDamage physdam;
  int amount;

  friend Damage PhysicalAttack(int pow, PhysicalDamage pd);
  friend Damage MagicAttack(int pow, MagicDamage pd);
  friend Damage DirectAttack(int pow);

protected:
  Damage(DamageType t, int pow) : type(t), amount(pow) {}
  Damage(DamageType t, int pow, MagicDamage md, PhysicalDamage pd) : type(t), amount(pow) {
    if (type == Physical) {
      physdam = pd;
    } else if (type == Magic) {
      magdam = md;
    }
  }
};

Damage PhysicalAttack(int pow, Damage::PhysicalDamage pd) {
  return Damage(Damage::Physical, pow, pd)
}

Damage MagicAttack(int pow, Damage::MagicDamage pd) {
  return Damage(Damage::Magic, pow, md)
}

Damage DirectAttack(int pow) {
  return Damage(Damage::Direct, pow)
}

struct Buff {
  /* data */
  int& stat;
  float power;
  int duration;
};

struct Support {
  /* data */
};

struct Action {
  /* data */
  // Damage part
  int power;
  Damage::DamageType type;
  Damage::MagicDamage::Type mt;
  Damage::PhysicalDamage::Type pt;
  // Buff/Debuff part

  // Status part
};

struct CurrentStatus {
  /* data */
  Stats stats;
  int currhp, currmp;
};

struct AI {
  /* data */
  const Action& takeAction(CurrentStatus status, const std::vector<Action> &moveset) {

  }
};

class Character {
private:
  /* data */
  Stats stats;
  AI ai;
  std::vector<Action> moveset;

public:
  Character ();
  // ~Character ();
};

int main(int argc, char const *argv[]) {
  // Damage1 d1;
  // Damage2 d2;

  std::vector<Action> moveset;

  // struct enumst {
  //   enum e { a,b,c };
  //   e t;
  // };
  //
  // enum d { a,b,c };
  // enumst m;
  // d h;
  // std::cout << "size of Damage1: " << (sizeof m) << '\n';
  // std::cout << "size of Damage2: " << (sizeof h) << '\n';
  return 0;
}

// struct A {
//   /* data */
// };
//
// struct B1 : A {
//   /* data */
// };
//
// struct B2 : A {
//   /* data */
// };
//
// void fa(const A &a) {
//   /* code */
// }
//
// void fb1(const B1 &b) {
//   /* code */
// }
//
// int main(int argc, char const *argv[]) {
//   /* code */
//   A a;
//   B1 b1;
//   B2 b2;
//   fa(a);
//   fa(b1);
//   fa(b2);
//   fb1(b1);
//   return 0;
// }
