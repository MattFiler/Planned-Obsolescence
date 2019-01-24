#ifndef PO_CHARACTER
#define PO_CHARACTER

#include "../Core/DynamicSprite.h"
#include "../Core/FileHandler.h"
#include "../Core/PathfindingMap.h"
#include "../Core/Vector.h"

#include <Engine/Renderer.h>
#include <json.hpp>
#include <vector>
using json = nlohmann::json;

class Character
{
 public:
  Character();
  ~Character();

  void wake(ASGE::Renderer* passed_renderer);
  void updatePosition(double delta_time);

  void setSpawnPosition(int x_pos, int y_pos);
  void setVisible(bool isVisible);
  void setDimensions(int new_width, int new_height);
  void setSpeed(int speed);

  void generatePathfindingMap(GameMap* game_map);
  void linkPathfindingMap();
  bool calculateRouteToPoint(Point point);

  bool isVisible();
  unsigned long long getSpawnCap();
  int getSpawnCapAsInt();
  std::string getSpritePath();

  DynamicSprite* getSprite();
  ASGE::Renderer* getRenderer();

 protected:
  void updateCoreConfig(std::string character_type = "DEFAULT");
  void updateSprite();
  float calculateScoresOfNextDepth(PathNode* node,
                                   unsigned long long int depth,
                                   float best_score,
                                   Point point);

  Point position = Point(0, 0);
  Vector direction = Vector(0, 0);

  PathfindingMap* internal_map = nullptr;
  std::vector<PathNode*> current_route;
  unsigned long long route_index = 0;
  float distance_to_next_node = 0;

 private:
  void importConfig(json json_config);

  FileHandler file_handler;
  json character_config;

  DynamicSprite* my_sprite = nullptr;
  ASGE::Renderer* renderer = nullptr;
};

#endif