#include "converters.hpp"

namespace utils
{

    sf::Vector2f B2ToSfCoords(const b2Vec2 b2_vector)
    {
        return sf::Vector2f(scale * b2_vector.x, viewheight - (scale * b2_vector.y));
    }

    b2Vec2 SfToB2Coords(const sf::Vector2f sf_vector)
    {
        return b2Vec2(sf_vector.x / scale, (viewheight - sf_vector.y) / scale);
    }

    float RadiansToDegrees(const float radians)
    {
        return radians * (180.0f / M_PI);
    }

    float DegreesToRadians(const float degrees)
    {
        return degrees * (M_PI / 180.0f);
    }

    void PathPrefix()
    {
        char buf[4096]; // never know how much is needed
        std::string str = cwd(buf, sizeof buf);
        auto string_size = str.size();
        std::string ab = "angry-birds-group-2";
        auto subStr = str.substr(string_size - 3, 3);
        while (true)
        {

            str = cwd(buf, sizeof buf);
            string_size = str.size();
            subStr = str.substr(string_size - 19, 19);

            if (subStr == ab)
            {
                return;
            }

            cd("..");
        }
    }
}