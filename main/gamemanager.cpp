#include <iostream>

#include "gamemanager.h"

GameManager::GameManager() : map(GridSize(20,15)), p1(mapOrigin), bot(mapOrigin), item(mapOrigin) {
  map.setPosition(mapOrigin);
  // p1i.setScreenPosition(mapOrigin); //Find a way to make it more clean

  map.fill(MapTiles::water, 0,0, map.getMapSize());

  map.fill(MapTiles::land, 0,0, 15,12);

  setMapObjectPosition(p1, GridPoint(5,3));
  setMapObjectPosition(bot, GridPoint(4,2));
  setMapObjectPosition(item, GridPoint(2,7));

  hud.setHealth(50);
  p1.takeDamage(20);

  // map.makeMount(2,3,4,2);
  map.updateMap();

  // map.showVisMap();
  map.showNormalMap();
}

void GameManager::drawInfo() {
  iw.setPlayerPosition(p1.getGridPosition());
  CharacterStatus p1stat(p1.getName(), p1.getStatus().currHP, p1.getStatus().stats.maxHP, p1.getStatus().stats.atk);
  iw.setStatus(p1stat);
  iw.drawWindow();
}

void GameManager::setMapObjectPosition(MapObject& ch, GridPoint point) {
  if (checkMovement(point, false)) {
    ch.setGridPosition(zeroGrid);
    ch.setScreenPosition(mapOrigin);
    ch.move(point);
  }
}

bool GameManager::checkMovement(int x, int y, bool action) {
  if ( (x < 0) || (y < 0) || (x >= map.getMapSize().x) ||(y >= map.getMapSize().y) ) {
    std::cout << "Out of the map!" << '\n';
    return false;
  } else if (!map.getTerrianCell(x, y).pass) {
    std::cout << "Can't go into " << map.getTerrianCell(x, y).name << '\n';
    return false;
  } else if (action) {
    if (GridPoint(x,y) == bot.getGridPosition() && bot.isActive()) {
      // std::cout << "Can't go into " << enemy.getCharacter().getName() << '\n';
      p1.attack(bot);
      std::cout << "Attacked " << bot.getName() << '\n';
      return false;
    } else if (GridPoint(x,y) == item.getGridPosition() && item.isActive()) {
      // std::cout << "Can't go into " << enemy.getCharacter().getName() << '\n';
      item.setActive(false);
      std::cout << "Player got " << item.getName() << '\n';
      item.getItem().use(p1);
      return true;
    }
  }
  return true;
}

void GameManager::readEventKey(sf::Keyboard::Key key) {
  if (key == sf::Keyboard::Up) { moveCharacter(0,-1); }
  if (key == sf::Keyboard::Down) { moveCharacter(0,1); }
  if (key == sf::Keyboard::Left) { moveCharacter(-1,0); }
  if (key == sf::Keyboard::Right) { moveCharacter(1,0); }
  // if (key == sf::Keyboard::Space) { map.fill(MapTiles::lava, p1i.getX(),p1i.getY(),1,1); }
  if (key == sf::Keyboard::Tab) { map.toggleGrid(); p1.toggleEdges(); bot.toggleEdges(); item.toggleEdges(); }
  if (key == sf::Keyboard::Q) { map.toggleVisMap(); }
}

void GameManager::moveCharacter(int dx, int dy) {
  if (checkMovement(p1.getGridPosition().x + dx, p1.getGridPosition().y + dy, true)) {
    p1.move(dx,dy);
  }
}
