#include "../Characters/Boss.h"
#include "../Characters/Goon.h"
#include "../Characters/LabTechnician.h"
#include "../Characters/Security.h"

class CharacterManager
{
  public:
  CharacterManager() = default;
  ~CharacterManager();

  bool spawn(Boss& new_boss);
  bool spawn(Goon& new_goon);
  bool spawn(LabTechnician& new_techie);
  bool spawn(Security& new_guard);

  void render(double delta_time, ASGE::Renderer* renderer);

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