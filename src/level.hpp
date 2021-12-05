#ifndef ANGRY_BIRDS_LEVEL
#define ANGRY_BIRDS_LEVEL

#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "bird.hpp"
#include "converters.hpp"

class Level
{
public:
    Level();
    Level(std::string name);
    Level(std::ifstream &file);

    std::string GetName() const
    {
        return name_;
    };

    b2World *GetWorld()
    {
        return world_;
    }

    std::list<Object *> objects()
    {
        return objects_;
    }

    Object *GetBird()
    {
        return bird_;
    }

    void ThrowBird(int angle, b2Vec2 velocity);

    void ResetBird();

    // Returns true if world hasn't settled yet
    bool DrawLevel(sf::RenderWindow &window);

    // Returns { direction, power } of the arrow
    std::tuple<float, float> DrawArrow(sf::RenderWindow &window);

    void SaveState(std::ofstream &file);

private:
    std::string name_;
    Bird *bird_;
    b2World *world_;
    std::list<Object *> objects_;
};

#endif // ANGRY_BIRDS_LEVEL