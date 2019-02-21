#ifndef PLANNEDOBSOLESCENCE_WORLDINTERACTIONPOPUP_H
#define PLANNEDOBSOLESCENCE_WORLDINTERACTIONPOPUP_H

#include "../Managers/Gauges.h"
#include "../Map/Tile.h"
#include "Button.h"
#include "GetLocalisedString.h"
#include "HudGaugeData.h"
#include "ProgressBar.h"
#include "UI.h"

class CharacterManager;

class WorldInteractionPopup : public UI
{
 public:
  explicit WorldInteractionPopup(ASGE::Renderer* rend, CharacterManager* character_manager);
  ~WorldInteractionPopup() override;

  WorldInteractionPopup(const WorldInteractionPopup&) = delete;
  WorldInteractionPopup& operator=(const WorldInteractionPopup&) = delete;

  void setSoundPlayer(SoLoud::Soloud* player) { sound_player = player; }

  void render(double delta_time) override;

  void getClickedTileReference(Tile& clicked_tile);
  void updateTileDynamicData();

  void setActive(bool is_active, bool should_play_sound = true);
  bool isActive() { return active; };
  Button* checkForClick(Point click_location);

 private:
  bool active = false;

  ScaledSpriteArray* background_sprite = nullptr;
  Button* close_button = nullptr;
  Button* poi_interaction_button = nullptr;

  Tile* referenced_tile = nullptr;

  PO_Gauges gauge_data = PO_Gauges();
  FileHandler file_handler;
  GetLocalisedString localiser;

  SoLoud::Soloud* sound_player;
  SoLoud::Wav popup_load;
  SoLoud::Wav popup_close;
  SoLoud::Wav hacked_poi;
  SoLoud::Wav hacked_poi_failed;

  std::string poi_name = "";
  std::string poi_desc = "";
};

#endif // PLANNEDOBSOLESCENCE_WORLDINTERACTIONPOPUP_H
