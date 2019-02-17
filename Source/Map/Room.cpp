#include "Room.h"
using namespace std;

/* Load config and tiles on instantiation */
Room::Room(string room_name, json* room_big_config, json* tile_big_config)
{
  // Load configs
  room_data.load(room_big_config, room_name);
  tile_config = tile_big_config;
}

/* Build our room */
void Room::build(float room_x, float room_y, ASGE::Renderer* renderer, int tile_offset)
{
  // Load room sprite
  room_data.loadSprite(renderer);

  // Store position data
  room_data.updatePosition(room_x, room_y);

  // Load all tiles into room at the correct position and add up room size
  float tile_x = room_data.x_pos;
  float tile_y = room_data.y_pos;
  float y_modifier = 0.0f;
  for (int i = 0; i < room_data.tile_count; i++)
  {
    room_data.tiles.emplace_back(room_data.tile_names[i], tile_config, renderer);
    room_data.tiles[i].configure(tile_x, tile_y);
    room_data.tiles[i].setIndexInRoom(i);
    room_data.tiles[i].setIndexInMap(tile_offset + i);

    if ((i + 1) % room_data.tiles_x == 0)
    {
      float new_room_w = tile_x - room_data.x_pos + room_data.tiles[i].getWidth();

      tile_x = room_data.x_pos;
      tile_y += y_modifier;
      y_modifier = 0.0f;

      if (room_data.width < new_room_w)
      {
        room_data.width = new_room_w;
      }
      if (room_data.height < tile_y - room_data.y_pos)
      {
        room_data.height = tile_y - room_data.y_pos;
      }
    }
    else
    {
      tile_x += room_data.tiles[i].getWidth();
      if (room_data.tiles[i].getHeight() > y_modifier)
      {
        y_modifier = room_data.tiles[i].getHeight();
      }
    }
  }

  // Update sprite size
  room_data.refreshSpriteSize();
}

/* Return our sprite */
shared_ptr<ScaledSpriteArray> Room::getSprite()
{
  return room_data.sprite;
}

/* Return room width */
float Room::getWidth()
{
  return room_data.width;
}

/* Return room height */
float Room::getHeight()
{
  return room_data.height;
}

/* Return room position X */
float Room::getPositionX()
{
  return room_data.y_pos;
}

/* Return room position Y */
float Room::getPositionY()
{
  return room_data.y_pos;
}

/* Return all tiles in the room */
vector<Tile> Room::getTiles()
{
  return room_data.tiles;
}

/* Return the number of tiles in the room */
int Room::getTileCount()
{
  return room_data.tile_count;
}