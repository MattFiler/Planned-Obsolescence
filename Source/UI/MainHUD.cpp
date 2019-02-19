#include "MainHUD.h"

MainHUD::MainHUD(ASGE::Renderer* rend) : UI(Point(0, 0), rend)
{
  // Make background sprite
  background_sprite = createSprite("data/UI/IN_GAME_UI/BOTTOM_RIGHT_BG.png");

  // Make gauges
  hud_gauges.reserve(3);
  hud_gauges.push_back(HudGaugeData(Point(805, 603), rend, "gauge_detection", 50));
  hud_gauges.push_back(HudGaugeData(Point(805, 640), rend, "gauge_progress", 40));
  hud_gauges.push_back(HudGaugeData(Point(805, 677), rend, "gauge_timeremaining", 30));
}

MainHUD::~MainHUD()
{
  delete background_sprite;
  background_sprite = nullptr;
}

void MainHUD::render(double delta_time)
{
  renderer->renderSprite(background_sprite->returnNextSprite(delta_time),
                         render_index::UI_TOP_LAYER_BASE);
  for (HudGaugeData& this_gauge : hud_gauges)
  {
    this_gauge.render(renderer, delta_time);
  }
}

/* Set values of gauges */
void MainHUD::adjustGauge(hud_gauge_types bar, float gauge_amount)
{
  hud_gauges[bar].progress_bar->setProgress(gauge_amount / 100);
}