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
#include <map>

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

    std::tuple<std::string, int> GetHighScore();

    int GetLevelNumber()
    {
        return level_number_;
    }

    std::list<std::tuple<std::string, int>> UpdateHighScore(std::string nickname);

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

    int GetStars()
    {
        return std::count_if(star_tresholds_.begin(), star_tresholds_.end(), [this](int i)
                             { return GetScore() >= i; });
    }

private:
    std::string name_;
    std::list<Bird *> birds_;
    b2World *world_;
    std::list<Object *> objects_;
    int score_ = 0;
    std::list<std::tuple<std::string, int>> high_scores_;
    bool level_ended_ = false;
    int level_number_;
    std::list<int> star_tresholds_;
};

#endif // ANGRY_BIRDS_LEVEL