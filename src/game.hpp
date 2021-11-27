#ifndef ANGRY_BIRDS_GAME
#define ANGRY_BIRDS_GAME

#include "level.hpp"

const int viewwidth = 1600;
const int viewheight = 900;
const int framerate = 60;
const float time_step = 1.0f / framerate;
const int velocity_iterations = 6;
const int position_iterations = 2;

class Game
{
public:
    Game(){};
    void LoadLevel(std::string filename);
    void Start();

private:
    Level current_level_;
};

#endif // ANGRY_BIRDS_GAME