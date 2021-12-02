#ifndef ANGRY_BIRDS_GROUND
#define ANGRY_BIRDS_GROUND

#include "object.hpp"

class Ground : public Object
{
public:
    Ground(b2Body *body) : Object("../../resources/images/ground.png", body)
    {
        texture_.setRepeated(true);
        sprite_.setTextureRect({0, 0, static_cast<int>(10 * scale), static_cast<int>(2 * scale)}); // just hard coded based on Level Constructor
        sprite_.setOrigin(0, 900 - (-10 * scale));
    };

private:
};

#endif // ANGRY_BIRDS_GROUND