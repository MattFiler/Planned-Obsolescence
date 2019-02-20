#include "WorldInteractionPopup.h"
#include "../Managers/CharacterManager.h"

WorldInteractionPopup::WorldInteractionPopup(ASGE::Renderer* rend,
                                             CharacterManager* character_manager) :
  UI(Point(0, 0), rend)
{
  // Make background sprite
  background_sprite = createSprite("data/UI/IN_GAME_UI/BOTTOM_LEFT_BG.png");

  // Make close button
  close_button = new Button(Point(461, 606),
                            rend,
                            "data/UI/IN_GAME_UI/CHARACTER_POPUP_CLOSE_BUTTON.png",
                            "data/UI/IN_GAME_UI/CHARACTER_POPUP_CLOSE_BUTTON_HOVER.png",
                            19,
                            22);
  WorldInteractionPopup* popup_instance = this;
  close_button->click_function = [popup_instance] { popup_instance->setActive(false); };

  // Make interaction button
  poi_interaction_button = new Button(Point(18, 672),
                                      rend,
                                      "data/UI/IN_GAME_UI/POI_INTERACTION_BUTTON.jpg",
                                      "data/UI/IN_GAME_UI/POI_INTERACTION_BUTTON_HOVER.jpg",
                                      340,
                                      29,
                                      "placeholder_text",
                                      0.5f,
                                      Point(8, 7),
                                      ASGE::COLOURS::BLACK);
  poi_interaction_button->click_function = [popup_instance, character_manager] {
    // If we have enough power to perform action, and it's not already broken/inuse - break it!
    if (popup_instance->referenced_tile->getPointOfInterestState() ==
          poi_state::POI_IS_FUNCTIONAL &&
        popup_instance->gauge_data.player_power >= gauge_levels::GAUGE_HALF)
    {
      popup_instance->referenced_tile->setPointOfInterestState(poi_state::POI_IS_BROKEN);
      popup_instance->gauge_data.player_power -= gauge_levels::GAUGE_HALF;
      character_manager->sabotageAtPoint(Point(popup_instance->referenced_tile->getPositionX(),
                                               popup_instance->referenced_tile->getPositionY()));
    }
  };
}

WorldInteractionPopup::~WorldInteractionPopup()
{
  delete background_sprite;
  background_sprite = nullptr;

  delete close_button;
  close_button = nullptr;

  delete poi_interaction_button;
  poi_interaction_button = nullptr;
}

/* set active/inactive */
void WorldInteractionPopup::setActive(bool is_active)
{
  active = is_active;
  close_button->setActive(is_active);
  poi_interaction_button->setActive(is_active);
}

void WorldInteractionPopup::render(double delta_time)
{
  if (active)
  {
    updateTileDynamicData();

    renderer->renderSprite(background_sprite->returnNextSprite(delta_time),
                           render_index::UI_TOP_LAYER_BASE);
    close_button->render(delta_time);
    poi_interaction_button->render(delta_time);
    renderer->renderText(poi_desc,
                         static_cast<int>(17 * ScaledSpriteArray::width_scale),
                         static_cast<int>(668 * ScaledSpriteArray::width_scale),
                         0.4f,
                         ASGE::COLOURS::WHITE);
    renderer->renderText(poi_name,
                         static_cast<int>(17 * ScaledSpriteArray::width_scale),
                         static_cast<int>(652 * ScaledSpriteArray::width_scale),
                         1,
                         ASGE::COLOURS::WHITE);
  }
}

/* Set values */
void WorldInteractionPopup::getClickedTileReference(Tile& clicked_tile)
{
  referenced_tile = &clicked_tile;
  poi_name = localiser.getString(clicked_tile.getTileName());
  updateTileDynamicData();
}

/* update dynamic tile-related data */
void WorldInteractionPopup::updateTileDynamicData()
{
  if (referenced_tile != nullptr)
  {
    // Show relevant description of clicked POI and enable button if we can sabotage
    switch (referenced_tile->getPointOfInterestState())
    {
      case poi_state::POI_IS_FUNCTIONAL:
      {
        if (gauge_data.player_power < gauge_levels::GAUGE_HALF)
        {
          // Not enough power to sabotage this POI
          poi_interaction_button->setActive(false);
          poi_desc = localiser.getString("poi_generic_desc_notenoughpower");
        }
        else
        {
          // Enough power to sabotage, allow option to
          poi_interaction_button->setActive(true);
          poi_desc = localiser.getString(referenced_tile->getTileName() + "_desc_hackable");
        }
        break;
      }
      case poi_state::POI_IS_BEING_USED_BY_GOON:
      {
        // In use by goon, we cannot hack
        poi_interaction_button->setActive(false);
        poi_desc = localiser.getString(referenced_tile->getTileName() + "_desc_inuse");
        break;
      }
      case poi_state::POI_IS_BEING_FIXED:
      {
        // being fixed by technician, we cannot hack
        poi_interaction_button->setActive(false);
        poi_desc = localiser.getString(referenced_tile->getTileName() + "_desc_being_fixed");
        break;
      }
      default:
      {
        // Either queued to be fixed or we've broken it and it is idle
        poi_interaction_button->setActive(false);
        poi_desc = localiser.getString(referenced_tile->getTileName() + "_desc_hacked");
        break;
      }
    }
    // Update button text
    poi_interaction_button->updateText(referenced_tile->getTileName() + "_interact");
  }
}

/* Returns a pointer to the button that was clicked (nullptr if none) */
Button* WorldInteractionPopup::checkForClick(Point click_location)
{
  if (active && close_button->checkForClick(click_location))
  {
    return close_button;
  }
  if (active && poi_interaction_button->checkForClick(click_location))
  {
    return poi_interaction_button;
  }
  return nullptr;
}