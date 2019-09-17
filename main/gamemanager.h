#ifndef GAMEMANAGER
#define GAMEMANAGER

#include "map.h"
#include "character.h"
#include "item.h"

class GameManager : public sf::Drawable {

private:
  /* data */
  Map map;

  PlayerCharacter p1;
  Character bot;
  ItemObject item;
  bool itemcheck = true;
  Point mapOrigin = Point(100,100);

  void moveCharacter(int dx, int dy);
  bool checkMovement(int x, int y, bool action);
  bool checkMovement(GridPoint d, bool action) { return checkMovement(d.x, d.y, action); }

public:
  GameManager ();
  // ~GameManager ();
  void readEventKey(sf::Keyboard::Key key);
  void setMapObjectPosition(MapObject& go, GridPoint point);
  // void setCharacterPosition(Character& ch, GridPoint point);
  void postTurn() { map.updateMap(); }
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    target.draw(map, states);
    // target.draw(p1, states);
    // target.draw(bot, states);
    if (p1.isActive()) { target.draw(p1, states); }
    if (bot.isActive()) { target.draw(bot, states); }
    if (item.isActive()) { target.draw(item, states); }
  };
};



#endif /* end of include guard: GAMEMANAGER */
