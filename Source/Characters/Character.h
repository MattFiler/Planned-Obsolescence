#ifndef PO_CHARACTER
#define PO_CHARACTER

#include <json.hpp>
#include "../Core/DynamicSprite.h"
#include "../Core/FileHandler.h"
#include <Engine/Renderer.h>
using json = nlohmann::json;

class Character
{
 public:
  Character();
  ~Character() = default;

  // Assign the renderer for working with sprites
  void wake(ASGE::Renderer* passed_renderer);

  // Modify character config on-the-fly
  void setSpawnPosition(int x, int y);
  void setVisible(bool isVisible);
  void setDimensions(int w, int h);
  void setSpeed(int speed);

  // Get character config data
  bool isVisible();
  int getSpawnCap();
  std::string getSpritePath();

  // Get character components
  DynamicSprite* getSprite();
  ASGE::Renderer* getRenderer();

 protected:
  void updateCoreConfig(std::string character_type = "DEFAULT");
  void updateSprite();

 private:
  void importConfig(json json_config);

  FileHandler file_handler;
  json character_config;

  DynamicSprite* my_sprite = nullptr;
  ASGE::Renderer* renderer = nullptr;
};

#endif