#ifndef ANGRY_BIRDS_WALL
#define ANGRY_BIRDS_WALL

#include "object.hpp"

class Wall : public Object
{
public:
    Wall(b2Body *body, float b2_w, float b2_h) : Object("../resources/images/box.png", body)
    {
        int w = sprite_.getTextureRect().width;
        int h = sprite_.getTextureRect().height;

        sprite_.setScale(b2_w * 2.0f * scale / (1.0f * w), b2_h * 2.0f * scale / (1.0f * h));

        sprite_.setOrigin(w / 2, h / 2);
    };

private:
    const float wall_scale_ = 0.1f; // Maybe could be replaced by levels scale and bodys radius
};

#endif // ANGRY_BIRDS_WALL