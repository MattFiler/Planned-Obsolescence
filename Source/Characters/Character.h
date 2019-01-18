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

  bool isVisible();

 protected:
  void updateCoreConfig(std::string character_type = "DEFAULT");

 private:
  FileHandler file_handler;
  json core_config;
};

#endif