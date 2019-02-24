#ifndef PO_CHARACTER
#define PO_CHARACTER

#include "../Characters/Pathfinding/PathfindingMap.h"
#include "../ConfigParsers/CharacterData.h"
#include "../Debug/DebugText.h"
#include "../Math/Vector.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "../Viewport/ClickArea.h"

#include <Engine/Renderer.h>
#include <vector>

/**
 **   The parent class for all characters in the game, defines all their shared functionality, most
 *importantly their pathfinding algorithm.
 */
class Character
{
 public:
  explicit Character(character_type type);
  virtual ~Character();

  void wake(ASGE::Renderer* passed_renderer);
  virtual void update(double delta_time) { updatePosition(delta_time); };
  virtual void lockedDoorFound(){};
  bool updatePosition(double delta_time);

  void setSpawnPositionX(float x_pos);
  void setSpawnPositionY(float y_pos);
  void setSpawnPosition(float x_pos, float y_pos);
  void setVisible(bool is_visible);
  void setSpeed(int speed);

  void generatePathfindingMap(GameMap* game_map);
  bool calculateRouteToPoint(Point point);
  void resetPathfindingMap();
  Point findPositionForPOI(Point point, Room* room);
  Point findPositionForPOI(Point point);

  bool isVisible();
  int getSpawnCap();
  int getSpawnCapAsInt();
  Point getPosition() { return position; };

  bool isPointInArea(Point point) { return click_area.isPointInArea(point); };
  void updateTimeBetweenFrames(double new_time);

  tile_exit getDirection() { return config.currently_facing; };
  void setDirection(tile_exit new_direction) { config.currently_facing = new_direction; };

  void setCharacterID(int index);
  std::string getCharacterID();
  int getIndex();
  character_type getCharacterType();

  ScaledSpriteArray* getSprite();
  ASGE::Renderer* getRenderer();

  float getInternalGauge();
  void reduceInternalGauge(float reduce_by = 1);
  std::string getInternalGaugeDesc();

  std::string getDisplayName();

 protected:
  float calculateScoresOfNextDepth(PathNode* node,
                                   unsigned long long int depth,
                                   float best_score,
                                   Point point);
  void clearPathfindingMapScores();

  Point position = Point(0, 0);
  Vector direction = Vector(0, 0);

  PathfindingMap* internal_map = nullptr;
  GameMap* global_map = nullptr;
  std::vector<PathNode*> current_route;

  unsigned long long route_index = 0;
  float distance_to_next_node = 0;
  int iteration_count = 0;

  ClickArea click_area;
  CharacterData config;

  float speed_multiplier = 1;

 private:
  void importConfig(json json_config);

  ASGE::Renderer* renderer = nullptr;

  DebugText debug_text;
};

#endif