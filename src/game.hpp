#ifndef ANGRY_BIRDS_GAME
#define ANGRY_BIRDS_GAME

#include "level.hpp"
#include "main_menu.hpp"
#include "level_selector.hpp"
#include <fstream>
#include <sstream>
#include "utils.hpp"

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
};

#endif // ANGRY_BIRDS_GAME