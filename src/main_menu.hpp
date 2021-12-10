#ifndef ANGRY_BIRDS_MAIN_MENU
#define ANGRY_BIRDS_MAIN_MENU

#include "menu.hpp"
#include <string>

class MainMenu : public Menu
{
public:
    MainMenu();
    void Draw(sf::RenderWindow &window);
    std::string GetNickname() const
    {
        return nickname_;
    }
    void ChangeNickname(char ch)
    {
        std::cout << ch << std::endl;
        if (ch == 8)
        {
            if (nickname_.size() > 0)
            {
                nickname_ = nickname_.erase(nickname_.size() - 1, nickname_.size());
            }
        }
        else
        {
            if (nickname_.size() < 13)
            {
                nickname_ += ch;
            }
        }

        menu_items_[4].setString(nickname_);
    }

private:
    const static int button_amount_ = 5;
    sf::Text menu_items_[button_amount_];
    sf::RectangleShape nickname_input_;
    std::string nickname_ = "Player 1";
};

#endif
