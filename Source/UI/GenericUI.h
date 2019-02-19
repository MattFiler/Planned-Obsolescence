#ifndef PLANNEDOBSOLESCENCE_GENERICUISPRITE_H
#define PLANNEDOBSOLESCENCE_GENERICUISPRITE_H

#include "../Constants.h"
#include "../Math/Point.h"
#include "../Sprites/ScaledSpriteArray.h"
#include "UI.h"
#include <Engine/Renderer.h>

/* A basic UI component, consisting of foreground and (optional) background */
class GenericUI : public UI
{
 public:
  GenericUI() = default;
  GenericUI(ASGE::Renderer* rend,
            const std::string& texture_path_1,
            const std::string& texture_path_2 = "",
            float _width = 0,
            float _height = 0,
            Point pos = Point(0, 0));
  ~GenericUI() override;

  GenericUI(const GenericUI&) = delete;
  GenericUI& operator=(const GenericUI&) = delete;

  void render(double delta_time) override;

 private:
  ScaledSpriteArray* sprite_fg = nullptr;
  ScaledSpriteArray* sprite_bg = nullptr;
};

#endif // PLANNEDOBSOLESCENCE_GENERICUISPRITE_H
