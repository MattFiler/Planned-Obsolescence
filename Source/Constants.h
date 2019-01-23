/**
 @brief   Constants that are used throughout the game.
 @details Add any new constants to this file.
*/

#ifndef PO_CONSTANTS
#define PO_CONSTANTS

enum character_type
{
  BOSS,
  GOON,
  TECHNICIAN,
  SECURITY
};

enum direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};

enum point_of_interest
{
  COMPUTER,
  DOOR
};

const float SCREEN_WIDTH = 1280;
const float SCREEN_HEIGHT = 720;

#endif