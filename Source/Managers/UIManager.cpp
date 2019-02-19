#include "UIManager.h"

/* destroy! */
UIManager::~UIManager()
{
  for (Button* button : buttons)
  {
    delete button;
    button = nullptr;
  }
  for (TextBox* text : text_boxes)
  {
    delete text;
    text = nullptr;
  }
  for (ProgressBar* progress : progress_bars)
  {
    delete progress;
    progress = nullptr;
  }
  for (GenericUI* generic_ui : generic_spriteset)
  {
    delete generic_ui;
    generic_ui = nullptr;
  }
  delete char_info_popup;
  char_info_popup = nullptr;
}

/* Add a generic UI element set (foreground and background) */
void UIManager::addGenericUI(GenericUI* new_generic_ui)
{
  generic_spriteset.push_back(new_generic_ui);
}

/* Add a button */
void UIManager::addButton(Button* new_button)
{
  buttons.push_back(new_button);
}

/* Add a textbox */
void UIManager::addTextBox(TextBox* new_textbox)
{
  text_boxes.push_back(new_textbox);
}

/* Add a progress bar */
void UIManager::addProgressBar(ProgressBar* new_progressbar)
{
  progress_bars.push_back(new_progressbar);
}

/* Initialise the character popup */
void UIManager::initCharacterPopup()
{
  char_info_popup = new CharacterInfoPopup(renderer);
  char_info_popup->setActive(false);
}

/* Creates all the UI */
void UIManager::updateAndShowCharacterInfo(const std::string& character_type,
                                           float character_gauge,
                                           const std::string& gauge_name)
{
  char_info_popup->setActive(true);
  char_info_popup->setCharacterName(character_type);
  char_info_popup->setGaugeAmount(character_gauge);
  char_info_popup->setGaugeDescription(gauge_name);
}

/* render all ui */
void UIManager::render(double delta_time)
{
  for (Button* button : buttons)
  {
    button->render(delta_time);
  }
  for (TextBox* text : text_boxes)
  {
    text->render(delta_time);
  }
  for (ProgressBar* progress : progress_bars)
  {
    progress->render(delta_time);
  }
  for (GenericUI* generic_ui : generic_spriteset)
  {
    generic_ui->render(delta_time);
  }

  if (char_info_popup->isActive())
  {
    char_info_popup->render(delta_time);
  }
}

/* Checks all Buttons to see if the passed click lands on any of them */
bool UIManager::checkForClick(Point click)
{
  for (Button* button : buttons)
  {
    if (button->checkForClick(click))
    {
      // Store a reference to the clicked button to un-click it later
      clicked_button = button;
      return true;
    }
  }

  clicked_button = char_info_popup->checkForClick(click);

  return clicked_button != nullptr;
}

/* 'un-clicks' the currently clicked button (if any) and triggers its click function */
void UIManager::releaseClick()
{
  if (clicked_button)
  {
    clicked_button->releaseClick();
    clicked_button = nullptr;
  }
}

/* keep a popup within the window bounds */
void UIManager::keepUIWithinScreen(UI* ui_object)
{
  /*
  Point new_pos = ui_object->getPosition();
  if (new_pos.x_pos > SCREEN_WIDTH - boss_popup->getWidth())
  {
    new_pos.x_pos = SCREEN_WIDTH - boss_popup->getWidth();
  }
  else if (new_pos.x_pos < 0)
  {
    new_pos.x_pos = 0;
  }
  if (new_pos.y_pos > SCREEN_HEIGHT - boss_popup->getHeight())
  {
    new_pos.y_pos = SCREEN_HEIGHT - boss_popup->getHeight();
  }
  else if (new_pos.y_pos < 0)
  {
    new_pos.y_pos = 0;
  }
  ui_object->moveTo(new_pos);
  */
}