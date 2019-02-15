#include "../Characters/Boss.h"
#include "../Characters/Goon.h"
#include "../Characters/LabTechnician.h"
#include "../Characters/Security.h"
#include <memory>

#define IS_TYPE(x) typeid(CharacterType) == typeid(x)

class CharacterManager
{
 public:
  CharacterManager() = default;
  ~CharacterManager();

  bool canSpawn(character_type type);

  /* Spawn a character */
  template<class CharacterType>
  bool spawnCharacter(CharacterType& new_character)
  {
    if (IS_TYPE(Goon) || IS_TYPE(Boss) || IS_TYPE(Security) || IS_TYPE(LabTechnician))
    {
      typedef typename AllCharacterData<CharacterType>::data character_data;
      int& character_count = character_data::count;
      CharacterType& character_instances = character_data::instances;

      // Create our array if it doesn't exist
      if (character_instances == nullptr)
      {
        character_instances = new CharacterType[new_character.getSpawnCap()];
      }

      // Spawn if we haven't exceeded our limits
      if (character_count < new_character.getSpawnCap())
      {
        new_character.wake(renderer);
        new_character.setCharacterID(character_count);
        new_character.generatePathfindingMap(game_map);
        AllCharacterData<CharacterType>::data.instances[character_count] = new_character;
        character_count++;
        return true;
      }
    }
    // We've exceeded our spawn limits, or have had the wrong type requested
    return false;
  }

  template<typename T>
  struct AllCharacterData;

  struct GoonData
  {
    Goon* instances = nullptr;
    int count = 0;
  };
  struct BossData
  {
    Boss* instances = nullptr;
    int count = 0;
  };
  struct TechnicianData
  {
    LabTechnician* instances = nullptr;
    int count = 0;
  };
  struct SecurityData
  {
    Security* instances = nullptr;
    int count = 0;
  };

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
  DebugText debug_text;
};