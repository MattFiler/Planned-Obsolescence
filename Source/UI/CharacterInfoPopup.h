#ifndef PLANNEDOBSOLESCENCE_CHARACTERINFOPOPUP_H
#define PLANNEDOBSOLESCENCE_CHARACTERINFOPOPUP_H

#include "Button.h"
#include "ProgressBar.h"
#include "UI.h"

class CharacterInfoPopup : public UI
{
 public:
  explicit CharacterInfoPopup(ASGE::Renderer* rend);
  ~CharacterInfoPopup() override;

  CharacterInfoPopup(const CharacterInfoPopup&) = delete;
  CharacterInfoPopup& operator=(const CharacterInfoPopup&) = delete;

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
  ProgressBar* progress_bar = nullptr;

  std::string character_name = "";
  std::string gauge_name = "";
  float gauge_value = 0.0f;
};

#endif // PLANNEDOBSOLESCENCE_CHARACTERINFOPOPUP_H
