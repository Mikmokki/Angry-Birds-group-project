#ifndef ANGRY_BIRDS_CONVERTERS
#define ANGRY_BIRDS_CONVERTERS

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "math.h"
#define M_PI 3.14159265358979323846

const int viewwidth = 1600;
const int viewheight = 900;
const int framerate = 60;
const float time_step = 1.0f / framerate;
const int velocity_iterations = 6;
const int position_iterations = 2;
const b2Vec2 gravity(0.0f, -9.8f);
const float scale = 100.0f;
const b2Vec2 bird_starting_position(3, 3);

namespace utils
{
    sf::Vector2f B2ToSfCoords(const b2Vec2 b2_vector);

    b2Vec2 SfToB2Coords(const sf::Vector2f sf_vector);

    float RadiansToDegrees(const float radians);

    float DegreesToRadians(const float degrees);

}

#endif // ANGRY_BIRDS_CONVERTERS