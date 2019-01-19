#ifndef PLANNEDOBSOLESCENCE_MAPNODE_H
#define PLANNEDOBSOLESCENCE_MAPNODE_H

#include <vector>
#include "Geometry.h"

struct MapNode
{
  Vector position;
  std::vector<MapNode> connected_nodes;

};

#endif //PLANNEDOBSOLESCENCE_MAPNODE_H
