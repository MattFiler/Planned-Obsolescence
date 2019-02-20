#ifndef PLANNEDOBSOLESCENCE_WORLDINTERACTIONPOPUP_H
#define PLANNEDOBSOLESCENCE_WORLDINTERACTIONPOPUP_H

#include "../Managers/Gauges.h"
#include "../Map/Tile.h"
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

  void getClickedTileReference(Tile& clicked_tile);
  void updateTileDynamicData();

  void setActive(bool is_active);
  bool isActive() { return active; };
  Button* checkForClick(Point click_location);

 private:
  bool active = false;

  ScaledSpriteArray* background_sprite = nullptr;
  Button* close_button = nullptr;
  Button* poi_interaction_button = nullptr;

  Tile* referenced_tile = nullptr;

  PO_Gauges gauge_data;

  GetLocalisedString localiser;

  std::string poi_name = "";
  std::string poi_desc = "";
};

#endif // PLANNEDOBSOLESCENCE_WORLDINTERACTIONPOPUP_H
