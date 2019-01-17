#include <Engine/FileIO.h>
#include <json.hpp>
#include <sstream>
#include <string>

using namespace std;
using json = nlohmann::json;

class FileHandler
{
  public:
  json openAsJSON(string filename);
  string openAsString(string filename);
};