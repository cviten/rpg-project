#include "map.h"

Map::Terrian::Terrian() : Map::Terrian::Terrian(MapTiles::wip) {}

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
