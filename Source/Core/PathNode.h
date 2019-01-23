#ifndef PLANNEDOBSOLESCENCE_MAPNODE_H
#define PLANNEDOBSOLESCENCE_MAPNODE_H

#include "NodeConnection.h"
#include "Point.h"

/**
 **   Similar to the tile class, but with relevant information for path-finding.
 *    Used to build the internal map for characters
 */
struct PathNode
{
  Point position;
  NodeConnection connections[4];
  bool visited = false;
};

#endif // PLANNEDOBSOLESCENCE_MAPNODE_H
