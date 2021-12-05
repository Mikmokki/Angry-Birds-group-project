#ifndef ANGRY_BIRDS_GAME
#define ANGRY_BIRDS_GAME

#include "level.hpp"
#include "main_menu.hpp"
#include <fstream>
#include <sstream>

class Game
{
public:
    Game(){};
    void LoadLevel(std::string filename);
    void SaveLevel();
    void Start();

private:
    std::ofstream OpenFileSafe(const std::string filename);
    Level current_level_;
    const std::string file_suffix = "ab"; // ab as in Angry Birds
};

#endif // ANGRY_BIRDS_GAME