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

 private:
  Boss** bosses = nullptr;
  int boss_count = 0;

  Goon** goons = nullptr;
  int goon_count = 0;

  LabTechnician** techies = nullptr;
  int techie_count = 0;

  Security** guards = nullptr;
  int guard_count = 0;
};