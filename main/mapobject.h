#ifndef MAPOBJECT
#define MAPOBJECT

#include "common.h"

class MapObject : public sf::Drawable {
// public:
  // enum MapObjectType {Char, Item};
private:
  /* data */
  sf::RectangleShape sprite;
  sf::Transformable transform;
  GridPoint position;
  bool pass;
  bool edge = true;
  bool active = true;

protected:
  void changeColor(const sf::Color color) { sprite.setFillColor(color); }

public:
  MapObject (Point point, sf::Color spriteColor, bool pass = false, GridPoint startPoint = GridPoint());
  void move(int dx, int dy);
  void move(GridPoint dp) { move(dp.x, dp.y); }
  const GridPoint& getGridPosition() const { return position; }
  void setGridPosition(const GridPoint& point) { position = point; }
  Point getScreenPosition() const { return Point(transform.getPosition().x, transform.getPosition().y); }
  void setScreenPosition(Point point) { transform.setPosition(point); }
  // ~MapObject ();
  void updateObject();
  void toggleEdges() { edge = !edge; updateObject(); }
  void setEdges(bool e) { edge = e; updateObject(); }
  void setPass(bool pass) { this->pass = pass; }
  bool getPass() const { return pass; }
  void toggleActive() { active = !active; }
  void setActive(bool a) { active = a; }
  bool isActive() const { return active; }
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif /* end of include guard: MAPOBJECT */
