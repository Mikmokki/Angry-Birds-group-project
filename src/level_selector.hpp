#ifndef ANGRY_BIRDS_LEVEL_SELECTOR
#define ANGRY_BIRDS_LEVEL_SELECTOR

#include "menu.hpp"
#include <string>

class LevelSelector : public Menu
{
public:
    LevelSelector();
    void Draw(sf::RenderWindow &window);

private:
    const static int level_amount_ = 3;
    sf::Text level_names_[level_amount_];
    sf::Texture preview_textures_[level_amount_];
    sf::RectangleShape preview_images_[level_amount_];
};

#endif
