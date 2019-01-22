#ifndef PO_TILE
#define PO_TILE

#include "../Constants.h"
#include "../Core/DynamicSprite.h"
#include "../Core/FileHandler.h"
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>
#include <json.hpp>
using json = nlohmann::json;

class Tile
{
 public:
  explicit Tile(std::string tile_type = "DEFAULT");
  ~Tile() = default;

  Tile(const Tile&) = delete;

  bool exitIsValid(room_exits exit);
  bool entryIsValid(room_exits exit);
  bool hasPointOfInterest(point_of_interest poi);

  void configure(float x, float y, ASGE::Renderer* renderer);
  float getPositionX();
  float getPositionY();

  ASGE::Sprite* getSprite();

  float getWidth();
  float getHeight();

 private:
  json tile_data;
  FileHandler file_handler;
  ASGE::Sprite* sprite = nullptr;
};

#endif