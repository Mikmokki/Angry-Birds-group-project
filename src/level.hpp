#ifndef ANGRY_BIRDS_LEVEL
#define ANGRY_BIRDS_LEVEL

#include <string>
#include <list>
#include <Box2D/box2d.h>
#include "object.hpp"

const b2Vec2 gravity(0.0f, -9.8f);

class Level
{
public:
    Level(std::string name, b2Vec2 bird_starting_pos);

    std::string GetName() const
    {
        return name_;
    };

    b2World *GetWorld()
    {
        return &world_;
    }

    void ThrowBird(int angle, b2Vec2 velocity);

private:
    const std::string name_;
    const b2Vec2 bird_starting_position_;
    b2World world_;
    std::list<Object *> objects_;
};

#endif // ANGRY_BIRDS_LEVEL