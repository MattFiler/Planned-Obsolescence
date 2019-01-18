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
  // Load our config and assign default values.
  string config_file("CONFIGS/characters_core.json");
  json temp_config = file_handler.openAsJSON(config_file);
  json json_config = temp_config["DEFAULT"];

  // If we're requesting default, we can stop here.
  if (character_type == "DEFAULT")
  {
    importConfig(json_config);
    return;
  }

  // If not, continue to override the selected character's details.
  temp_config = temp_config[character_type];
  for (json::iterator i = temp_config.begin(); i != temp_config.end(); ++i) {
    if (!temp_config[i.key()].is_null()) {
      json_config[i.key()] = i.value();
    }
  }
  importConfig(json_config);
}

void Character::importConfig(json json_config)
{
  config.my_sprite = "data/CHARACTERS/DEFAULT/placeholder.png";
  config.width = json_config["width"];
  config.height = json_config["height"];
  config.is_visible = json_config["is_visible"];
  config.spawn_pos[0] = json_config["spawn_pos"][0];
  config.spawn_pos[1] = json_config["spawn_pos"][1];
  config.spawn_cap = json_config["spawn_cap"];
  config.movement_speed = json_config["movement_speed"];
  config.max_health = json_config["max_health"];
  config.suspicion_gauge = json_config["suspicion"];
  config.stress_gauge = json_config["stress"];
  config.productivity_gauge = json_config["productivity"];
  config.faith_gauge = json_config["faith"];
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
  config.spawn_pos[0] = x;
  config.spawn_pos[1] = y;
}

/* Toggle visibility */
void Character::setVisible(bool isVisible)
{
  config.is_visible = isVisible;
}

/* Adjust dimensions */
void Character::setDimensions(int w, int h)
{
  config.width = w;
  config.height = h;
}

/* Adjust movement speed */
void Character::setSpeed(int speed)
{
  config.movement_speed = speed;
}

/* Return the spawn limit for this character class */
int Character::getSpawnCap()
{
  return config.spawn_cap;
}

/* Check that we are visible for rendering */
bool Character::isVisible()
{
  return config.is_visible;
}

/* Return the path to our character's sprite */
string Character::getSpritePath()
{
  return config.my_sprite;
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