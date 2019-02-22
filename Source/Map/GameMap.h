#ifndef PO_MAP
#define PO_MAP

#include "../ConfigParsers/MapData.h"
#include "../Constants.h"
#include "../Debug/DebugText.h"
#include "../Managers/UIManager.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "Room.h"
#include <Engine/Renderer.h>

class GameMap
{
 public:
  GameMap();
  ~GameMap() = default;

  void load(ASGE::Renderer* renderer_instance, Camera* camera);
  void render(double delta_time);

  void setUIManager(UIManager* manager) { ui_manager = manager; };

  std::vector<Room>* getRooms();
  int getRoomCount();
  int getTileCount();
  MapData* getMapData() { return &map_data; };
  std::shared_ptr<ScaledSpriteArray> getSprite();

  int getRoomsX() { return map_data.rooms_x; };
  int getRoomsY() { return map_data.rooms_y; };
  Point getMapSize() { return Point(map_data.map_width, map_data.map_height); }

  bool isPOIStateAtPoint(poi_state poi_state, Point point);
  Tile* getTileAtPoint(Point point);

  bool clickedPointCheck(Point click, bool act_on_click = true);

 private:
  void importJSON();

  // JSON configs
  json map_config;
  json room_config;
  json tile_config;

  // Map data
  MapData map_data;

  // Engine features
  FileHandler file_handler;
  DebugText debug_text;
  Camera* game_camera = nullptr;
  ASGE::Renderer* renderer = nullptr;
  UIManager* ui_manager = nullptr;
};

#endif