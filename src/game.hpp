#ifndef ANGRY_BIRDS_GAME
#define ANGRY_BIRDS_GAME

#include "level.hpp"

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