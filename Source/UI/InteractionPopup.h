#ifndef PLANNEDOBSOLESCENCE_InteractionPopup_H
#define PLANNEDOBSOLESCENCE_InteractionPopup_H

#include "../Managers/Gauges.h"
#include "../Map/Tile.h"
#include "Button.h"
#include "GetLocalisedString.h"
#include "HudGaugeData.h"
#include "ProgressBar.h"
#include "UI.h"

class CharacterManager;

class InteractionPopup : public UI
{
 public:
  explicit InteractionPopup(ASGE::Renderer* rend);
  ~InteractionPopup() override;

  InteractionPopup(const InteractionPopup&) = delete;
  InteractionPopup& operator=(const InteractionPopup&) = delete;

  void setPopupType(popup_type this_type);

  void setCharacterManager(CharacterManager* manager) { character_manager = manager; }
  void setSoundPlayer(SoLoud::Soloud* player) { sound_player = player; }

  void render(double delta_time) override;

  void getClickedTileReference(Tile& clicked_tile);
  void updateTileDynamicData();

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
  Button* poi_interaction_button = nullptr;
  HudGaugeData* progress_bar = nullptr;

  Tile* referenced_tile = nullptr;

  PO_Gauges gauge_data = PO_Gauges();
  FileHandler file_handler;
  GetLocalisedString localiser;
  CharacterManager* character_manager = nullptr;
  ASGE::Renderer* renderer = nullptr;

  popup_type type;

  SoLoud::Soloud* sound_player;
  SoLoud::Wav popup_load;
  SoLoud::Wav popup_close;
  SoLoud::Wav hacked_poi;
  SoLoud::Wav hacked_poi_failed;

  std::string popup_title = "";
  std::string popup_subtitle = "";
};

#endif // PLANNEDOBSOLESCENCE_InteractionPopup_H
