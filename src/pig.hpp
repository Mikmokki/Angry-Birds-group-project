#ifndef ANGRY_BIRDS_PIG
#define ANGRY_BIRDS_PIG

#include "object.hpp"

class Pig : public Object
{
public:
    Pig(b2Body *body, float b2_radius) : Object("resources/images/pig.png", body)
    {
        int w = sprite_.getTextureRect().width;
        int h = sprite_.getTextureRect().height;

        sprite_.setScale(b2_radius * 2.0f * scale / (1.0f * w), b2_radius * 2.0f * scale / (1.0f * h));
        sprite_.setOrigin(w / 2.f, h / 2.f);
        destruction_points_ = 500;
        destructable_ = true;
    };

    virtual char GetType() { return 'P'; };

private:
    const float pig_scale_ = 0.1f; // Maybe could be replaced by levels scale and bodys radius
};

#endif // ANGRY_BIRDS_PIG