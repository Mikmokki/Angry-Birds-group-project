#include "level_end_menu.hpp"

LevelEndMenu::LevelEndMenu(int level_number)
{
    Close();
    SetLevel(level_number);
}

void LevelEndMenu::Draw(sf::RenderWindow &window)
{
    int loop_end = image_amount - 1;
    if (highscore_)
    {
        textures_[2].loadFromFile("resources/images/highscore.png");
        elements_[2].setSize(sf::Vector2f(viewwidth, viewheight) / 6.0f);
        elements_[2].setTexture(&textures_[2]);
        elements_[2].setPosition(window.mapPixelToCoords(sf::Vector2i(5 * viewwidth / 12, viewheight / 5 * 2)));
        loop_end++;
    }
    elements_[0].setPosition(window.mapPixelToCoords(sf::Vector2i(viewwidth / 4, viewheight / 4)));
    elements_[1].setPosition(window.mapPixelToCoords(sf::Vector2i(5 * viewwidth / 12, viewheight / 8)));
    level_name_.setPosition(window.mapPixelToCoords(sf::Vector2i(21 * viewwidth / 47, viewheight * 4 / 15)));

    for (int i = 0; i < loop_end; i++)
    {
        window.draw(elements_[i]);
    }
    window.draw(level_name_);
}
void LevelEndMenu::SelectStars(int no_of_stars)
{
    textures_[1].loadFromFile("resources/images/" + std::to_string(no_of_stars) + "_stars.png");
    elements_[1].setSize(sf::Vector2f(viewwidth, viewheight) / 6.0f);
    elements_[1].setTexture(&textures_[1]);
}

void LevelEndMenu::SetLevel(int level_number)
{
    level_number_ = level_number;
    highscore_ = false;
    level_name_.setFont(font_);
    level_name_.setFillColor(sf::Color(246, 215, 150));
    level_name_.setOutlineColor(sf::Color(165, 69, 11));
    level_name_.setOutlineThickness(2.0f);

    level_name_.setString("Level " + std::to_string(level_number_));
    level_name_.setCharacterSize(viewheight / 16);

    if (level_number_ == 3)
    {
        textures_[0].loadFromFile("resources/images/last_level_end.png");
    }
    else
    {
        textures_[0].loadFromFile("resources/images/level_end.png");
    }
    elements_[0].setSize(sf::Vector2f(viewwidth, viewheight) / 2.0f);
    elements_[0].setTexture(&textures_[0]);
}
