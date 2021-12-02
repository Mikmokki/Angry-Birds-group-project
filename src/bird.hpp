#ifndef ANGRY_BIRDS_BIRD
#define ANGRY_BIRDS_BIRD

#include "object.hpp"

class Bird : public Object
{
public:
    Bird(b2Body *body, float b2_w, float b2_h, float angle) : Object("../resources/images/bird.png", body)
    {
        // sprite_.setScale(bird_scale_, bird_scale_);
        float TEXTURE_SCALE = 64.0f;
        sprite_.setScale(b2_w * TEXTURE_SCALE / (1.0f * sprite_.getTextureRect().width), b2_h * TEXTURE_SCALE / (1.0f * sprite_.getTextureRect().height));

        int h = sprite_.getTextureRect().height;
        int w = sprite_.getTextureRect().width;
        sprite_.setOrigin(h / 2, w / 2); // Set origin to center
        sprite_.setRotation(angle);
    };

private:
    const float bird_scale_ = 0.1f; // Maybe could be replaced by levels scale and bodys radius
};

#endif // ANGRY_BIRDS_BIRD