#ifndef ANGRY_BIRDS_BIRD
#define ANGRY_BIRDS_BIRD

#include "object.hpp"

class Bird : public Object
{
public:
    Bird(b2Body *body) : Object("../resources/bird.png", body)
    {
        sprite_.setScale(bird_scale_, bird_scale_);

        int h = sprite_.getTextureRect().height;
        int w = sprite_.getTextureRect().width;
        sprite_.setOrigin(h * bird_scale_ / 2, w * bird_scale_ / 2); // Set origin to center
    };

private:
    const float bird_scale_ = 0.1f; // Maybe could be replaced by levels scale and bodys radius
};

#endif // ANGRY_BIRDS_BIRD