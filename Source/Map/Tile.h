#include "../Constants.h"
#include "../Core/FileHandler.h"
#include <json.hpp>
using json = nlohmann::json;

class Tile
{
 public:
  Tile(std::string tile_type = "DEFAULT");
  ~Tile() = default;

  bool exitIsValid(room_exits exit);
  bool entryIsValid(room_exits exit);
  bool hasPointOfInterest(point_of_interest poi);

 private:
  json tile_data;
  FileHandler file_handler;
};