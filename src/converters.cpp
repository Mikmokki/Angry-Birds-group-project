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
        //std::string_view strW(str);

        auto koko = str.size();
        std::string ab = "angry-birds-group-2";

        /* auto subStr = str.substr(koko - 3, 3);
        std::cout << "substr: " << subStr << std::endl;
        if (subStr != "src")
        {
            std::cout << "CWD: " << ab.size() << std::endl;
            std::cout << "../../" << std::endl;
            return "../../";
        }
        std::cout << "CWD: " << cwd(buf, sizeof buf) << std::endl;
        std::cout << "../" << std::endl;
        return "../"; */
        auto subStr = str.substr(koko - 3, 3);
        while (true)
        {

            str = cwd(buf, sizeof buf);
            koko = str.size();
            subStr = str.substr(koko - 19, 19);

            if (subStr == ab)
            {
                return;
            }

            cd("..");
        }
    }
}