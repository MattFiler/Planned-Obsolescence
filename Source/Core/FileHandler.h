#ifndef PO_FILEHANDLER
#define PO_FILEHANDLER

#include <Engine/FileIO.h>
#include <json.hpp>
#include <sstream>
#include <string>
using json = nlohmann::json;

class FileHandler
{
  public:
  json openAsJSON(std::string& filename);
  std::string openAsString(std::string& filename);
};

#endif