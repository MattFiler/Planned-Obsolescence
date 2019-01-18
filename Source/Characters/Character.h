#ifndef PO_CHARACTER
#define PO_CHARACTER

#include <json.hpp>
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

  // Get character config data
  bool isVisible();
  int getSpawnCap();

 protected:
  void updateCoreConfig(std::string character_type = "DEFAULT");

 private:
  FileHandler file_handler;
  json core_config;
};

#endif