#include "Character.h"
using namespace std;

/* Load config on instantiation */
Character::Character()
{
  updateCoreConfig();
}

/* Allow character variations to update the config to suit their needs */
void Character::updateCoreConfig(std::string character_type)
{
  // Load our config and assign default values.
  string config_file("CONFIGS/characters_core.json");
  json temp_config = file_handler.openAsJSON(config_file);
  core_config = temp_config["DEFAULT"];

  // If we're requesting default, we can stop here.
  if (character_type == "DEFAULT")
  {
    return;
  }

  // If not, continue to override the selected character's details.
  temp_config = temp_config[character_type];
  for (json::iterator i = temp_config.begin(); i != temp_config.end(); ++i) {
    if (!temp_config[i.key()].is_null()) {
      core_config[i.key()] = i.value();
    }
  }
}

/* Adjust spawn position */
void Character::setPosition(int x, int y)
{
  core_config["spawn_pos"][0] = x;
  core_config["spawn_pos"][1] = y;
}

/* Toggle visibility */
void Character::setVisible(bool isVisible)
{
  core_config["is_visible"] = isVisible;
}

/* Adjust dimensions */
void Character::setDimensions(int w, int h)
{
  core_config["width"] = w;
  core_config["height"] = h;
}

/* Adjust movement speed */
void Character::setSpeed(int speed)
{
  core_config["movement_speed"] = speed;
}

/* Assign sprite */
void Character::setSprite(DynamicSprite &new_sprite)
{
  my_sprite = &new_sprite;
}

/* Return the spawn limit for this character class */
int Character::getSpawnCap()
{
  return core_config["spawn_cap"];
}

/* Check that we are visible for rendering */
bool Character::isVisible()
{
  return core_config["is_visible"];
}

/* Return the path to our character's sprite */
string Character::getSpritePath()
{
  return core_config["sprite"];
}

/* Return sprite */
DynamicSprite* Character::getSprite()
{
  return my_sprite;
}