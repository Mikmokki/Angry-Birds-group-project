#ifndef ANGRY_BIRDS_GROUND
#define ANGRY_BIRDS_GROUND

#include "object.hpp"

class Ground : public Object
{
public:
    Ground(b2Body *body) : Object("resources/images/ground.png", body)
    {
        float w = sprite_.getTextureRect().width;
        float h = sprite_.getTextureRect().height;
        float TEXTURE_SCALE = 64.0f;

        sprite_.setScale(50.0f * TEXTURE_SCALE / w, 10.0f * TEXTURE_SCALE / h);
        texture_.setRepeated(true);
        sprite_.setTextureRect({0, 0, static_cast<int>(100 * scale), static_cast<int>(6 * scale)}); // just hard coded based on Level Constructor

        sprite_.setOrigin(0, 150);
    };

    virtual char GetType() { return 'G'; };

private:
};

#endif // ANGRY_BIRDS_GROUND