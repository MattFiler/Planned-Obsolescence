#include "WorldInteractionPopup.h"

WorldInteractionPopup::WorldInteractionPopup(ASGE::Renderer* rend) : UI(Point(0, 0), rend)
{
  // Make background sprite
  background_sprite = createSprite("data/UI/IN_GAME_UI/BOTTOM_LEFT_BG.png");

  // Make close button
  close_button = new Button(Point(461, 606),
                            rend,
                            "data/UI/IN_GAME_UI/CHARACTER_POPUP_CLOSE_BUTTON.png",
                            "data/UI/IN_GAME_UI/CHARACTER_POPUP_CLOSE_BUTTON.png",
                            19,
                            22);
  WorldInteractionPopup* active_p = this;
  close_button->click_function = [active_p] { active_p->setActive(false); };
}

WorldInteractionPopup::~WorldInteractionPopup()
{
  delete background_sprite;
  background_sprite = nullptr;

  delete close_button;
  close_button = nullptr;
}

/* set active/inactive */
void WorldInteractionPopup::setActive(bool is_active)
{
  active = is_active;
  close_button->setActive(is_active);
}

void WorldInteractionPopup::render(double delta_time)
{
  if (active)
  {
    renderer->renderSprite(background_sprite->returnNextSprite(delta_time),
                           render_index::UI_TOP_LAYER_BASE);
    close_button->render(delta_time);
    renderer->renderText(poi_name,
                         static_cast<int>(21 * ScaledSpriteArray::width_scale),
                         static_cast<int>(657 * ScaledSpriteArray::width_scale),
                         1,
                         ASGE::COLOURS::WHITE);
  }
}

/* Set values */
void WorldInteractionPopup::setClickedPointName(const std::string& char_name)
{
  poi_name = localiser.getString(char_name);
}

/* Returns a pointer to the button that was clicked (nullptr if none) */
Button* WorldInteractionPopup::checkForClick(Point click_location)
{
  if (active && close_button->checkForClick(click_location))
  {
    return close_button;
  }
  return nullptr;
}