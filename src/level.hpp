#ifndef ANGRY_BIRDS_LEVEL
#define ANGRY_BIRDS_LEVEL

#include <string>
#include <list>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "bird.hpp"
#include "converters.hpp"

class Level
{
public:
    Level();
    Level(std::string name, b2Vec2 bird_starting_pos);

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

    Bird *GetBird()
    {
        return birds_.front();
    }

    int GetScore()
    {
        return score_;
    }

    void ThrowBird(int angle, b2Vec2 velocity);

    void ResetBird();

    // Returns true if world hasn't settled yet
    bool DrawLevel(sf::RenderWindow &window);

    // Returns { direction, power } of the arrow
    std::tuple<float, float> DrawArrow(sf::RenderWindow &window);

private:
    std::string name_;
    b2Vec2 bird_starting_position_;
    std::list<Bird *> birds_;
    b2World *world_;
    std::list<Object *> objects_;
    int score_ =0;
};

#endif // ANGRY_BIRDS_LEVEL