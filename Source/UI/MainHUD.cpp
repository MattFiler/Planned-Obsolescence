#include "MainHUD.h"

/* Create main hud */
MainHUD::MainHUD(ASGE::Renderer* rend) : UI(Point(0, 0), rend)
{
  background_sprite = createSprite("data/UI/IN_GAME_UI/CORE_UI.png");

  hud_gauges.reserve(3);

  gauge_detection = new HudGaugeData(Point(805, 603), rend, "gauge_detection");
  hud_gauges.push_back(gauge_detection);

  gauge_progress = new HudGaugeData(Point(805, 640), rend, "gauge_progress");
  hud_gauges.push_back(gauge_progress);

  gauge_timeremaining = new HudGaugeData(Point(805, 677), rend, "gauge_timeremaining", 0, false);
  hud_gauges.push_back(gauge_timeremaining);

  gauge_playerpower = new HudGaugeData(Point(13, 10), rend, "gauge_playerpower", 100, false);
  hud_gauges.push_back(gauge_playerpower);
}

MainHUD::~MainHUD()
{
  delete background_sprite;
  background_sprite = nullptr;

  delete gauge_detection;
  gauge_detection = nullptr;

  delete gauge_progress;
  gauge_progress = nullptr;

  delete gauge_timeremaining;
  gauge_timeremaining = nullptr;

  delete gauge_playerpower;
  gauge_playerpower = nullptr;
}

void MainHUD::render(double delta_time)
{
  renderer->renderSprite(background_sprite->returnNextSprite(delta_time),
                         render_index::UI_TOP_LAYER_BASE);
  for (HudGaugeData* this_gauge : hud_gauges)
  {
    this_gauge->render(renderer, delta_time);
  }
}

/* Set values of gauges */
void MainHUD::adjustGauge(hud_gauge_types bar, float gauge_amount)
{
  hud_gauges.at(bar)->update(gauge_amount / 100);
}