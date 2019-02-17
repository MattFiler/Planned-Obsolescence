#include "../Characters/Boss.h"
#include "../Characters/Goon.h"
#include "../Characters/LabTechnician.h"
#include "../Characters/Security.h"
#include <memory>

class CharacterManager
{
 public:
  CharacterManager() = default;
  ~CharacterManager();

  bool canSpawn(character_type type);
  bool spawnCharacter(Boss* new_boss);
  bool spawnCharacter(Goon* new_goon);
  bool spawnCharacter(LabTechnician* new_technician);
  bool spawnCharacter(Security* new_security);

  void render(double delta_time);
  void update(double delta_time);

  void setMap(GameMap* current_map);
  void setCamera(Camera* scene_camera);

 private:
  template<class CharacterArray>
  void renderCharacter(CharacterArray character, int& character_count, double& delta_time);

  template<class CharacterArray>
  void updateCharacter(CharacterArray character, int& character_count, double& delta_time);

  GameMap* game_map = nullptr;
  Camera* camera = nullptr;
  ASGE::Renderer* renderer = nullptr;

  Boss** boss_instances = nullptr;
  int boss_count = 0;

  Goon** goon_instances = nullptr;
  int goon_count = 0;

  LabTechnician** technician_instances = nullptr;
  int technician_count = 0;

  Security** security_instances = nullptr;
  int security_count = 0;
};