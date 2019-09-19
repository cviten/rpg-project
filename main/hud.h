#ifndef HUDCLASS
#define HUDCLASS

#include "common.h"

struct Meter {
  /* data */
  int min = 0;
  int max = 100;
  int curr= 100;
  Meter(int min, int max, int curr) : min(min), max(max), curr(curr) {}
  Meter(int max = 100, int min = 0) : Meter(min,max,max) {}
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
  Bar (sf::Color barColor, Point origin, Size size = Game::UI::HealthBarSize, Meter meter = Meter());
  Bar (sf::Color barColor, Rect rect, Meter meter = Meter()) : Bar(barColor, rect.point, rect.size, meter) {}
  // Bar (sf::Color barColor, ) :  {}
  // Bar () :  Bar(sf::Color::Red,0,100,100) {}
  void setPosition(Point origin);
  void set(int curr) { meter.curr = curr; }
  void set(int max, int curr) { meter.curr = curr; meter.max = max; }
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  // ~Bar ();
};

class HUDItem : public sf::Drawable {
private:
  /* data */
  sf::Text label;
  Bar bar;
  int offset;

public:
  // HUDItem (std::string text, Bar bar);
  HUDItem (std::string text, sf::Color barColor, Point origin, Size size = Game::UI::HealthBarSize, Meter meter = Meter());
  // HUDItem (std::string text, sf::Color barColor, Rect rect, Meter meter);
  // ~HUDItem ();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class HUD : public sf::Drawable {
private:
  /* data */
  HUDItem health;

public:
  HUD () : health("Health", sf::Color::Red, Point(20,500)) {};
  // ~HUD ();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* end of include guard: HUDCLASS */
