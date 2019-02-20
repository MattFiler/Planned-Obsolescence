#include "GaugeManager.h"

GaugeManager::~GaugeManager()
{
  delete ui_manager;
  ui_manager = nullptr;
}

/* Handle our per-frame updates */
void GaugeManager::update(double dt_sec)
{
  decreasePlayerPower(dt_sec / 1000);
  decreaseProjectTimeRemaining(dt_sec / 1000);

  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::PROJECT_PROGRESS, project_progress);
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::TIME_REMAINING, project_time_remaining);
  ui_manager->getMainHUD()->adjustGauge(
    hud_gauge_types::YOUR_DETECTION,
    character_manager->getHighestGaugeValue(character_type::SECURITY));
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::PLAYER_POWER, player_power);
}

/* Increase project progress */
void GaugeManager::incrementProjectProgress(float add_progress)
{
  if (project_progress + add_progress > 100)
  {
    project_progress = 100;
  }
  else
  {
    project_progress += add_progress;
  }
}

/* Increase player's power */
void GaugeManager::increasePlayerPower(float increase_power)
{
  if (player_power + increase_power > 100)
  {
    player_power = 100;
  }
  else
  {
    player_power += increase_power;
  }
}

/* Decrease project timer based on delta time */
void GaugeManager::decreaseProjectTimeRemaining(double dt_sec)
{
  if (project_time_remaining - static_cast<float>(dt_sec) < 0)
  {
    project_time_remaining = 0;
  }
  else
  {
    project_time_remaining -= static_cast<float>(dt_sec);
  }
}

/* Decrease player's power based on delta time */
void GaugeManager::decreasePlayerPower(double dt_sec)
{
  if (player_power - static_cast<float>(dt_sec) < 0)
  {
    player_power = 0;
  }
  else
  {
    player_power -= static_cast<float>(dt_sec);
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