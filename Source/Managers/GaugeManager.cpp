#include "GaugeManager.h"

GaugeManager::~GaugeManager()
{
  // delete ui_manager;
  // ui_manager = nullptr;
}

/* Handle our per-frame updates and check game over state */
game_over_type GaugeManager::update(double dt_sec)
{
  increasePlayerPower(dt_sec);
  decreaseProjectTimeRemaining(dt_sec);

  float detection_gauge = character_manager->getHighestGaugeValue(character_type::SECURITY);
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::PROJECT_PROGRESS, project_progress);
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::TIME_REMAINING, project_time_remaining);
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::YOUR_DETECTION, detection_gauge);
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::PLAYER_POWER, player_power);

  if (project_time_remaining == gauge_levels::GAUGE_EMPTY)
  {
    if (project_progress != gauge_levels::GAUGE_FULL && detection_gauge != gauge_levels::GAUGE_FULL)
    {
      return game_over_type::PLAYER_WON;
    }
    return game_over_type::PLAYER_LOST;
  }
  else if (project_progress == gauge_levels::GAUGE_FULL)
  {
    return game_over_type::PLAYER_LOST;
  }
  else if (detection_gauge == gauge_levels::GAUGE_FULL)
  {
    return game_over_type::PLAYER_LOST;
  }
  return game_over_type::NOT_YET_DECIDED;
}

/* Increase project progress */
void GaugeManager::incrementProjectProgress(float add_progress)
{
  if (project_progress + add_progress > gauge_levels::GAUGE_FULL)
  {
    project_progress = gauge_levels::GAUGE_FULL;
  }
  else
  {
    project_progress += add_progress;
  }
}

/* Increase player's power */
void GaugeManager::decreasePlayerPower(float decrease_power)
{
  if (player_power - decrease_power < gauge_levels::GAUGE_EMPTY)
  {
    player_power = gauge_levels::GAUGE_EMPTY;
  }
  else
  {
    player_power -= decrease_power;
  }
}

/* Decrease project timer based on delta time */
void GaugeManager::decreaseProjectTimeRemaining(double dt_sec)
{
  dt_sec /= gauge_rates::PROJECT_TIMER;
  if (project_time_remaining - static_cast<float>(dt_sec) < gauge_levels::GAUGE_EMPTY)
  {
    project_time_remaining = gauge_levels::GAUGE_EMPTY;
  }
  else
  {
    project_time_remaining -= static_cast<float>(dt_sec);
  }
}

/* Decrease player's power based on delta time */
void GaugeManager::increasePlayerPower(double dt_sec)
{
  dt_sec /= gauge_rates::POWER;
  if (player_power + static_cast<float>(dt_sec) > gauge_levels::GAUGE_FULL)
  {
    player_power = gauge_levels::GAUGE_FULL;
  }
  else
  {
    player_power += static_cast<float>(dt_sec);
  }
}

/* Get project progress */
float GaugeManager::getProjectProgress()
{
  return project_progress;
}

/* Get remaining project time */
float GaugeManager::getProjectTimeRemaining()
{
  return project_time_remaining;
}

/* Get the player's current power value */
float GaugeManager::getPlayerPower()
{
  return player_power;
}