#include "mainMenu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
MainMenu::MainMenu()
{
    std::vector<std::string> buttonTexts{"Play", "Level Editor", "High Scores", "Exit"};
    font_.loadFromFile("../../resources/fonts/Raleway-Medium.ttf");
    open_ = true;
    backgroundImage_.loadFromFile("../../resources/images/menu.png");
    background_.setSize(sf::Vector2f(1600, 900));
    background_.setTexture(&backgroundImage_);
    background_.setPosition(0, 0);
    for (int i = 0; i < 4; ++i)
    {
        menuItems_[i].setFont(font_);
        menuItems_[i].setFillColor(sf::Color::White);
        menuItems_[i].setString(buttonTexts[i]);
        menuItems_[i].setCharacterSize(80);
        menuItems_[i].setPosition(1000, 200 + i * 100);
    }
};

void MainMenu::Draw(sf::RenderWindow &window)
{
    window.draw(background_);
    for (int i = 0; i < 4; ++i)
    {
        window.draw(menuItems_[i]);
    }
}
bool MainMenu::IsOpen()
{
    return open_;
};

void MainMenu::Close()
{
    open_ = false;
}
void MainMenu::Open()
{
    open_ = true;
}

MainMenu::~MainMenu(){

};