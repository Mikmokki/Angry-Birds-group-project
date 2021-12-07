#ifndef ANGRY_BIRDS_MENU
#define ANGRY_BIRDS_MENU

#include <SFML/Graphics.hpp>
#include "converters.hpp"

class Menu
{
public:
    Menu();
    ~Menu();
    virtual void Draw(sf::RenderWindow &window) = 0;
    bool IsOpen();
    void Close();
    void Open();

protected:
    bool open_;
    sf::Font font_;
    sf::RectangleShape background_;
    sf::Texture background_image_;
};

#endif