#ifndef ANGRY_BIRDS_WALL
#define ANGRY_BIRDS_WALL

#include "object.hpp"

class Wall : public Object
{
public:
    Wall(b2Body *body, float b2_w, float b2_h, float rot) : Object("../resources/images/box.png", body)
    {
        float TEXTURE_SCALE = 64.0f;
        // wall_w * TEXTURE_SCALE / (1.0f * wall_texture.getSize().x), wall_h * TEXTURE_SCALE / (1.0f * wall_texture.getSize().y)
        sprite_.setScale(b2_w * TEXTURE_SCALE / (1.0f * sprite_.getTextureRect().width), b2_h * TEXTURE_SCALE / (1.0f * sprite_.getTextureRect().height));
        int h = sprite_.getTextureRect().height;
        int w = sprite_.getTextureRect().width;
        sprite_.setOrigin(h, w); // Set origin to center
        sprite_.setRotation(rot);
    };

private:
    const float wall_scale_ = 0.3f; // Maybe could be replaced by levels scale and bodys radius
};

#endif // ANGRY_BIRDS_WALL