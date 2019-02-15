#include "PathfindingMap.h"

PathfindingMap::PathfindingMap(GameMap* current_map)
{
  int total_tiles = 0;
  game_map = current_map;
  for (int i = 0; i < game_map->getRoomCount(); i++)
  {
    total_tiles += game_map->getRooms()[i].getTileCount();
  }

  nodes = new PathNode[total_tiles];
  number_of_nodes = total_tiles;

  // First populate the map with the positions of each node
  int tile_count = 0;
  for (int i = 0; i < game_map->getRoomCount(); i++)
  {
    for (Tile& this_tile : game_map->getRooms()[i].getTiles())
    {
      nodes[tile_count].position = Point(this_tile.getPositionX(), this_tile.getPositionY());
      tile_count++;
    }
  }
  linkNodes();
}

void PathfindingMap::linkNodes()
{
  // Loop through a second time to add the connections between nodes
  int tile_count = 0;
  float tile_size = game_map->getRooms()[0].getTiles()[0].getWidth();
  for (int i = 0; i < game_map->getRoomCount(); i++)
  {
    for (Tile& this_tile : game_map->getRooms()[i].getTiles())
    {
      // Check all 4 exits on each tile, and if there is one find the node
      if (this_tile.exitIsValid(direction::LEFT))
      {
        nodes[tile_count].connections[0].node =
          findNodeAtPoint(nodes[tile_count].position - Point(tile_size, 0));
      }
      if (this_tile.exitIsValid(direction::RIGHT))
      {
        nodes[tile_count].connections[1].node =
          findNodeAtPoint(nodes[tile_count].position + Point(tile_size, 0));
      }
      if (this_tile.exitIsValid(direction::UP))
      {
        nodes[tile_count].connections[2].node =
          findNodeAtPoint(nodes[tile_count].position - Point(0, tile_size));
      }
      if (this_tile.exitIsValid(direction::DOWN))
      {
        nodes[tile_count].connections[3].node =
          findNodeAtPoint(nodes[tile_count].position + Point(0, tile_size));
      }
      tile_count++;
    }
  }
}

/* Returns the node in the PathfindingMap that is at the given point */
PathNode* PathfindingMap::findNodeAtPoint(Point point)
{
  for (int i = 0; i < number_of_nodes; i++)
  {
    if (nodes[i].position == point)
    {
      return &nodes[i];
    }
  }
  return nullptr;
}

PathfindingMap::~PathfindingMap()
{
  delete[] nodes;
  nodes = nullptr;
}
