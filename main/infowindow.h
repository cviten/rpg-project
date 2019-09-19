#ifndef INFOWINDOW
#define INFOWINDOW

#include "./SFML-imgui/imgui.h"
#include "./SFML-imgui/imgui-SFML.h"

#include "common.h"

class InfoWindow {
private:
  /* data */
  GridPoint playerPosition;

public:
  // InfoWindow ();
  void setPlayerPosition(GridPoint point) { playerPosition = point; }
  void drawWindow();
  // ~InfoWindow ();
};



#endif /* end of include guard: INFOWINDOW */
