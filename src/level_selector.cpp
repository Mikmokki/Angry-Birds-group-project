#include "level_selector.hpp"

LevelSelector::LevelSelector()
{
    std::string name_texts[level_amount_] = {"Level 1", "Level 2", "Level 3"};
    std::string preview_filenames[level_amount_] = {"preview1.png", "preview2.png", "preview3.png"};
    for (int i = 0; i < level_amount_; i++)
    {
        level_names_[i].setFont(font_);
        level_names_[i].setFillColor(sf::Color::White);
        level_names_[i].setString(name_texts[i]);
        level_names_[i].setCharacterSize(80);
        level_names_[i].setPosition(100 + i * 500, 600);
    }
    for (int i = 0; i < level_amount_; i++)
    {
        preview_textures_[i].loadFromFile("resources/images/" + preview_filenames[i]);
        preview_images_[i].setTexture(&preview_textures_[i]);
        preview_images_[i].setSize(sf::Vector2f(viewwidth, viewheight) / 5.0f);
        preview_images_[i].setPosition(100 + i * 500, 400);
    }
}

void LevelSelector::Draw(sf::RenderWindow &window)
{
    window.draw(background_);
    for (auto image : preview_images_)
    {
        window.draw(image);
    }
    for (auto level_name : level_names_)
    {
        window.draw(level_name);
    }
}
