#include <iostream>

#include <stdexcept>
#include <SFML/Graphics.hpp>

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

struct GridSize : XY {
  GridSize(int x, int y) : XY(x,y) {}
  GridSize() : GridSize (5,5) {}
};

struct GridPoint : XY {
  GridPoint(int x, int y) : XY(x,y) {}
  GridPoint() : GridPoint (0,0) {}
};

const CellSize tileSize(30,30);
const GridPoint zeroGrid(0,0);

class Map : public sf::Drawable, public sf::Transformable {
public:
  struct Terrian {
    /* data */
    std::string name;
    bool pass = true;
    sf::Color color;
    Terrian(std::string&& name, bool pass, sf::Color color) : name(name), pass(pass), color(color) {}
    Terrian();
    // Terrian() : Terrian("Default", true, sf::Color(65,30,30)) {}
  };
  struct MapRef {
    /* data */
    const std::vector<Terrian>& map;
    GridSize size;
    MapRef(const std::vector<Terrian>& map, GridSize mapsize) : map(map), size(mapsize) {}
  };
private:
  /* data */
  GridSize mapsize;
  std::vector<Terrian> map;
  bool vismap = false;
  bool mapChanged = false;
  bool gridVisible = false;

  sf::VertexArray m_vertices;
  sf::VertexArray m_vertices2;

  void updateDraw();

public:
  explicit Map (GridSize size) : mapsize(size) , map(mapsize.x * mapsize.y, Terrian()) { updateDraw(); }
  // Map () : mapsize(10,10) , map(mapsize.x * mapsize.y, Terrian()) { updateDraw(); }
  Map () : Map(GridSize(10,10)) { }
  const Terrian& getTerrianCell(int x, int y) const;
  const Terrian& getTerrianCell(GridPoint p) const { return getTerrianCell(p.x, p.y); }
  void fill(const Terrian& tile, int x, int y, int sizeX, int sizeY);
  void fill(const Terrian& tile, int x, int y, GridSize size) { fill(tile, x,y, size.x, size.y); }
  void fill(const Terrian& tile, GridPoint p, GridSize size) { fill(tile, p.x, p.y, size.x, size.y); }
  GridSize getMapSize() const { return mapsize; }
  void showNormalMap() { vismap = false; mapChanged = true; }
  void showVisMap() { vismap = true; mapChanged = true;}
  void showGrid(bool visible) { gridVisible = true; mapChanged = true; }
  void toggleGrid() { gridVisible = !gridVisible; mapChanged = true; }
  void toggleVisMap() { vismap = !vismap; mapChanged = true; }
  // const std::vector<Terrian> getMap() { return map; }
  MapRef getMap() { return MapRef(map, mapsize); }
  void updateMap();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  // ~Map ();
};

namespace MapTiles {
  const Map::Terrian wip("Default", true, sf::Color(65,30,30));
  const Map::Terrian land("Land", true, sf::Color(36, 120, 39));
  const Map::Terrian water("Sea", false, sf::Color(36, 87, 191));
  const Map::Terrian mount("Mountain", false, sf::Color(153, 84, 32));
  const Map::Terrian lava("Lava", false, sf::Color(249, 79, 27));
}
// Map::Map() : map()

inline Map::Terrian::Terrian() : Map::Terrian(MapTiles::wip) {}

void Map::updateMap() {
  if (mapChanged) {
    updateDraw();
  }
}

const Map::Terrian& Map::getTerrianCell(int x, int y) const {

  return map.at(x + y * mapsize.x);
}

void Map::fill(const Terrian& tile, int x, int y, int sizeX, int sizeY) {
  x = (x < 0) ? 0 : x;
  y = (y < 0) ? 0 : y;
  int mx = (x + sizeX > mapsize.x) ? mapsize.x : x + sizeX;
  int my = (y + sizeY > mapsize.y) ? mapsize.y : y + sizeY;
  for (int i = x; i < mx; i++) {
    for (int j = y; j < my; j++) {
      /* code */
      map[i + j * mapsize.x] = tile;
    }

  }
}


void Map::updateDraw() {
  m_vertices.setPrimitiveType(sf::Lines);
  m_vertices.resize(mapsize.x * mapsize.y * 4 + 4);

  m_vertices2.setPrimitiveType(sf::Quads);
  m_vertices2.resize(mapsize.x * mapsize.y * 4);

  for (unsigned int i = 0; i < mapsize.x; ++i) {
    for (unsigned int j = 0; j < mapsize.y; ++j) {
      // get the current tile number
      // int tileNumber = tiles[i + j * mapsize.x];

      // find its position in the tileset texture
      // int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
      // int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

      // get a pointer to the current tile's quad
      sf::Vertex* grid = &m_vertices[(i + j * mapsize.x) * 4];

      // define its 4 corners
      // grid[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
      // grid[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
      grid[0].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
      grid[1].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
      grid[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
      grid[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
      // grid[6].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
      // grid[7].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);

      // grid[0].color = sf::Color::Green;
      // grid[1].color = sf::Color::Green;
      grid[0].color = sf::Color::Green;
      grid[1].color = sf::Color::Green;
      grid[2].color = sf::Color::Green;
      grid[3].color = sf::Color::Green;


      sf::Vertex* quad = &m_vertices2[(i + j * mapsize.x) * 4];

      quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
      quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
      quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
      quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);


      sf::Color color = (vismap) ? ((map[i + j * mapsize.x].pass) ? sf::Color(20,200,20) : sf::Color(200,20,20)) : map[i + j * mapsize.x].color;


      quad[0].color = color;
      quad[1].color = color;
      quad[2].color = color;
      quad[3].color = color;

    }
  }

  unsigned int n = mapsize.x * mapsize.y * 4 + 4;
  m_vertices[n-4].position = sf::Vector2f(0, 0);
  m_vertices[n-3].position = sf::Vector2f(mapsize.x * tileSize.x, 0);
  m_vertices[n-2].position = sf::Vector2f(0, 0);
  m_vertices[n-1].position = sf::Vector2f(0, mapsize.y * tileSize.y);

  m_vertices[n-4].color = sf::Color::Green;
  m_vertices[n-3].color = sf::Color::Green;
  m_vertices[n-2].color = sf::Color::Green;
  m_vertices[n-1].color = sf::Color::Green;

};

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // apply the transform
  states.transform *= getTransform();

  // apply the tileset texture
  // states.texture = &m_tileset;

  // draw the vertex array
  target.draw(m_vertices2, states);

  if (gridVisible) {
    /* code */
    target.draw(m_vertices, states);
  }
}

namespace Game {
  namespace Colors {
    const sf::Color player(165, 70, 200);
    const sf::Color bot(200, 70, 70);
    const sf::Color defeatedBot(120, 40, 50);
    const sf::Color item(55, 145, 200);
  }
} /* Game */

class GameObject : public sf::Drawable {
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
  GameObject (Point point, sf::Color spriteColor, bool pass, GridPoint startPoint);
  void move(int dx, int dy);
  void move(GridPoint dp) { move(dp.x, dp.y); }
  const GridPoint& getGridPosition() const { return position; }
  void setGridPosition(const GridPoint& point) { position = point; }
  Point getScreenPosition() const { return Point(transform.getPosition().x, transform.getPosition().y); }
  void setScreenPosition(Point point) { transform.setPosition(point); }
  // ~GameObject ();
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

GameObject::GameObject(Point point, sf::Color color, bool pass = false, GridPoint startPoint = GridPoint()) : pass(pass), position(startPoint) {
  sprite.setSize(tileSize);
  sprite.setFillColor(color);
  transform.setPosition(point.x, point.y);
  move(startPoint);
}

void GameObject::move(int dx, int dy) {
  transform.move(dx*tileSize.x, dy*tileSize.y);
  position.x += dx;
  position.y += dy;
}

void GameObject::updateObject() {
  if (edge) {
    sprite.setSize(tileSize);
  } else {
    sprite.setSize(sf::Vector2f(tileSize.x - 1 ,tileSize.y - 1));
  }
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= transform.getTransform();
  // target.draw(character, states);
  target.draw(sprite, states);
};

struct Stats {
  /* data */
  int maxHP;
  int atk;
  Stats(int hp, int atk) : maxHP(hp), atk(atk) {}
  Stats() : Stats(30,15) {}
};

class Character : public GameObject {
private:
  /* data */
  std::string name;
  Stats stats;

  int currHP;

public:
  Character (Point point, sf::Color spriteColor = Game::Colors::bot, const std::string& name = "Bot", Stats stats = Stats()) : GameObject(point,spriteColor), currHP(stats.maxHP) {}
  const std::string& getName() const { return name;}
  const Stats& getStats() const { return stats; }
  void takeDamage(int atk) { currHP -= atk; if (currHP <= 0) { changeColor(Game::Colors::defeatedBot); setActive(false); }; }
  void attack(Character& target) { target.takeDamage(getStats().atk); }
  // ~Character ();
};

class PlayerCharacter : public Character {
private:
  /* data */
  // std::vector<Item> v;

public:
  PlayerCharacter(Point point, sf::Color spriteColor = Game::Colors::player, const std::string& name = "Player", Stats stats = Stats()) : Character(point, spriteColor, name, stats) {}
  // ~Character ();
};

class Item : public GameObject {
private:
  /* data */
  std::string name;

public:
  Item (Point point, sf::Color spriteColor = Game::Colors::item, const std::string& name = "Item A") : GameObject(point, spriteColor, true), name(name) {}
  const std::string& getName() const { return name;}
  // ~Item ();
};

class GameManager : public sf::Drawable {

private:
  /* data */
  Map map;

  PlayerCharacter p1;
  Character bot;
  Item item;
  bool itemcheck = true;
  Point mapOrigin = Point(100,100);

  void moveCharacter(int dx, int dy);
  bool checkMovement(int x, int y, bool action);
  bool checkMovement(GridPoint d, bool action) { return checkMovement(d.x, d.y, action); }

public:
  GameManager ();
  // ~GameManager ();
  void readEventKey(sf::Keyboard::Key key);
  void setGameObjectPosition(GameObject& go, GridPoint point);
  // void setCharacterPosition(Character& ch, GridPoint point);
  void postTurn() { map.updateMap(); }
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    target.draw(map, states);
    target.draw(bot, states);
    target.draw(p1, states);
  };
};

GameManager::GameManager() : p1(mapOrigin), bot(mapOrigin), item(mapOrigin), map(GridSize(20,15)) {
  map.setPosition(mapOrigin);
  // p1i.setScreenPosition(mapOrigin); //Find a way to make it more clean
  setGameObjectPosition(p1, GridPoint(5,3));
  setGameObjectPosition(bot, GridPoint(4,2));
  setGameObjectPosition(bot, GridPoint(4,2));

  map.fill(MapTiles::water, 0,0, map.getMapSize());

  map.fill(MapTiles::land, 0,0, 15,12);

  // map.makeMount(2,3,4,2);
  map.updateMap();

  // map.showVisMap();
  map.showNormalMap();
}

void GameManager::setGameObjectPosition(GameObject& ch, GridPoint point) {
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
  if (key == sf::Keyboard::Tab) { map.toggleGrid(); p1.toggleEdges(); bot.toggleEdges(); }
  if (key == sf::Keyboard::Q) { map.toggleVisMap(); }
}

void GameManager::moveCharacter(int dx, int dy) {
  if (checkMovement(p1.getGridPosition().x + dx, p1.getGridPosition().y + dy, true)) {
    p1.move(dx,dy);
  }
}


int main(int argc, char const *argv[]) {
  sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Grid movement", sf::Style::Titlebar | sf::Style::Close);
  sf::Clock clock;

  // Map map;
  // map.setPosition(100,100);
  GameManager gm;

  while (window.isOpen())
  {
    // gm.setup();

    sf::Event event;
    while (window.pollEvent(event))
    {
      if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
        window.close();
      }
      if ((event.type == sf::Event::KeyPressed) ) {
        // std::cout << "In key event" << '\n';
        gm.readEventKey(event.key.code);
      }
      // if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
      //   gm.readEventKey(event.key.code);
      // }
    }
    // deltaTime = clock.restart().asSeconds();
    // gm.process();
    // gm.process(deltaTime);

    gm.postTurn();
    window.clear();


    // window.draw(gm);
    window.draw(gm);

    window.display();
    // gm.cleanup();
  }

  return 0;
}
