#ifndef ANGRY_BIRDS_MAIN_MENU
#define ANGRY_BIRDS_MAIN_MENU

#include "menu.hpp"
#include <string>

class MainMenu : public Menu
{
public:
    MainMenu();
    void Draw(sf::RenderWindow &window);

private:
    const static int button_amount_ = 3;
    sf::Text menu_items_[button_amount_];
};

#endif
