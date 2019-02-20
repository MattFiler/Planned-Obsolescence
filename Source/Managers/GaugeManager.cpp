#include "GaugeManager.h"

GaugeManager::~GaugeManager()
{
  // delete ui_manager;
  // ui_manager = nullptr;
}

/* Handle our per-frame updates and check game over state */
game_over_type GaugeManager::update(double dt_sec)
{
  // Modify time-based data
  increasePlayerPower(dt_sec);
  increaseProjectProgress(dt_sec);
  decreaseProjectTimeRemaining(dt_sec);

  // Update static data
  gauge_data.productivity = character_manager->getTotalGaugeValue(character_type::GOON);
  gauge_data.detection = character_manager->getHighestGaugeValue(character_type::SECURITY);

  // Adjust UI
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::PROJECT_PROGRESS,
                                        gauge_data.project_progress);
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::TIME_REMAINING,
                                        gauge_data.project_time_remaining);
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::YOUR_DETECTION, gauge_data.detection);
  ui_manager->getMainHUD()->adjustGauge(hud_gauge_types::PLAYER_POWER, gauge_data.player_power);

  // Check for a win condition
  if (gauge_data.project_time_remaining == gauge_levels::GAUGE_EMPTY)
  {
    if (gauge_data.project_progress != gauge_levels::GAUGE_FULL &&
        gauge_data.detection != gauge_levels::GAUGE_FULL)
    {
      return game_over_type::PLAYER_WON;
    }
    return game_over_type::PLAYER_LOST;
  }
  else if (gauge_data.project_progress == gauge_levels::GAUGE_FULL)
  {
    return game_over_type::PLAYER_LOST;
  }
  else if (gauge_data.detection == gauge_levels::GAUGE_FULL)
  {
    return game_over_type::PLAYER_LOST;
  }
  return game_over_type::NOT_YET_DECIDED;
}

/* Increase project progress */
void GaugeManager::incrementProjectProgress(float add_progress)
{
  if (gauge_data.project_progress + add_progress > gauge_levels::GAUGE_FULL)
  {
    gauge_data.project_progress = gauge_levels::GAUGE_FULL;
  }
  else
  {
    gauge_data.project_progress += add_progress;
  }
}

/* Decrease player's power by a set amount */
void GaugeManager::decreasePlayerPower(float decrease_power)
{
  if (gauge_data.player_power - decrease_power < gauge_levels::GAUGE_EMPTY)
  {
    gauge_data.player_power = gauge_levels::GAUGE_EMPTY;
  }
  else
  {
    gauge_data.player_power -= decrease_power;
  }
}

/* Decrease project timer based on delta time */
void GaugeManager::decreaseProjectTimeRemaining(double dt_sec)
{
  dt_sec /= gauge_rates::PROJECT_TIMER;
  if (gauge_data.project_time_remaining - static_cast<float>(dt_sec) < gauge_levels::GAUGE_EMPTY)
  {
    gauge_data.project_time_remaining = gauge_levels::GAUGE_EMPTY;
  }
  else
  {
    gauge_data.project_time_remaining -= static_cast<float>(dt_sec);
  }
}

/* Increase player's power based on delta time */
void GaugeManager::increasePlayerPower(double dt_sec)
{
  dt_sec /= gauge_rates::POWER;
  if (gauge_data.player_power + static_cast<float>(dt_sec) > gauge_levels::GAUGE_FULL)
  {
    gauge_data.player_power = gauge_levels::GAUGE_FULL;
  }
  else
  {
    gauge_data.player_power += static_cast<float>(dt_sec);
  }
}

/* Increase project progress based on delta time and productivity */
void GaugeManager::increaseProjectProgress(double dt_sec)
{
  // Work out what we should add on (time in ms divided by modifier * by normalised productivity)
  dt_sec /= gauge_rates::TOTAL_PROGRESS;
  dt_sec *= (gauge_data.productivity / gauge_levels::GAUGE_FULL);
  if (gauge_data.project_progress + static_cast<float>(dt_sec) > gauge_levels::GAUGE_FULL)
  {
    gauge_data.project_progress = gauge_levels::GAUGE_FULL;
  }
  else
  {
    gauge_data.project_progress += static_cast<float>(dt_sec);
  }
}

/* reset all gauges */
void GaugeManager::resetAll()
{
  gauge_data.project_progress = gauge_levels::GAUGE_EMPTY;
  gauge_data.productivity = gauge_levels::GAUGE_FULL;
  gauge_data.player_power = gauge_levels::GAUGE_FULL;
  gauge_data.detection = gauge_levels::GAUGE_EMPTY;
  gauge_data.project_time_remaining = gauge_levels::GAUGE_FULL;
}

/* Get project progress */
float GaugeManager::getProjectProgress()
{
  return gauge_data.project_progress;
}

/* Get remaining project time */
float GaugeManager::getProjectTimeRemaining()
{
  return gauge_data.project_time_remaining;
}

/* Get the player's current power value */
float GaugeManager::getPlayerPower()
{
  return gauge_data.player_power;
}