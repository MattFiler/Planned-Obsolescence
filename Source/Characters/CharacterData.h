#include <string>

struct CharacterData {
  std::string my_sprite;
  int width;
  int height;
  bool is_visible;

  int spawn_pos[2];
  int spawn_cap;

  int movement_speed;
  int max_health;

  int suspicion_gauge;
  int stress_gauge;
  int productivity_gauge;
  int faith_gauge;
};