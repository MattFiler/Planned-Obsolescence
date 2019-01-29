#include "Camera.h"

Camera::Camera()
{
    game_sprites.reserve(10);
    ui_sprites.reserve(10);
}

void Camera::setRenderer(ASGE::Renderer* rend)
{
    renderer = rend;
}

/* Registers a sprite that will be rendered by the camera and will move as the camera does */
void Camera::registerGameSprite(DynamicSprite *sprite)
{
    game_sprites.push_back(sprite);
    if(game_sprites.size() == game_sprites.capacity())
    {
        game_sprites.reserve(10);
    }

}

/* Registers a sprite that will be rendered by the camera and not move with the camera*/
void Camera::registerUiSprite(DynamicSprite *sprite)
{
    ui_sprites.push_back(sprite);
    if(ui_sprites.size() == ui_sprites.capacity())
    {
        ui_sprites.reserve(10);
    }
}

/* Renders all sprites registered with the camera */
void Camera::renderSprites(double delta_time)
{
    for (auto i : game_sprites)
    {
        // Add the camera offset to the sprite
        i->addX(position.x_pos);
        i->addY(position.y_pos);
        // Render ths sprite
        renderer->renderSprite(i->returnNextSprite(delta_time));
        // Restore the sprite to the previous position
        i->addX(-position.x_pos);
        i->addY(-position.y_pos);
    }
    for (auto i : ui_sprites)
    {
        renderer->renderSprite(i->returnNextSprite(delta_time));
    }
}

/* Returns the current position of the camera */
Point Camera::getCameraPosition()
{
    return position;
}

/* Move the camera by the passed amount*/
void Camera::moveCamera(float x_amount, float y_amount)
{
    position.x_pos += x_amount;
    position.y_pos += y_amount;
}