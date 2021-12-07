#ifndef ANGRY_BIRDS_LEVEL
#define ANGRY_BIRDS_LEVEL

#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "bird.hpp"
#include "converters.hpp"
#include <iostream>
#include <tuple>
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

    Bird *GetBird()
    {
        return birds_.front();
    }

    int GetScore()
    {
        return score_;
    }

    int GetHighScore();

    std::list<int> UpdateHighScore();

    void ThrowBird(int angle, b2Vec2 velocity);

    std::vector<int> CountBirdTypes();

    int CountPigs();

    void ResetBird();

    bool IsLevelEnded() { return level_ended_; }

    // Returns true if world hasn't settled yet
    bool DrawLevel(sf::RenderWindow &window);

    // Returns { direction, power } of the arrow
    std::tuple<float, float> DrawArrow(sf::RenderWindow &window);

    void SaveState(std::ofstream &file);

private:
    std::string name_;
    std::list<Bird *> birds_;
    b2World *world_;
    std::list<Object *> objects_;
    int score_ = 0;
    std::list<int> high_scores_;
    bool level_ended_ = false;
};

#endif // ANGRY_BIRDS_LEVEL