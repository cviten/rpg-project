#ifndef INFOWINDOW
#define INFOWINDOW

#include "./SFML-imgui/imgui.h"
#include "./SFML-imgui/imgui-SFML.h"

#include "common.h"

struct CharacterStatus {
  std::string name;
  int hp;
  int maxhp;
  int atk;
  CharacterStatus() : name("Noone"), hp(-1), maxhp(-1), atk(-1) {}
  CharacterStatus(std::string name, int hp, int maxhp, int atk) : name(name), hp(hp), maxhp(maxhp), atk(atk) {}
};

class InfoWindow {
private:
  /* data */
  GridPoint playerPosition;
  CharacterStatus plStatus;

public:
  // InfoWindow ();
  void setPlayerPosition(GridPoint point) { playerPosition = point; }
  void setStatus(CharacterStatus stat) { plStatus = stat; }
  void drawWindow();
  // ~InfoWindow ();
};



#endif /* end of include guard: INFOWINDOW */
