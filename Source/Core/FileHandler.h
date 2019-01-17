#include <json.hpp>
#include <string>
#include <sstream>
#include <Engine/FileIO.h>

using namespace std;
using json = nlohmann::json;

class FileHandler {
  public:
  json openAsJSON(string filename);
  string openAsString(string filename);
};