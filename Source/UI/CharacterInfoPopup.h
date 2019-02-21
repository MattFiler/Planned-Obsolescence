#ifndef PLANNEDOBSOLESCENCE_CHARACTERINFOPOPUP_H
#define PLANNEDOBSOLESCENCE_CHARACTERINFOPOPUP_H

#include "Button.h"
#include "GetLocalisedString.h"
#include "HudGaugeData.h"
#include "ProgressBar.h"
#include "UI.h"

class CharacterInfoPopup : public UI
{
 public:
  explicit CharacterInfoPopup(ASGE::Renderer* rend);
  ~CharacterInfoPopup() override;

  CharacterInfoPopup(const CharacterInfoPopup&) = delete;
  CharacterInfoPopup& operator=(const CharacterInfoPopup&) = delete;

  void setSoundPlayer(SoLoud::Soloud* player) { sound_player = player; }

  void render(double delta_time) override;

  void setCharacterName(const std::string& char_name);
  void setGaugeDescription(const std::string& gauge_desc);
  void setGaugeAmount(float gauge_amount);

  void setActive(bool is_active, bool should_play_sound = true);
  bool isActive() { return active; };
  Button* checkForClick(Point click_location);

 private:
  bool active = false;

  ScaledSpriteArray* background_sprite = nullptr;
  Button* close_button = nullptr;
  HudGaugeData* progress_bar = nullptr;
  FileHandler file_handler;
  GetLocalisedString localiser;

  std::string character_name = "";
  std::string character_desc = "";

  SoLoud::Soloud* sound_player;
  SoLoud::Wav popup_load;
  SoLoud::Wav popup_close;
};

#endif // PLANNEDOBSOLESCENCE_CHARACTERINFOPOPUP_H
