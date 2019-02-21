#ifndef PLANNEDOBSOLESCENCE_MAINHUD_H
#define PLANNEDOBSOLESCENCE_MAINHUD_H

#include "Button.h"
#include "HudGaugeData.h"
#include "ProgressBar.h"
#include "UI.h"

class MainHUD : public UI
{
 public:
  explicit MainHUD(ASGE::Renderer* rend);
  ~MainHUD() override;

  MainHUD(const MainHUD&) = delete;
  MainHUD& operator=(const MainHUD&) = delete;

  void render(double delta_time) override;

  void adjustGauge(hud_gauge_types bar, float gauge_amount);

 private:
  ScaledSpriteArray* background_sprite = nullptr;
  std::vector<HudGaugeData*> hud_gauges;

  HudGaugeData* gauge_detection = nullptr;
  HudGaugeData* gauge_progress = nullptr;
  HudGaugeData* gauge_timeremaining = nullptr;
  HudGaugeData* gauge_playerpower = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_MAINHUD_H
