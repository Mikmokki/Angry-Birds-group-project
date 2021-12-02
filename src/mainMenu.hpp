#ifndef ANGRY_BIRDS_MENU
#define ANGRY_BIRDS_MENU
#include <SFML/Graphics.hpp>

class MainMenu
{
public:
    MainMenu();
    void Draw(sf::RenderWindow &window);
    bool IsOpen();
    ~MainMenu();
    void Close();
    void Open();

private:
    bool open_;
    sf::Font font_;
    sf::RectangleShape background_;
    sf::Texture backgroundImage_;
    sf::Text menuItems_[4];
};
#endif
