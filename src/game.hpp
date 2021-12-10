#ifndef ANGRY_BIRDS_GAME
#define ANGRY_BIRDS_GAME

#include "level.hpp"
#include "main_menu.hpp"
#include "pause_menu.hpp"
#include "level_selector.hpp"
#include "level_end_menu.hpp"
#include <fstream>
#include <sstream>
#include "utils.hpp"

class Game
{
public:
    Game();
    void LoadLevel(std::string filename);
    void SaveLevel();
    void UpdateSavedHighScore(std::list<int> high_scores);
    void LoadIcon();
    void Start();

private:
    std::string current_level_file_name_;
    Level current_level_;
    sf::RenderWindow window_;
    sf::Texture background_texture_;
    sf::Sprite bg_sprite_;
    int victory_achieved_; // Variable for keeping track if the victory sound has already played
};

#endif // ANGRY_BIRDS_GAME