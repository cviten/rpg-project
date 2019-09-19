#ifndef HUD
#define HUD

#include "common.h"

struct Meter {
  /* data */
  int min = 0;
  int max = 100;
  int curr= 100;
  Meter(int min, int max, int cur)
  Meter(int min = 0, int max = 100) : Meter(min,max,max) {}
};

class Bar : public sf::Drawable {
private:
  /* data */
  sf::RectangleShape back;
  sf::RectangleShape bar;
  sf::Text text;
  sf::Color barColor;
  Meter meter;

  void update();

public:
  Bar (sf::Color barColor, Rect rect, Meter meter)
  // Bar (sf::Color barColor, ) :  {}
  // Bar () :  Bar(sf::Color::Red,0,100,100) {}
  void set(int curr) { meter.curr = curr; }
  void set(int max, int curr) { meter.curr = curr; meter.max = max; }
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  // ~Bar ();
};

class HUDItem : sf::Drawable {
private:
  /* data */
  sf::Text label;
  Bar bar;

public:
  HUDItem (std::string, Bar bar);
  HUDItem (std::string, sf::Color barColor, Rect rect, Meter meter);
  // ~HUDItem ();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class HUD {
private:
  /* data */

public:
  HUD ();
  // ~HUD ();
};

#endif /* end of include guard: HUD */
