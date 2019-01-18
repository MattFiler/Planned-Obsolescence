#ifndef PO_CHARACTER
#define PO_CHARACTER

#include <json.hpp>
#include "../Core/DynamicSprite.h"
#include "../Core/FileHandler.h"
using json = nlohmann::json;

class Character
{
 public:
  Character();
  ~Character() = default;

  // Modify character config on-the-fly
  void setPosition(int x, int y);
  void setVisible(bool isVisible);
  void setDimensions(int w, int h);
  void setSpeed(int speed);

  // Set character components
  void setSprite(DynamicSprite &new_sprite);

  // Get character config data
  bool isVisible();
  int getSpawnCap();
  std::string getSpritePath();

  // Get character components
  DynamicSprite* getSprite();

 protected:
  void updateCoreConfig(std::string character_type = "DEFAULT");

 private:
  FileHandler file_handler;
  json core_config;
  DynamicSprite* my_sprite;
};

#endif