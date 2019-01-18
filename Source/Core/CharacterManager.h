#include "../Characters/Boss.h"
#include "../Characters/Goon.h"
#include "../Characters/LabTechnician.h"
#include "../Characters/Security.h"

class CharacterManager {
 public:
  CharacterManager();
  ~CharacterManager() = default;

  bool spawnBoss(Boss &new_boss);
  bool spawnGoon(Goon &new_goon);
  bool spawnTechnician(LabTechnician &new_techie);
  bool spawnGuard(Security &new_guard);

  void renderAll(double delta_time, ASGE::Renderer* renderer);

 private:
  void renderBosses(double delta_time, ASGE::Renderer* renderer);
  void renderGoons(double delta_time, ASGE::Renderer* renderer);
  void renderTechnicians(double delta_time, ASGE::Renderer* renderer);
  void renderSecurity(double delta_time, ASGE::Renderer* renderer);

  Boss* bosses = nullptr;
  int boss_count = 0;

  Goon* goons = nullptr;
  int goon_count = 0;

  LabTechnician* techies = nullptr;
  int techie_count = 0;

  Security* guards = nullptr;
  int guard_count = 0;
};