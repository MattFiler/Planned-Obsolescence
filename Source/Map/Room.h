#include "Tile.h"

class Room
{
 public:
  Room();
  ~Room();

  void loadTiles();

 private:
  Tile* tiles = nullptr;
};