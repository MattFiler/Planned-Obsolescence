//
// Created by tobyj on 19/01/2019.
//

#ifndef PLANNEDOBSOLESCENCE_LABMAP_H
#define PLANNEDOBSOLESCENCE_LABMAP_H

#include "PathNode.h"

/**
 **   Acts as the internal map for each character, as they do not know if
 *    the actual map has changed until they encounter said change (e.g. a door
 *    has been locked.)
 */
struct PathfindingMap
{
  PathNode* nodes = nullptr;
  int number_of_nodes = 0;
};

#endif // PLANNEDOBSOLESCENCE_LABMAP_H
