#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

const int gameWidth = 1000;
const int gameHeight = 700;

struct CellSize {
  int x = 50;
  int y = 50;
  CellSize(int _x, int _y) : x(_x), y(_y) {}
  CellSize() : CellSize (50,50) {}
};

// const int cellSizex = 50;
// const int cellSizey = 50;

const CellSize tileSize(50,50);

struct GridSize {
  int x = 5;
  int y = 5;
  GridSize(int _x, int _y) : x(_x), y(_y) {}
  GridSize() : GridSize (5,5) {}
};

class Map : public sf::Drawable, public sf::Transformable {
public:
  struct Terrian {
    /* data */
    std::string name;
    bool pass = true;
    sf::Color color;
    Terrian(std::string&& _name, bool passible, sf::Color _color) : name(_name), pass(passible), color(_color) {}
    Terrian() : Terrian("Default", true, sf::Color(65,30,30)) {}
  };
  struct MapRef {
    /* data */
    const std::vector<Terrian>& map;
    GridSize size;
    MapRef(const std::vector<Terrian>& _map, GridSize mapsize) : map(_map), size(mapsize) {}
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
  void fill(Terrian tile, int x, int y, int sizeX, int sizeY);
  void fill(Terrian tile, int x, int y, GridSize size) { fill(tile, x,y, size.x, size.y); }
  void makeLand(int x, int y, int sizeX, int sizeY);
  void makeLand(int x, int y, GridSize size) { makeLand(x,y, size.x, size.y); }
  void makeSea(int x, int y, int sizeX, int sizeY);
  void makeSea(int x, int y, GridSize size) { makeSea(x,y, size.x, size.y); }
  void makeMount(int x, int y, int sizeX, int sizeY);
  void makeMount(int x, int y, GridSize size) { makeMount(x,y, size.x, size.y); }
  void makeLava(int x, int y, int sizeX, int sizeY);
  void makeLava(int x, int y, GridSize size) { makeLava(x,y, size.x, size.y); }
  GridSize getMapSize() const { return mapsize; }
  void showNormalMap() { vismap = false; mapChanged = true; }
  void showVisMap() { vismap = true; mapChanged = true;}
  void showGrid(bool visible) { gridVisible = true; mapChanged = true; }
  void toggleGrid() { gridVisible = !gridVisible; mapChanged = true; }
  // const std::vector<Terrian> getMap() { return map; }
  MapRef getMap() { return MapRef(map, mapsize); }
  void updateMap();
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  // ~Map ();
};

namespace MapTiles {
  Map::Terrian land("Land", true, sf::Color(36, 193, 39));
  Map::Terrian water("Sea", false, sf::Color(36, 87, 191));
  Map::Terrian mount("Mountain", false, sf::Color(153, 84, 32));
  Map::Terrian lava("Lava", false, sf::Color(249, 79, 27));
}

// Map::Map() : map()

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

void Map::makeLand(int x, int y, int sizeX, int sizeY) {
  fill(MapTiles::land, x, y, sizeX, sizeY);
  mapChanged = true;
}
void Map::makeSea(int x, int y, int sizeX, int sizeY) {
  fill(MapTiles::water, x, y, sizeX, sizeY);
  mapChanged = true;
}
void Map::makeMount(int x, int y, int sizeX, int sizeY) {
  fill(MapTiles::mount, x, y, sizeX, sizeY);
  mapChanged = true;
}
void Map::makeLava(int x, int y, int sizeX, int sizeY) {
  fill(MapTiles::lava, x, y, sizeX, sizeY);
  mapChanged = true;
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


      // if (vismap) {
      //   sf::Color color = (map[i + j * mapsize.x].pass) ? sf::Color::Green : sf::Color::Red;
      // } else {
      //   sf::Color color = map[i + j * mapsize.x].color;
      // }

      sf::Color color = (vismap) ? ((map[i + j * mapsize.x].pass) ? sf::Color(20,200,20) : sf::Color(200,20,20)) : map[i + j * mapsize.x].color;

      // sf::Color color = map[i + j * mapsize.x].color;
      // Is useful for pass map
      // sf::Color color = (map[i + j * mapsize.x].pass) ? sf::Color::Green : sf::Color::Red;

      quad[0].color = color;
      quad[1].color = color;
      quad[2].color = color;
      quad[3].color = color;


      // grid[6].color = sf::Color::Green;
      // grid[7].color = sf::Color::Green;

      // define its 4 texture coordinates
      // quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
      // quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
      // quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
      // quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
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
private:
  /* data */
  std::string name = "Bot";

public:
  Character ();
  std::string getName() const { return name;}
  // ~Character ();
  // void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
  //   //Figure out waht to do with transforms
  //   states.transform *= transform.getTransform();
  //   target.draw(sprite, states);
  // };
};

Character::Character() {

}

class GameManager : public sf::Drawable {
public:
  class CharacterInst : public sf::Drawable /*, public sf::Transformable */{
  private:
    /* data */
    Character character;
    sf::RectangleShape sprite;
    sf::Transformable transform;
    // sf::Transformable transform;
    int x = 0;
    int y = 0;

  public:
    CharacterInst (const Character&& ch, int _x, int _y) : character(ch) {
      sprite.setSize(sf::Vector2f(tileSize.x - 1 ,tileSize.y - 1));
      sprite.setFillColor(sf::Color::Red);
      transform.setPosition(_x, _y);
    }
    // CharacterInst (const Character&& ch) : CharacterInst(ch,0,0) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void move(int dx, int dy);
    // ~CharacterInst ();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
      states.transform *= transform.getTransform();
      // target.draw(character, states);
      target.draw(sprite, states);
    };
  };
private:
  /* data */
  Map map;
  Character p1;
  CharacterInst p1i;

  void moveCharacter(int dx, int dy);

public:
  GameManager ();
  // ~GameManager ();
  void readEventKey(sf::Keyboard::Key key);
  void postTurn() { map.updateMap(); }
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(map, states); target.draw(p1i, states); };
};

GameManager::GameManager() : p1i(Character(), 100, 100), map(GridSize(15,15)) {
  map.setPosition(100, 100);
  // p1i.setPosition(100,100);
  map.makeSea(0,0, map.getMapSize());
  // map.makeSea(0,0,20,10);
  map.makeLand(0,0,5,5);
  // map.makeLand(7,7,5,5);
  map.makeLand(4,2,5,1);
  map.makeLand(7,2,1,6);
  map.makeLand(2,7,5,1);
  map.makeLand(2,4,1,5);
  map.makeMount(5,0,1,5);
  map.updateMap();

  // map.showVisMap();
  map.showNormalMap();
}

void GameManager::readEventKey(sf::Keyboard::Key key) {
  // if (key == sf::Keyboard::Up) { p1.move(0,-tileSize.y); }
  // if (key == sf::Keyboard::Down) { p1.move(0,tileSize.y); }
  // if (key == sf::Keyboard::Left) { p1.move(-tileSize.x,0); }
  // if (key == sf::Keyboard::Right) { p1.move(tileSize.x,0); }

  if (key == sf::Keyboard::Up) { moveCharacter(0,-1); }
  if (key == sf::Keyboard::Down) { moveCharacter(0,1); }
  if (key == sf::Keyboard::Left) { moveCharacter(-1,0); }
  if (key == sf::Keyboard::Right) { moveCharacter(1,0); }
  if (key == sf::Keyboard::Space) { map.makeLava(p1i.getX(),p1i.getY(),1,1); }
  if (key == sf::Keyboard::Tab) { map.toggleGrid(); }
}

void GameManager::moveCharacter(int dx, int dy) {
  if ( (p1i.getX() + dx < 0) || (p1i.getY() + dy < 0) || (p1i.getX() + dx >= map.getMapSize().x) ||(p1i.getY() + dy >= map.getMapSize().y) ) {
    /* code */
    std::cout << "Out of the map!" << '\n';
  } else if (!map.getTerrianCell(p1i.getX() + dx, p1i.getY() + dy).pass) {
    /* code */
    std::cout << "Can't go into " << map.getTerrianCell(p1i.getX() + dx, p1i.getY() + dy).name << '\n';
  } else {
    /* code */
  // } {
    /* code */
    p1i.move(dx,dy);
  }
}

void GameManager::CharacterInst::move(int dx, int dy) {
  transform.move(dx*tileSize.x, dy*tileSize.y);
  x += dx;
  y += dy;
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
