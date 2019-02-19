#ifndef PO_TILE
#define PO_TILE

#include "../ConfigParsers/TileData.h"
#include "../Constants.h"
#include "../FileHandler/FileHandler.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "../Viewport/Camera.h"
#include "../Viewport/ClickArea.h"
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>

class Tile
{
 public:
  Tile(std::string tile_type, json* tile_big_config, ASGE::Renderer* renderer);
  ~Tile() = default;

  bool exitIsValid(direction exit);

  bool hasSpecificPointOfInterest(point_of_interest poi);
  bool hasAnyPointOfInterest();
  poi_state getPointOfInterestState();
  void setPointOfInterestState(poi_state new_state);

  tile_accessibility getTileAccessibility();

  bool isPointOnTile(Point point) { return click_area.isPointInArea(point); };

  void configure(float x_position, float y_position);
  float getPositionX();
  float getPositionY();

  void setIndexInRoom(int index);
  void setIndexInMap(int index);
  int getIndexInRoom();
  int getIndexInMap();

  std::shared_ptr<ScaledSpriteArray> getSprite();

  float getWidth();
  float getHeight();

 private:
  // Engine features
  FileHandler file_handler;

  // Tile data
  ClickArea click_area;
  TileData tile_data;
};

#endif