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
  GridPoint() : GridPoint (1,1) {}
};

const CellSize tileSize(30,30);

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
  Map (GridSize size) : mapsize(size) , map(mapsize.x * mapsize.y, Terrian()) { updateDraw(); }
  // Map () : mapsize(10,10) , map(mapsize.x * mapsize.y, Terrian()) { updateDraw(); }
  Map () : Map(GridSize(10,10)) { }
  const Terrian& getTerrianCell(int x, int y) const;
  const Terrian& getTerrianCell(GridPoint p) const { return getTerrianCell(p.x, p.y); }
  void fill(Terrian tile, int x, int y, int sizeX, int sizeY);
  void fill(Terrian tile, int x, int y, GridSize size) { fill(tile, x,y, size.x, size.y); }
  void fill(Terrian tile, GridPoint p, GridSize size) { fill(tile, p.x, p.y, size.x, size.y); }
  // void makeLand(int x, int y, int sizeX, int sizeY);
  // void makeLand(int x, int y, GridSize size) { makeLand(x,y, size.x, size.y); }
  // void makeSea(int x, int y, int sizeX, int sizeY);
  // void makeSea(int x, int y, GridSize size) { makeSea(x,y, size.x, size.y); }
  // void makeMount(int x, int y, int sizeX, int sizeY);
  // void makeMount(int x, int y, GridSize size) { makeMount(x,y, size.x, size.y); }
  // void makeLava(int x, int y, int sizeX, int sizeY);
  // void makeLava(int x, int y, GridSize size) { makeLava(x,y, size.x, size.y); }
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
  // if ((x < 0) || (y < 0) || (x >= mapsize.x) || (y >= mapsize.y)) {
  //   throw std::out_of_range("Map Error: Trying to get Terrian outside of map");
  // }
  return map.at(x + y * mapsize.x);
}

void Map::fill(Terrian tile, int x, int y, int sizeX, int sizeY) {
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

// void Map::makeLand(int x, int y, int sizeX, int sizeY) {
//   fill(MapTiles::land, x, y, sizeX, sizeY);
//   mapChanged = true;
// }
// void Map::makeSea(int x, int y, int sizeX, int sizeY) {
//   fill(MapTiles::water, x, y, sizeX, sizeY);
//   mapChanged = true;
// }
// void Map::makeMount(int x, int y, int sizeX, int sizeY) {
//   fill(MapTiles::mount, x, y, sizeX, sizeY);
//   mapChanged = true;
// }
// void Map::makeLava(int x, int y, int sizeX, int sizeY) {
//   fill(MapTiles::lava, x, y, sizeX, sizeY);
//   mapChanged = true;
// }

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

// class Character : public sf::Drawable {
class Character {
public:
  struct Stats {
    /* data */
    int maxHP;
    int atk;
    Stats(int hp, int atk) : maxHP(hp), atk(atk) {}
    Stats() : Stats(30,15) {}
  };
private:
  /* data */
  std::string name = "Bot";
  Stats stats;
  bool pass = false;

public:
  Character (Stats stats = Stats()) : stats(stats) {}
  // Character () : Character(Stats()) {}
  const std::string& getName() const { return name;}
  const Stats& getStats() const { return stats; }
  bool getPass() const { return pass; }

};

namespace CharColors {
  const sf::Color player(165, 70, 200);
  const sf::Color bot(200, 70, 70);
  const sf::Color defeatedBot(120, 40, 50);
}

struct Item {
  std::string name;
};

class GameManager : public sf::Drawable {
public:
  class CharacterInst : public sf::Drawable /*, public sf::Transformable */{
  private:
    /* data */
    Character character;
    sf::RectangleShape sprite;
    sf::Transformable transform;
    // sf::Transformable transform;
    GridPoint gridPosition;
    int currHP;

    bool edge = true;

  public:
    CharacterInst (const Character& ch = Character(), int x = 0, int y = 0, sf::Color color = CharColors::bot) : character(ch), gridPosition(x,y), currHP(ch.getStats().maxHP) {
      // sprite.setSize(sf::Vector2f(tileSize.x, tileSize.y));
      sprite.setSize(tileSize);
      sprite.setFillColor(color);
      transform.setPosition(x, y);
    }
    CharacterInst (const Character& ch = Character(), Point p = Point(), sf::Color color= CharColors::bot) : CharacterInst(ch, p.x, p.y, color) {}
    // CharacterInst (const Character& ch, int x, int y) : CharacterInst(ch, x, y, sf::Color::Red) {}
    // CharacterInst (const Character& ch, Point p) : CharacterInst(ch, p.x, p.y, sf::Color::Red) {}
    CharacterInst (const Character& ch = Character(), sf::Color color = CharColors::bot) : CharacterInst(ch, 0, 0, color) {}
    CharacterInst (sf::Color color = CharColors::bot) : CharacterInst(Character(), 0, 0, color) {}
    // CharacterInst (const Character& ch) : CharacterInst(ch, 0, 0, sf::Color::Red) {}
    //-------------------------
    const Character& getCharacter() const { return character; }

    void takeDamage(int atk) { currHP -= atk; if (currHP <= 0) { sprite.setFillColor(CharColors::defeatedBot); }; }
    void attack(CharacterInst& target) { target.takeDamage(character.getStats().atk); }

    // CharacterInst (const Character&& ch) : CharacterInst(ch,0,0) {}
    GridPoint getGridPosition() const { return gridPosition; }
    // Point getScreenPosition() const { return Point(transform.getOrigin().x,transform.getOrigin().y); }
    void setGridPosition(int x, int y) { gridPosition.x = x; gridPosition.y = y; }
    void setGridPosition(GridPoint point) { gridPosition = point; }
    // GridPoint getGridPosition() const { return gridPosition; }
    void setScreenPosition(Point point) { transform.setPosition(point); }
    int getX() const { return gridPosition.x; }
    int getY() const { return gridPosition.y; }
    void move(int dx, int dy);
    void move(GridPoint point) { move(point.x, point.y); }
    void toggleEdges() { edge = !edge; updateChar(); }
    void setEdges(bool e) { edge = e; updateChar(); }
    void updateChar() {
      if (edge) {
        sprite.setSize(tileSize);
      } else {
        sprite.setSize(sf::Vector2f(tileSize.x - 1 ,tileSize.y - 1));
      }
    }
    // ~CharacterInst ();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
      states.transform *= transform.getTransform();
      // target.draw(character, states);
      target.draw(sprite, states);
    };
  };
  // class PlayerCharacterInst : public CharacterInst {
  // private:
  //   /* data */
  //
  // public:
  //   PlayerCharacterInst (const Character& ch, int x, int y, sf::Color color) : character(ch), gridPosition(x,y), currHP(ch.getStats().maxHP)
  //   PlayerCharacterInst (const Character& ch, Point p, sf::Color color) : CharacterInst(ch, p.x, p.y, color) {}
  //   PlayerCharacterInst (const Character& ch, int x, int y) : CharacterInst(ch, x, y, sf::Color::Red) {}
  //   PlayerCharacterInst (const Character& ch, Point p) : CharacterInst(ch, p.x, p.y, sf::Color::Red) {}
  //   PlayerCharacterInst (const Character& ch, sf::Color color) : CharacterInst(ch, 0, 0, color) {}
  //   PlayerCharacterInst (const Character& ch) : CharacterInst(ch, 0, 0, sf::Color::Red) {}
  //   // ~Player ();
  // };

private:
  /* data */
  Map map;
  Character p1;
  CharacterInst p1i;
  CharacterInst enemy;
  Point mapOrigin = Point(100,100);

  void moveCharacter(int dx, int dy);
  bool checkMovement(int x, int y);
  bool checkMovement(GridPoint d) { return checkMovement(d.x, d.y); }

public:
  GameManager ();
  // ~GameManager ();
  void readEventKey(sf::Keyboard::Key key);
  void setCharacterPosition(CharacterInst& ch, GridPoint point);
  void postTurn() { map.updateMap(); }
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    target.draw(map, states);
    target.draw(enemy, states);
    target.draw(p1i, states);
  };
};

GameManager::GameManager() : p1i(CharColors::player), enemy(CharColors::bot), map(GridSize(20,15)) {
  map.setPosition(mapOrigin);
  // p1i.setScreenPosition(mapOrigin); //Find a way to make it more clean
  setCharacterPosition(p1i, GridPoint(5,3));
  setCharacterPosition(enemy, GridPoint(4,2));
  // p1i.setPosition(100,100);
  // map.makeSea(0,0, map.getMapSize());
  map.fill(MapTiles::water, 0,0, map.getMapSize());
  // map.makeSea(0,0,20,10);
  // map.makeLand(0,0,15,12);
  map.fill(MapTiles::land, 0,0, 15,12);

  // map.makeMount(2,3,4,2);
  map.updateMap();

  // map.showVisMap();
  map.showNormalMap();
}

void GameManager::setCharacterPosition(CharacterInst& ch, GridPoint point) {
  if (checkMovement(point)) {
    ch.setGridPosition(0,0);
    ch.setScreenPosition(mapOrigin);
    ch.move(point);
  }
}

bool GameManager::checkMovement(int x, int y) {
  if ( (x < 0) || (y < 0) || (x >= map.getMapSize().x) ||(y >= map.getMapSize().y) ) {
    std::cout << "Out of the map!" << '\n';
    return false;
  } else if (!map.getTerrianCell(x, y).pass) {
    std::cout << "Can't go into " << map.getTerrianCell(x, y).name << '\n';
    return false;
  } else if (GridPoint(x,y) == enemy.getGridPosition()) {
    // std::cout << "Can't go into " << enemy.getCharacter().getName() << '\n';
    p1i.attack(enemy);
    std::cout << "Attacked " << enemy.getCharacter().getName() << '\n';
    return false;
  } else {
    return true;
  }
}

void GameManager::readEventKey(sf::Keyboard::Key key) {


  if (key == sf::Keyboard::Up) { moveCharacter(0,-1); }
  if (key == sf::Keyboard::Down) { moveCharacter(0,1); }
  if (key == sf::Keyboard::Left) { moveCharacter(-1,0); }
  if (key == sf::Keyboard::Right) { moveCharacter(1,0); }
  if (key == sf::Keyboard::Space) { map.fill(MapTiles::lava, p1i.getX(),p1i.getY(),1,1); }
  if (key == sf::Keyboard::Tab) { map.toggleGrid(); p1i.toggleEdges(); enemy.toggleEdges(); }
  if (key == sf::Keyboard::Q) { map.toggleVisMap(); }
}

void GameManager::moveCharacter(int dx, int dy) {
  if (checkMovement(p1i.getX() + dx, p1i.getY() + dy)) {
    p1i.move(dx,dy);
  }
}

void GameManager::CharacterInst::move(int dx, int dy) {
  transform.move(dx*tileSize.x, dy*tileSize.y);
  gridPosition.x += dx;
  gridPosition.y += dy;
}

// void GameManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//   target.draw(map, states);
// }

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
