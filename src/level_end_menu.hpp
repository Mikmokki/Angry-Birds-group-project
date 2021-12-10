#ifndef ANGRY_BIRDS_LEVEL_END_MENU
#define ANGRY_BIRDS_LEVEL_END_MENU

#include "menu.hpp"
#include "converters.hpp"
#include <string>
#include <iostream>
class LevelEndMenu : public Menu
{
public:
    LevelEndMenu(int level_number);
    void Draw(sf::RenderWindow &window);
    void SelectStars(int no_of_stars);
    void SetLevel(int level_number);
    void ShowHighScore()
    {
        highscore_ = true;
    }

private:
    int level_number_;
    const static int image_amount = 3;
    sf::Text level_name_;
    sf::Texture textures_[image_amount];
    sf::RectangleShape elements_[image_amount];
    bool highscore_;
};

#endif
