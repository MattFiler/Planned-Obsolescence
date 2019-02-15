//
// Created by tobyj on 19/01/2019.
//

#ifndef PLANNEDOBSOLESCENCE_LABMAP_H
#define PLANNEDOBSOLESCENCE_LABMAP_H

#include "../../Debug/DebugText.h"
#include "../../Map/GameMap.h"
#include "PathNode.h"

/**
 **   Acts as the internal map for each character, as they do not know if
 *    the actual map has changed until they encounter said change (e.g. a door
 *    has been locked.)
 */
struct PathfindingMap
{
 public:
  PathfindingMap() = default;
  explicit PathfindingMap(GameMap* current_map);
  ~PathfindingMap();

  PathfindingMap(const PathfindingMap&) = delete;
  PathfindingMap& operator=(const PathfindingMap&) = delete;

  void linkNodes();

  PathNode* nodes = nullptr;
  int number_of_nodes = 0;

 private:
  PathNode* findNodeAtPoint(Point point);
  GameMap* game_map = nullptr;
  DebugText debug_text;
};

#endif // PLANNEDOBSOLESCENCE_LABMAP_H
