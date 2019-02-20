#include "MainHUD.h"

/* Create main hud */
MainHUD::MainHUD(ASGE::Renderer* rend) : UI(Point(0, 0), rend)
{
  background_sprite = createSprite("data/UI/IN_GAME_UI/BOTTOM_RIGHT_BG.png");

  hud_gauges.reserve(3);

  gauge_detection = new HudGaugeData(Point(805, 603), rend, "gauge_detection", 50);
  hud_gauges.push_back(gauge_detection);

  gauge_progress = new HudGaugeData(Point(805, 640), rend, "gauge_progress", 40);
  hud_gauges.push_back(gauge_progress);

  gauge_timeremaining = new HudGaugeData(Point(805, 677), rend, "gauge_timeremaining", 30);
  hud_gauges.push_back(gauge_timeremaining);
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
  hud_gauges[bar]->progress_bar->setProgress(gauge_amount / 100);
}