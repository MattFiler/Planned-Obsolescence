#ifndef PLANNEDOBSOLESCENCE_HUDDATA_H
#define PLANNEDOBSOLESCENCE_HUDDATA_H

#include "ProgressBar.h"

struct HudGaugeData
{
  HudGaugeData(Point location, ASGE::Renderer* renderer, std::string name = "", float value = 0)
  {
    progress_bar = new ProgressBar(location, renderer, 464, 29);
    progress_bar->addBackgroundSprite("data/UI/WHITE.png");
    progress_bar->addFillSprite("data/UI/LIGHT_PURPLE.png");

    gauge_location = location;
    text_location = Point((gauge_location.x_pos + 11) * ScaledSpriteArray::width_scale,
                          (gauge_location.y_pos + 22) * ScaledSpriteArray::width_scale);

    gauge_name = name;
    gauge_value = value;
  }

  void render(ASGE::Renderer* renderer, double delta_time)
  {
    progress_bar->render(delta_time);
    renderer->renderText(gauge_name,
                         static_cast<int>(text_location.x_pos),
                         static_cast<int>(text_location.y_pos),
                         0.5,
                         ASGE::COLOURS::BLACK);
  }

  void update(float value) { gauge_value = value; }

  ProgressBar* progress_bar = nullptr;
  std::string gauge_name = "";
  float gauge_value = 0.0f;

 private:
  Point gauge_location;
  Point text_location;
};

#endif // PLANNEDOBSOLESCENCE_HUDDATA_H
