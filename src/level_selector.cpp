#include "level_selector.hpp"

LevelSelector::LevelSelector()
{
    std::string name_texts[level_amount_] = {"Level 1", "Level 2", "Level 3"};
    font_.loadFromFile("../resources/fonts/Raleway-Medium.ttf");
    open_ = true;
    background_image_.loadFromFile("../resources/images/menu.png");
    background_.setSize(sf::Vector2f(viewwidth, viewheight));
    background_.setTexture(&background_image_);
    background_.setPosition(0, 0);
    for (int i = 0; i < level_amount_; i++)
    {
        level_names_[i].setFont(font_);
        level_names_[i].setFillColor(sf::Color::White);
        level_names_[i].setString(name_texts[i]);
        level_names_[i].setCharacterSize(80);
        level_names_[i].setPosition(100 + i * 500, 700);
    }
}

void LevelSelector::Draw(sf::RenderWindow &window)
{
    window.draw(background_);
    for (auto level_name : level_names_)
    {
        window.draw(level_name);
    }
}

bool LevelSelector::IsOpen()
{
    return open_;
}

void LevelSelector::Close()
{
    open_ = false;
}

void LevelSelector::Open()
{
    open_ = true;
}

LevelSelector::~LevelSelector() {}