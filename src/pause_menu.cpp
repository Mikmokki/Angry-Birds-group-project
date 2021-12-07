#include "pause_menu.hpp"

PauseMenu::PauseMenu() : Menu()
{
    std::string button_texts[button_amount_] = {"Resume", "Main menu"};
    for (int i = 0; i < button_amount_; ++i)
    {
        menu_items_[i].setFont(font_);
        menu_items_[i].setFillColor(sf::Color::White);
        menu_items_[i].setString(button_texts[i]);
        menu_items_[i].setCharacterSize(80);
        menu_items_[i].setPosition(1000, 200 + i * 100);
    }
}

void PauseMenu::Draw(sf::RenderWindow &window)
{
    window.draw(background_);
    for (auto menu_item : menu_items_)
    {
        window.draw(menu_item);
    }
}