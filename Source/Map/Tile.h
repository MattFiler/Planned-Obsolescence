#ifndef PO_TILE
#define PO_TILE

#include "../Constants.h"
#include "../Core/Camera.h"
#include "../Core/DynamicSprite.h"
#include "../Core/FileHandler.h"
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>
#include <json.hpp>
using json = nlohmann::json;

class Tile
{
 public:
  Tile(std::string tile_type, json* tile_big_config);
  ~Tile() = default;

  bool exitIsValid(direction exit);
  bool entryIsValid(direction exit);
  bool hasPointOfInterest(point_of_interest poi);

  void configure(float x_position, float y_position, ASGE::Renderer* renderer);
  float getPositionX();
  float getPositionY();

  void setIndexInRoom(int index);
  void setIndexInMap(int index);
  int getIndexInRoom();
  int getIndexInMap();

  std::shared_ptr<DynamicSprite> getSprite();

  float getWidth();
  float getHeight();

 private:
  json tile_config;
  FileHandler file_handler;
  std::shared_ptr<DynamicSprite> sprite = nullptr;

  float x_pos = 0;
  float y_pos = 0;

  int tile_index_in_room = 0;
  int tile_index_in_map = 0;
};

#endif