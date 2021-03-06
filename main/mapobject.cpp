#include "mapobject.h"

MapObject::MapObject(sf::Color color, MapObjectType type, bool pass, GridPoint startPoint) : pass(pass), position(startPoint), type(type) {
  sprite.setSize(tileSize);
  sprite.setFillColor(color);
  transform.setPosition(mapOrigin.x, mapOrigin.y);
  move(startPoint);
}

void MapObject::move(int dx, int dy) {
  transform.move(dx*tileSize.x, dy*tileSize.y);
  position.x += dx;
  position.y += dy;
}

void MapObject::updateObject() {
  if (edge) {
    sprite.setSize(tileSize);
  } else {
    sprite.setSize(sf::Vector2f(tileSize.x - 1 ,tileSize.y - 1));
  }
}

void MapObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= transform.getTransform();
  // target.draw(character, states);
  target.draw(sprite, states);
};


const NullMapObject& getNullMapObject() {
 static NullMapObject nullobj;
 return nullobj;
}
