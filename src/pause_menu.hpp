#ifndef ANGRY_BIRDS_PAUSE_MENU
#define ANGRY_BIRDS_PAUSE_MENU

#include "menu.hpp"

class PauseMenu : public Menu
{
public:
    PauseMenu();
    void Draw(sf::RenderWindow &window);

private:
    const static int button_amount_ = 2;
    sf::Text menu_items_[button_amount_];
};

#endif