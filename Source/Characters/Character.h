#ifndef PO_CHARACTER
#define PO_CHARACTER

#include "../ConfigParsers/CharacterData.h"
#include "../Core/DebugText.h"
#include "../Core/DynamicSprite.h"
#include "../Core/PathfindingMap.h"
#include "../Core/Vector.h"

#include <Engine/Renderer.h>
#include <vector>

/**
 **   The parent class for all characters in the game, defines all their shared functionality, most
 *importantly their pathfinding algorithm.
 */
class Character
{
 public:
  Character();
  ~Character();

  void wake(ASGE::Renderer* passed_renderer);
  void updatePosition(double delta_time);

  void setSpawnPositionX(int x_pos);
  void setSpawnPositionY(int y_pos);
  void setSpawnPosition(int x_pos, int y_pos);
  void setVisible(bool is_visible);
  void setDimensions(int new_width, int new_height);
  void setSpeed(int speed);

  void generatePathfindingMap(GameMap* game_map);
  bool calculateRouteToPoint(Point point);
  void resetPathfindingMap();

  bool isVisible();
  int getSpawnCap();
  int getSpawnCapAsInt();
  std::string getSpritePath();

  void setCharacterID(int index);
  std::string getCharacterID();
  int getIndex();

  DynamicSprite* getSprite();
  ASGE::Renderer* getRenderer();
  std::vector<PathNode*> current_route;

 protected:
  void updateCoreConfig(character_type type = character_type::DEFAULT);
  void updateSprite();
  float calculateScoresOfNextDepth(PathNode* node,
                                   unsigned long long int depth,
                                   float best_score,
                                   Point point);
  void clearPathfindingMapScores();

  Point position = Point(0, 0);
  Vector direction = Vector(0, 0);

  PathfindingMap* internal_map = nullptr;

  unsigned long long route_index = 0;
  float distance_to_next_node = 0;

 private:
  void importConfig(json json_config);

  CharacterData config;

  DynamicSprite* sprite = nullptr;
  ASGE::Renderer* renderer = nullptr;

  DebugText debug_text;
};

#endif