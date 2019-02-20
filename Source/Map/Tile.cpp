#include "Tile.h"

/* Load our config on instantiation */
Tile::Tile(std::string tile_type, json* tile_big_config, ASGE::Renderer* renderer)
{
  // Load tile config
  tile_data.load(tile_big_config, tile_type, renderer);

  // Resize click area
  click_area.setWidth(tile_data.width);
  click_area.setHeight(tile_data.height);
}

/* Work out if we have the requested exit on this tile */
bool Tile::exitIsValid(direction exit)
{
  return tile_data.getCanExit(exit);
}

/* Work out if we have a specified point of interest on this tile */
bool Tile::hasSpecificPointOfInterest(point_of_interest poi)
{
  return (tile_data.poi == poi);
}

/* Check to see if we have ANY point of interest on this tile */
bool Tile::hasAnyPointOfInterest()
{
  return (tile_data.poi != point_of_interest::NONE_ON_THIS_TILE);
}

/* Return our POI state (e.g. open or closed for doors) */
poi_state Tile::getPointOfInterestState()
{
  return tile_data.state_of_poi;
}

/* Set our POI state */
void Tile::setPointOfInterestState(poi_state new_state)
{
  tile_data.state_of_poi = new_state;

  // Show/hide our specialist "alt-sprite" if needed
  if (new_state == poi_state::POI_IS_BROKEN)
  {
    tile_data.sprite->show();
  }
  else
  {
    tile_data.sprite->hide();
  }
}

/* Get accessibility - can we traverse this tile? */
tile_accessibility Tile::getTileAccessibility()
{
  return tile_data.traversal;
}

/* Configure our sprite and set position */
void Tile::configure(float x_position, float y_position)
{
  tile_data.updatePosition(x_position, y_position);
  click_area.setPosition(Point(tile_data.x_pos, tile_data.y_pos));
}

/* Return the X position of the tile */
float Tile::getPositionX()
{
  return tile_data.x_pos;
}

/* Get the Y position of the tile */
float Tile::getPositionY()
{
  return tile_data.y_pos;
}

/* Get the width of the tile */
float Tile::getWidth()
{
  return tile_data.width;
}

/* Get the height of the tile */
float Tile::getHeight()
{
  return tile_data.height;
}

/* Set tile index in its room */
void Tile::setIndexInRoom(int index)
{
  tile_data.index_in_room = index;
}

/* Set tile index in the whole map */
void Tile::setIndexInMap(int index)
{
  tile_data.index_in_map = index;
}

/* Return our sprite (only applies if we have a POI) */
std::shared_ptr<ScaledSpriteArray> Tile::getSprite()
{
  if (tile_data.poi != point_of_interest::NONE_ON_THIS_TILE)
  {
    return tile_data.sprite;
  }
  // I have no sympathy for people who don't check for a sprite before calling it.
  throw "Someone requested a tile's sprite when it didn't have one. That idiot was probably YOU!";
}

/* Get tile index in its room */
int Tile::getIndexInRoom()
{
  return tile_data.index_in_room;
}

/* Get tile index in the whole map */
int Tile::getIndexInMap()
{
  return tile_data.index_in_map;
}

/* Get description of tile POI */
std::string Tile::getTileName()
{
  return tile_data.poi_desc;
}