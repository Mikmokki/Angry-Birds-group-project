#ifndef ANGRY_BIRDS_LEVEL
#define ANGRY_BIRDS_LEVEL

#include <string>
#include <Box2D/box2d.h>

const b2Vec2 gravity(0.0f, -9.8f);

class Level
{
public:
    Level(std::string &name) : name_(name), world_(gravity){};

    std::string GetName() const
    {
        return name_;
    };

private:
    std::string name_;
    b2World world_;
};

#endif // ANGRY_BIRDS_LEVEL