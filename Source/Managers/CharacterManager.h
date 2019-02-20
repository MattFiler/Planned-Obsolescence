#ifndef PO_CHARACTER_MANAGER
#define PO_CHARACTER_MANAGER

#include "../Characters/Boss.h"
#include "../Characters/Goon.h"
#include "../Characters/LabTechnician.h"
#include "../Characters/Security.h"
#include "../Managers/UIManager.h"
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

  float getTotalGaugeValue(character_type character);
  float getHighestGaugeValue(character_type character);

  bool checkForClick(Point click, bool act_on_click = true);

  void render(double delta_time);
  void update(double delta_time);

  void setMap(GameMap* current_map);
  void setCamera(Camera* scene_camera);
  void setUIManager(UIManager* manager) { ui_manager = manager; };

 private:
  template<class CharacterArray>
  void renderCharacter(CharacterArray character, int& character_count, double& delta_time);

  template<class CharacterArray>
  void updateCharacter(CharacterArray character,
                       int& char_c,
                       int& char_visible_c,
                       float& char_gauge,
                       double& delta_time);

  template<class CharacterArray>
  bool clickedCharacterCheck(CharacterArray character,
                             int& character_count,
                             Point click,
                             bool act_on_click = true);

  GameMap* game_map = nullptr;
  Camera* camera = nullptr;
  UIManager* ui_manager = nullptr;
  ASGE::Renderer* renderer = nullptr;

  DebugText debug_text;

  Boss** boss_instances = nullptr;
  int boss_count = 0;
  int boss_visible_count = 0;
  float boss_gauge_sum = 0;
  float boss_gauge_highest = 0;

  Goon** goon_instances = nullptr;
  int goon_count = 0;
  int goon_visible_count = 0;
  float goon_gauge_sum = 0;
  float goon_gauge_highest = 0;

  LabTechnician** technician_instances = nullptr;
  int technician_count = 0;
  int technician_visible_count = 0;
  float technician_gauge_sum = 0;
  float technician_gauge_highest = 0;

  Security** security_instances = nullptr;
  int security_count = 0;
  int security_visible_count = 0;
  float security_gauge_sum = 0;
  float security_gauge_highest = 0;
};

#endif