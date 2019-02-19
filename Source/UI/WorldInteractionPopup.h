#ifndef PLANNEDOBSOLESCENCE_WORLDINTERACTIONPOPUP_H
#define PLANNEDOBSOLESCENCE_WORLDINTERACTIONPOPUP_H

#include "Button.h"
#include "GetLocalisedString.h"
#include "HudGaugeData.h"
#include "ProgressBar.h"
#include "UI.h"

class WorldInteractionPopup : public UI
{
 public:
  explicit WorldInteractionPopup(ASGE::Renderer* rend);
  ~WorldInteractionPopup() override;

  WorldInteractionPopup(const WorldInteractionPopup&) = delete;
  WorldInteractionPopup& operator=(const WorldInteractionPopup&) = delete;

  void render(double delta_time) override;

  void setCharacterName(const std::string& char_name);
  void setGaugeDescription(const std::string& gauge_desc);
  void setGaugeAmount(float gauge_amount);

  void setActive(bool is_active) { active = is_active; };
  bool isActive() { return active; };
  Button* checkForClick(Point click_location);

 private:
  bool active = false;

  ScaledSpriteArray* background_sprite = nullptr;
  Button* close_button = nullptr;
  HudGaugeData* progress_bar = nullptr;

  GetLocalisedString localiser;

  std::string character_name = "";
};

#endif // PLANNEDOBSOLESCENCE_WORLDINTERACTIONPOPUP_H