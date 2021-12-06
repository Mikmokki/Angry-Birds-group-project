#ifndef ANGRY_BIRDS_PIG
#define ANGRY_BIRDS_PIG

#include "object.hpp"

class Pig : public Object
{
public:
    Pig(b2Body *body) : Object("../resources/images/possu.png", body)
    {
        sprite_.setScale(pig_scale_, pig_scale_);

        int h = sprite_.getTextureRect().height;
        int w = sprite_.getTextureRect().width;
        sprite_.setOrigin(h * pig_scale_ / 2, w * pig_scale_ / 2); // Set origin to center
        destruction_points_ = 500;
        destructable_ = true;
    };

    virtual char GetType() { return 'P'; };

private:
    const float pig_scale_ = 0.1f; // Maybe could be replaced by levels scale and bodys radius
};

#endif // ANGRY_BIRDS_PIG