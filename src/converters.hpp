#ifndef ANGRY_BIRDS_CONVERTERS
#define ANGRY_BIRDS_CONVERTERS

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "math.h"
#define M_PI 3.14159265358979323846
#include <iostream>

#ifdef _WIN32
#include <direct.h>
// MSDN recommends against using getcwd & chdir names
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif

const int viewwidth = 1600;
const int viewheight = 900;
const int framerate = 60;
const float time_step = 1.0f / framerate;
const int velocity_iterations = 6;
const int position_iterations = 2;
const b2Vec2 gravity(0.0f, -9.8f);
const float scale = 100.0f;
const b2Vec2 bird_starting_position(3, 2.5f);
const std::string file_suffix = "ab"; // ab as in Angry Birds

namespace utils
{
    sf::Vector2f B2ToSfCoords(const b2Vec2 b2_vector);

    b2Vec2 SfToB2Coords(const sf::Vector2f sf_vector);

    float RadiansToDegrees(const float radians);

    float DegreesToRadians(const float degrees);

    void PathPrefix();

}

#endif // ANGRY_BIRDS_CONVERTERS