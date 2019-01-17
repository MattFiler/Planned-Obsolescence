#include "../Core/AnimatedSprite.h"
#include "../Core/GameObject.h"
#include "../Core/Scene.h"

namespace ASGE
{
  class Renderer;
}

/**
 **   The first scene of the game, displays logos
 */
class TitleScene : public Scene
{
  public:
    TitleScene() = default;
    ~TitleScene() = default;
    bool load(ASGE::Renderer* renderer, ASGE::Input* input, json core_config) override;
    int update(double delta_time) override;
    void render(double delta_time) override;
    void keyHandler(const ASGE::SharedEventData data) override;
    void mouseHandler(const ASGE::SharedEventData data, Vector mouse_position) override;

  private:
    // All sprites for this scene
    GameObject* asge_logo = nullptr;
    GameObject* uwe_logo = nullptr;
    int switch_fade = 0;
    double time_waited = 0;
};