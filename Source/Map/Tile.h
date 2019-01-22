#ifndef PO_TILE
#define PO_TILE

#include "../Constants.h"
#include "../Core/DynamicSprite.h"
#include "../Core/FileHandler.h"
#include <Engine/Renderer.h>
#include <json.hpp>
using json = nlohmann::json;

class Tile
{
 public:
  Tile(std::string tile_type = "DEFAULT", ASGE::Renderer* renderer = nullptr);
  ~Tile() = default;

  bool exitIsValid(room_exits exit);
  bool entryIsValid(room_exits exit);
  bool hasPointOfInterest(point_of_interest poi);

  DynamicSprite* getSprite();

 private:
  json tile_data;
  FileHandler file_handler;
  DynamicSprite* my_sprite = nullptr;
};

#endif