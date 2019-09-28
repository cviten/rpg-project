#ifndef MAP
#define MAP

#include "common.h"

class MapException : std::logic_error {
public:
  MapException (std::string arg) : std::logic_error(arg) {}
};

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
  explicit Map (GridSize size);
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
  void showGrid(bool visible) { gridVisible = visible; mapChanged = true; }
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

#endif /* end of include guard: MAP */
