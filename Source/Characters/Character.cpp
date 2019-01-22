#include "Character.h"
using namespace std;

/* Load config on instantiation */
Character::Character()
{
  // Load default config
  updateCoreConfig();
}

/* Catch the renderer, then we can load our sprite */
void Character::wake(ASGE::Renderer* passed_renderer)
{
  renderer = passed_renderer;
  updateSprite();
}

/* Allow character variations to update the config to suit their needs */
void Character::updateCoreConfig(std::string character_type)
{
  character_config = file_handler.loadConfig("characters_core.json", character_type);
}

/* Update our sprite */
void Character::updateSprite()
{
  delete my_sprite;
  my_sprite = new DynamicSprite(1);
  ASGE::Sprite* new_sprite = renderer->createRawSprite();
  new_sprite->loadTexture(getSpritePath());
  my_sprite->addSprite(*new_sprite);
}

/* Adjust spawn position */
void Character::setSpawnPosition(int x, int y)
{
  character_config["spawn_pos"][0] = x;
  character_config["spawn_pos"][1] = y;
}

/* Toggle visibility */
void Character::setVisible(bool isVisible)
{
  character_config["is_visible"] = isVisible;
}

/* Adjust dimensions */
void Character::setDimensions(int w, int h)
{
  character_config["width"] = w;
  character_config["height"] = h;
}

/* Adjust movement speed */
void Character::setSpeed(int speed)
{
  character_config["movement_speed"] = speed;
}

/* Return the spawn limit for this character class */
int Character::getSpawnCap()
{
  return character_config["spawn_cap"];
}

/* Check that we are visible for rendering */
bool Character::isVisible()
{
  return character_config["is_visible"];
}

/* Return the path to our character's sprite */
string Character::getSpritePath()
{
  return character_config["sprites"]["walking"][0];
}

/* Return sprite */
DynamicSprite* Character::getSprite()
{
  return my_sprite;
}

/* Return renderer */
ASGE::Renderer* Character::getRenderer()
{
  return renderer;
}