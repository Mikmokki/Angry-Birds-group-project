#include "menu.hpp"

Menu::Menu()
{
    font_.loadFromFile("../resources/fonts/Raleway-Medium.ttf");
    open_ = true;
    background_image_.loadFromFile("../resources/images/menu.png");
    background_.setSize(sf::Vector2f(viewwidth, viewheight));
    background_.setTexture(&background_image_);
    background_.setPosition(0, 0);
};

Menu::~Menu(){};

bool Menu::IsOpen() { return open_; };

void Menu::Close() { open_ = false; };

void Menu::Open() { open_ = true; };
