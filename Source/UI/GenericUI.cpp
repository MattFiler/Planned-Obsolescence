#include "GenericUI.h"

GenericUI::GenericUI(ASGE::Renderer* rend,
                     const std::string& texture_path_1,
                     const std::string& texture_path_2,
                     float _width,
                     float _height,
                     Point pos) :
  UI(pos, rend)
{
  width = _width;
  height = _height;

  // foreground sprite
  delete sprite_fg;
  sprite_fg = new ScaledSpriteArray(1);
  ASGE::Sprite* _sprite_fg = renderer->createRawSprite();
  _sprite_fg->loadTexture("data/UI/" + texture_path_1);
  sprite_fg->addSprite(*_sprite_fg);

  // background sprite
  if (texture_path_2 != "")
  {
    delete sprite_bg;
    sprite_bg = new ScaledSpriteArray(1);
    ASGE::Sprite* _sprite_bg = renderer->createRawSprite();
    _sprite_bg->loadTexture("data/UI/" + texture_path_2);
    sprite_bg->addSprite(*_sprite_bg);
  }

  if (_width != 0 && _height != 0)
  {
    sprite_fg->setWidth(width);
    sprite_fg->setHeight(height);
    if (texture_path_2 != "")
    {
      sprite_bg->setWidth(width);
      sprite_bg->setHeight(height);
    }
  }
  if (pos.x_pos != 0 && pos.y_pos != 0)
  {
    sprite_fg->xPos(pos.x_pos);
    sprite_fg->yPos(pos.y_pos);
    if (texture_path_2 != "")
    {
      sprite_bg->xPos(pos.x_pos);
      sprite_bg->yPos(pos.y_pos);
    }
  }
}

GenericUI::~GenericUI()
{
  delete sprite_fg;
  sprite_fg = nullptr;

  delete sprite_bg;
  sprite_bg = nullptr;
}

void GenericUI::render(double delta_time)
{
  renderer->renderSprite(sprite_fg->returnNextSprite(delta_time), render_index::UI_TOP_LAYER_CAP);
  if (sprite_bg != nullptr)
  {
    renderer->renderSprite(sprite_bg->returnNextSprite(delta_time),
                           render_index::UI_TOP_LAYER_BASE);
  }
}
