#ifndef PLANNEDOBSOLESCENCE_UNIVERSALGAUGE_H
#define PLANNEDOBSOLESCENCE_UNIVERSALGAUGE_H

#include "CharacterManager.h"
#include "UIManager.h"

class GaugeManager
{
 public:
  GaugeManager() = default;
  ~GaugeManager();

  void setUIManager(UIManager* manager) { ui_manager = manager; };
  void setCharacterManager(CharacterManager* manager) { character_manager = manager; };

  void incrementProjectProgress(float add_progress);
  void decreasePlayerPower(float decrease_power);

  game_over_type update(double dt_sec);

  float getProjectProgress();
  float getProjectTimeRemaining();
  float getPlayerPower();

 private:
  void decreaseProjectTimeRemaining(double dt_sec);
  void increasePlayerPower(double dt_sec);

  float project_progress = gauge_levels::GAUGE_EMPTY;
  float project_time_remaining = gauge_levels::GAUGE_FULL;
  float player_power = gauge_levels::GAUGE_FULL;

  UIManager* ui_manager;
  CharacterManager* character_manager;
};

#endif // PLANNEDOBSOLESCENCE_UNIVERSALGAUGE_H
