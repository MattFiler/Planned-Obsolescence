#ifndef PLANNEDOBSOLESCENCE_HUDDATA_H
#define PLANNEDOBSOLESCENCE_HUDDATA_H

#include "GetLocalisedString.h"
#include "ProgressBar.h"

struct HudGaugeData
{
  HudGaugeData(Point location,
               ASGE::Renderer* renderer,
               const std::string& name = "placeholder_text",
               float value = 0,
               bool full_is_failed = true)
  {
    progress_bar = new ProgressBar(location, renderer, 464, 29);
    progress_bar->addBackgroundSprite("data/UI/WHITE.png");
    progress_bar->addFillSprite("data/UI/LIGHT_PURPLE.png");

    gauge_location = location;
    text_location = Point((gauge_location.x_pos + 11) * ScaledSpriteArray::width_scale,
                          (gauge_location.y_pos + 22) * ScaledSpriteArray::width_scale);

    gauge_name = localiser.getString(name);

    full_bar_fails = full_is_failed;
    if (!full_bar_fails)
    {
      fill_colour_orig[0] = 1.0f;
      fill_colour_orig[1] = 0.0f;
      fill_colour_orig[2] = 0.0f;
    }

    progress_bar->setProgress(value);
  }

  HudGaugeData(const HudGaugeData&) = delete;
  HudGaugeData& operator=(const HudGaugeData&) = delete;

  void render(ASGE::Renderer* renderer, double delta_time)
  {
    progress_bar->render(delta_time);
    renderer->renderText(gauge_name,
                         static_cast<int>(text_location.x_pos),
                         static_cast<int>(text_location.y_pos),
                         0.5,
                         ASGE::COLOURS::BLACK);
  }

  void update(float value)
  {
    float normalised_value = progress_bar->setProgress(value);

    // Make bar turn red as we approach a loss
    if (full_bar_fails)
    {
      fill_colour[0] = fill_colour_orig[0] + (0.161f * normalised_value);
      fill_colour[1] = fill_colour_orig[1] - (0.564f * normalised_value);
      fill_colour[2] = fill_colour_orig[2] - (0.976f * normalised_value);
    }
    else
    {
      fill_colour[0] = fill_colour_orig[0] - (0.161f * normalised_value);
      fill_colour[1] = fill_colour_orig[1] + (0.564f * normalised_value);
      fill_colour[2] = fill_colour_orig[2] + (0.976f * normalised_value);
    }
    progress_bar->getFillSprite()->setColour(fill_colour);
  }

  ProgressBar* progress_bar = nullptr;
  std::string gauge_name = "";

 private:
  Point gauge_location;
  Point text_location;
  GetLocalisedString localiser;

  float fill_colour[3] = { 0.839f, 0.564f, 0.976f };
  float fill_colour_orig[3] = { 0.839f, 0.564f, 0.976f };
  bool full_bar_fails = true;
};

#endif // PLANNEDOBSOLESCENCE_HUDDATA_H
