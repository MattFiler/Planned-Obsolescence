#include "CharacterInfoPopup.h"

CharacterInfoPopup::CharacterInfoPopup(ASGE::Renderer* rend) : UI(Point(0, 0), rend)
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
  CharacterInfoPopup* myself = this;
  close_button->click_function = [myself] { myself->setActive(false); };

  // Make progress bar
  progress_bar = new HudGaugeData(Point(18, 672), rend);
}

CharacterInfoPopup::~CharacterInfoPopup()
{
  delete background_sprite;
  background_sprite = nullptr;

  delete close_button;
  close_button = nullptr;

  delete progress_bar;
  progress_bar = nullptr;
}

void CharacterInfoPopup::render(double delta_time)
{
  if (active)
  {
    renderer->renderSprite(background_sprite->returnNextSprite(delta_time),
                           render_index::UI_TOP_LAYER_BASE);
    close_button->render(delta_time);
    progress_bar->render(renderer, delta_time);
    renderer->renderText(character_name,
                         static_cast<int>(21 * ScaledSpriteArray::width_scale),
                         static_cast<int>(657 * ScaledSpriteArray::width_scale),
                         1,
                         ASGE::COLOURS::WHITE);
  }
}

/* set active/inactive */
void CharacterInfoPopup::setActive(bool is_active)
{
  active = is_active;
  close_button->setActive(is_active);
}

/* Set values */
void CharacterInfoPopup::setCharacterName(const std::string& char_name)
{
  character_name = localiser.getString(char_name);
}
void CharacterInfoPopup::setGaugeDescription(const std::string& gauge_desc)
{
  progress_bar->gauge_name = localiser.getString(gauge_desc);
}
void CharacterInfoPopup::setGaugeAmount(float gauge_amount)
{
  progress_bar->progress_bar->setProgress(gauge_amount / 100);
}

/* Returns a pointer to the button that was clicked (nullptr if none) */
Button* CharacterInfoPopup::checkForClick(Point click_location)
{
  if (close_button->checkForClick(click_location))
  {
    return close_button;
  }
  return nullptr;
}