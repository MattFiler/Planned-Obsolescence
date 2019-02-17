#include "Menu.h"

/* Grab window scale */
Menu::Menu()
{
  ScaledSpriteArray sprite_render_data;
  middle_of_window = static_cast<int>((SCREEN_HEIGHT * sprite_render_data.width_scale / 2) + 14);
}

/* Grab renderer */
void Menu::giveRenderer(ASGE::Renderer* rend)
{
  renderer = rend;
}

/* Add menu text item */
void Menu::addMenuItem(const std::string& item_text)
{
  menu_text_items.push_back(item_text);
  menu_text_offsets.push_back(0);

  realignMenuTextItems();
}

/* Add menu sprite item */
std::shared_ptr<ScaledSpriteArray> Menu::addMenuSprite(const std::string& filepath)
{
  // Create sprite
  ASGE::Sprite* new_sprite = renderer->createRawSprite();
  new_sprite->loadTexture("data/" + filepath);
  std::shared_ptr<ScaledSpriteArray> sprite = std::make_shared<ScaledSpriteArray>(1);
  sprite->addSprite(*new_sprite);

  // Add to array and return
  menu_sprites.push_back(sprite);
  return sprite;
}

/* Set vertical spacing between menu text items */
void Menu::setMenuTextSpacing(int offset)
{
  y_offset = offset;
  realignMenuTextItems();
}

/* Set the offset to the left of the screen */
void Menu::setLeftMargin(int offset)
{
  x_offset = offset;
}

/* Set text active colour */
void Menu::setActiveTextColour(ASGE::Colour colour)
{
  active_text_colour = colour;
}

/* Set text inactive colour */
void Menu::setInactiveTextColour(ASGE::Colour colour)
{
  inactive_text_colour = colour;
}

/* Realign the menu text items */
void Menu::realignMenuTextItems()
{
  int vertical_correction = ((static_cast<int>(menu_text_items.size()) - 1) * y_offset) / 2;
  for (int i = 0; i < static_cast<int>(menu_text_items.size()); i++)
  {
    menu_text_offsets[i] = (i * y_offset) - vertical_correction + middle_of_window;
  }
}

/* Key Handler */
int Menu::keyHandler(Keybinds& user_input)
{
  if (user_input.keyReleased("Activate"))
  {
    return current_menu_index;
  }
  else if (user_input.keyReleased("Menu Up"))
  {
    if (current_menu_index > 0)
    {
      current_menu_index--;
    }
  }
  else if (user_input.keyReleased("Menu Down"))
  {
    if (current_menu_index < static_cast<int>(menu_text_items.size() - 1))
    {
      current_menu_index++;
    }
  }
  return -1;
}

/* Render */
void Menu::render(double delta_time)
{
  // Render sprites
  for (std::shared_ptr<ScaledSpriteArray>& item_sprite : menu_sprites)
  {
    renderer->renderSprite(item_sprite->returnNextSprite(delta_time),
                           render_index::UI_SPRITE_LAYER);
  }

  // Render text
  int index = 0;
  for (std::string& item_text : menu_text_items)
  {
    renderer->renderText(item_text,
                         x_offset,
                         menu_text_offsets[index],
                         1,
                         (current_menu_index == index) ? active_text_colour : inactive_text_colour,
                         render_index::UI_TEXT_LAYER);
    index++;
  }
}