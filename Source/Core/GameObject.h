#include "AnimatedSprite.h"
#include "Geometry.h"

/**
 *  Standard game object, usually for objects with sprites
 */
class GameObject
{
  public:
    GameObject();
    ~GameObject();

    std::string getName();              /**< Get the objects name*/
    void setName(std::string new_name); /**< Set the objects name*/

    bool shouldDestroy();
    void shouldDestroy(bool flag);

    float xPos();
    void xPos(float new_x);
    float yPos();
    void yPos(float new_y);
    void move(float x, float y);
    void CenterSpriteOnPoint(float x, float y);

    void setScale(float new_scale);
    float getScale();
    void scaleToWidth(float target_width);
    void scaleToHeight(float target_height);

    void setAnimatedSprite(AnimatedSprite* new_sprite);
    AnimatedSprite* getAnimatedSprite();

  protected:
    bool should_destroy = false; /**<  Flag to see if the main scene should destroy this object */
    std::string name = "Default";
    Point position;
    Point center;
    // The width, height and scale of the sprite (if any) BEFORE resolution scaling
    float width = 0;
    float height = 0;
    float scale = 0;

    AnimatedSprite* sprite = nullptr;
};