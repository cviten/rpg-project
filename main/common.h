#ifndef COMMON
#define COMMON

#include <SFML/Graphics.hpp>
#include <exception>
#include <stdexcept>

const int gameWidth = 1000;
const int gameHeight = 700;

struct XY {
  /* data */
  int x = 0;
  int y = 0;
  operator sf::Vector2f() const { return sf::Vector2f(x,y); }
  bool operator== (const XY& p) const { return (x == p.x && y == p.y);}
protected:
  XY(int _x, int _y) : x(_x), y(_y) {}
public:
  XY(const sf::Vector2f& p) : x(p.x), y(p.y) {}
  XY& operator= (const sf::Vector2f& p) { x = p.x; y = p.y; return *this; }
  // XY() : XY (50,50) {}
};

struct CellSize : XY {
  CellSize(int x, int y) : XY(x,y) {} //: x(_x), y(_y) {}
  CellSize() : CellSize(50,50) {}
};

struct Point : XY {
  Point(int x, int y) : XY(x,y) {}
  Point() : Point (50,50) {}
};

struct Size : XY {
  Size(int x, int y) : XY(x,y) {}
  Size() : Size (50,50) {}
};

struct GridSize : XY {
  GridSize(int x, int y) : XY(x,y) {}
  GridSize() : GridSize (5,5) {}
};

struct GridPoint : XY {
  GridPoint(int x, int y) : XY(x,y) {}
  GridPoint() : GridPoint (0,0) {}
};

struct Rect {
  Point point;
  Size size;
  Rect(Point point, Size size) : point(point), size(size) {}
};

const CellSize tileSize(30,30);
const GridPoint zeroGrid(0,0);

namespace Game {
  namespace Colors {
    const sf::Color player(165, 70, 200);
    const sf::Color bot(200, 70, 70);
    const sf::Color defeatedBot(120, 40, 50);
    const sf::Color item(55, 145, 200);
  }
  namespace UI {
    const Size HealthBarSize(200,30);
  } /* UI */
} /* Game */

#endif /* end of include guard: COMMON */
