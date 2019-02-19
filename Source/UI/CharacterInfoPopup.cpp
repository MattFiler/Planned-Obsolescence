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
  bool* active_p = &active;
  close_button->click_function = [active_p] { *active_p = false; };

  // Make progress bar
  progress_bar = new ProgressBar(Point(18, 762), rend, 463, 29);
  progress_bar->addBackgroundSprite("data/UI/default.png");
  progress_bar->addFillSprite("data/UI/default.png");
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
    renderer->renderSprite(background_sprite->returnNextSprite(delta_time));
    close_button->render(delta_time);
    progress_bar->render(delta_time);
    renderer->renderText(character_name,
                         static_cast<int>(21 * ScaledSpriteArray::width_scale),
                         static_cast<int>(653 * ScaledSpriteArray::width_scale),
                         1,
                         ASGE::COLOURS::WHITE);
    renderer->renderText(gauge_name,
                         static_cast<int>(29 * ScaledSpriteArray::width_scale),
                         static_cast<int>(694 * ScaledSpriteArray::width_scale),
                         0.5,
                         ASGE::COLOURS::BLACK);
  }
}

/* Set values */
void CharacterInfoPopup::setCharacterName(const std::string& char_name)
{
  character_name = char_name;
}
void CharacterInfoPopup::setGaugeDescription(const std::string& gauge_desc)
{
  gauge_name = gauge_desc;
}
void CharacterInfoPopup::setGaugeAmount(float gauge_amount)
{
  gauge_value = gauge_amount;
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