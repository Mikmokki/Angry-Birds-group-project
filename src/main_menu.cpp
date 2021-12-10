#include "main_menu.hpp"

MainMenu::MainMenu() : Menu()
{
    std::string button_texts[button_amount_] = {"Play", "High Scores", "Exit", "Player Name:", nickname_};
    for (int i = 0; i < button_amount_; ++i)
    {
        menu_items_[i].setFont(font_);
        menu_items_[i].setString(button_texts[i]);
        if (i < 3)
        {
            menu_items_[i].setFillColor(sf::Color::White);
            menu_items_[i].setCharacterSize(80);
            menu_items_[i].setPosition(1000, 200 + i * 100);
        }
    }
    menu_items_[3].setCharacterSize(20);
    menu_items_[3].setPosition(1020, 505);
    menu_items_[4].setCharacterSize(30);
    menu_items_[4].setPosition(1020, 535);
    menu_items_[3].setFillColor(sf::Color::Black);
    menu_items_[4].setFillColor(sf::Color::Black);
    nickname_input_.setFillColor(sf::Color::White);
    nickname_input_.setSize(sf::Vector2f(viewwidth / 5.0f, viewheight / 10.0f));
    nickname_input_.setPosition(1006, 500);
};

void MainMenu::Draw(sf::RenderWindow &window)
{
    window.draw(background_);
    window.draw(nickname_input_);
    for (auto menu_item : menu_items_)
    {
        window.draw(menu_item);
    }
}
